#include <gtest/gtest.h>
#include <simframework/simulation.hpp>
#include <simframework/interfaces.hpp>
#include <random>
#include <numeric>

using namespace simframework;

struct Input {
    std::vector<int> data;
};

struct Output {
    int comparisons = 0;
    int swaps = 0;
};

class DummyInputGen : public IInputGenerator<Input> {
    public:
        Input generate(int n) const override {
            Input input;
            input.data.resize(n);
            std::iota(input.data.begin(), input.data.end(), 0);
            std::shuffle(input.data.begin(), input.data.end(), std::mt19937{std::random_device{}()});
            return input;
        }
};

class DummySimulator : public ISimulator<Input, Output> {
    public:
        Output operator()(const Input& input) const override { // Rename to 'operator()' and add 'const'
            Output out;
            out.comparisons = static_cast<int>(input.data.size() * 2);
            out.swaps = static_cast<int>(input.data.size());
            return out;
        }
};

class ComparisonMetric : public IMetric<Output> {
public:
    std::string name() const override { return "comparisons"; }
    double extract(const Output& out) const override { return out.comparisons; }
};

class SwapMetric : public IMetric<Output> {
public:
    std::string name() const override { return "swaps"; }
    double extract(const Output& out) const override { return out.swaps; }
};

TEST(SimulationTest, RunsAndReturnsResults) {
    Simulation<Input, Output> sim;
    sim.set_input_generator(std::make_shared<DummyInputGen>());
    sim.set_simulator(std::make_shared<DummySimulator>());
    sim.set_range(10, 30, 10);
    sim.set_repetitions(5);

    sim.add_metric(std::make_shared<ComparisonMetric>());
    sim.add_metric(std::make_shared<SwapMetric>());

    sim.run();

    auto results = sim.get_results(std::make_shared<MeanAggregator>());

    ASSERT_EQ(results.count("comparisons"), 1);
    ASSERT_EQ(results.count("swaps"), 1);

    for (const auto& [n, val] : results["comparisons"]) {
        ASSERT_GT(val, 0.0);
    }
}
