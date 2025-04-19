#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <memory>
#include <vector>

#include "interfaces.hpp"

namespace simframework {

    template<typename Input, typename Output>
    class Simulation;

    template<typename Input, typename Output>
    class SimulationBuilder {
    public:
        SimulationBuilder() = default;

        SimulationBuilder& set_range(int start, int end, int step) {
            this->start = start;
            this->end = end;
            this->step = step;
            return *this;
        }

        SimulationBuilder& set_repetitions(int reps) {
            this->repetitions = reps;
            return *this;
        }

        SimulationBuilder& set_input_generator(std::shared_ptr<IInputGenerator<Input>> gen) {
            this->inputGenerator = std::move(gen);
            return *this;
        }

        SimulationBuilder& set_simulator(std::shared_ptr<ISimulator<Input, Output>> sim) {
            this->simulator = std::move(sim);
            return *this;
        }

        SimulationBuilder& add_metric(
            std::shared_ptr<IMetric<Output>> metric,
            std::shared_ptr<IAggregator> aggregator = std::make_shared<MeanAggregator>()
        ) {
            this->metrics.push_back(std::move(metric));
            this->aggregators.push_back(std::move(aggregator));
            return *this;
        }

        std::unique_ptr<Simulation<Input, Output>> build() {
            auto simulation = std::make_unique<Simulation<Input, Output>>(start, end, step, repetitions);
            if (inputGenerator) {
                simulation->set_input_generator(std::move(inputGenerator));
            }
            if (simulator) {
                simulation->set_simulator(std::move(simulator));
            }
            for (size_t i = 0; i < metrics.size(); ++i) {
                simulation->add_metric(std::move(metrics[i]));
            }
            return simulation;
        }

    private:
        int start = 10, end = 100, step = 10, repetitions = 5;
        std::shared_ptr<IInputGenerator<Input>> inputGenerator;
        std::shared_ptr<ISimulator<Input, Output>> simulator;
        std::vector<std::shared_ptr<IMetric<Output>>> metrics;
        std::vector<std::shared_ptr<IAggregator>> aggregators;
    };


    template<typename Input, typename Output>
    class Simulation {
    public:
        Simulation() = default;
        
        static SimulationBuilder<Input, Output> create() {
            return SimulationBuilder<Input, Output>();
        }

        Simulation(int start, int end, int step, int repetitions):
            n_start(start), n_end(end), n_step(step), repetitions(repetitions) {}

        void set_input_generator(std::shared_ptr<IInputGenerator<Input>> gen) {
            inputGenerator = std::move(gen);
        }

        void set_simulator(std::shared_ptr<ISimulator<Input, Output>> sim) {
            simulator = std::move(sim);
        }

        void set_range(int start, int end, int step) {
            n_start = start;
            n_end = end;
            n_step = step;
        }

        void set_repetitions(int reps) {
            repetitions = reps;
        }

        void add_metric(std::shared_ptr<IMetric<Output>> metric) {
            metrics.push_back(std::move(metric));
        }

        void run() {
            rawResults.clear();

            for (int n = n_start; n <= n_end; n += n_step) {
                std::vector<Output> results;

                for (int i = 0; i < repetitions; ++i) {
                    Input input = inputGenerator->generate(n);
                    Output output = (*simulator)(input);
                    results.push_back(output);
                }

                rawResults[n] = std::move(results);
            }
        }

        std::map<std::string, std::map<int, double>>
        get_results(std::shared_ptr<IAggregator> aggregator) const {
            std::map<std::string, std::map<int, double>> finalResults;
        
            for (const auto& metric : metrics) {
                const std::string& name = metric->name();
        
                for (const auto& [n, outputs] : rawResults) {
                    std::vector<double> extracted;
                    for (const auto& out : outputs) {
                        extracted.push_back(metric->extract(out));
                    }
        
                    finalResults[name][n] = aggregator->aggregate(extracted);
                }
            }
        
            return finalResults;
        }


    private:
        int n_start = 10, n_end = 100, n_step = 10, repetitions = 5;

        std::shared_ptr<IInputGenerator<Input>> inputGenerator;
        std::shared_ptr<ISimulator<Input, Output>> simulator;
        std::vector<std::shared_ptr<IMetric<Output>>> metrics;

        std::map<int, std::vector<Output>> rawResults;
    };
}
#endif