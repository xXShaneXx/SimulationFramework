# SimulationFramework

A lightweight and flexible C++ framework for building simulations.

## Features

* Interface-based architecture (`ISystem`, `ISimulation`) for modular design.
* Header-only library.
* Easy integration using CMake.
* Supports installation via CMake.

## Requirements

* CMake >= 3.16
* C++17 compatible compiler (e.g., GCC 9+, Clang 10+, MSVC 2019+)

## Building and Installing

### 1. Clone the Repository

```bash
# Clone your project repository
git clone https://github.com/xXShaneXx/SimulationFramework simulationframework
cd SimulationFramework
```

### 2. Build and Install (Optional)

```bash
# Create a build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_INSTALL_PREFIX=/your/install/path

# Install
cmake --build . --target install
```

The framework will be installed to `/your/install/path`.

## Usage

### 1. Install and Find Package

If you installed SimulationFramework, in your `CMakeLists.txt`:

```cmake
find_package(SimulationFramework REQUIRED)

add_executable(YourExecutable main.cpp)
target_link_libraries(YourExecutable PRIVATE simframework::SimulationFramework)
```

Make sure to add the appropriate `CMAKE_PREFIX_PATH` if the framework is installed in a non-standard location:

```bash
cmake -DCMAKE_PREFIX_PATH=/your/install/path ..
```

### 2. Add as Subdirectory (Optional)

Alternatively, you can directly add the framework into your project without installing:

1. Clone SimulationFramework into your project:

```bash
git clone <your-repo-url> simulationframework
```

2. Modify your `CMakeLists.txt`:

```cmake
# Add the SimulationFramework folder
add_subdirectory(simulationframework)

# Link to your executable
add_executable(YourExecutable main.cpp)
target_link_libraries(YourExecutable PUBLIC simframework::SimulationFramework)
```

3. Include the headers in your source files:

```cpp
#include <simframework/simulation.hpp>
#include <simframework/interfaces.hpp>
```

✅ No install step is needed.
✅ No `find_package()` needed.

---

## Example

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <simframework/interfaces.hpp>
#include <simframework/simulation.hpp>


using namespace simframework;
// Input type
struct TestInput {
    std::vector<double> values;
};

// Output type
struct TestOutput {
    double result;
};

// Input generator
class TestInputGenerator : public IInputGenerator<TestInput> {
public:
    TestInput generate(int size) const override {
        TestInput input;
        for (int i = 0; i < size; ++i) {
            input.values.push_back(static_cast<double>(rand()) / RAND_MAX);
        }
        return input;
    }
};

// Simulator
class TestSimulator : public ISimulator<TestInput, TestOutput> {
public:
    TestOutput operator()(const TestInput& input) const override {
        TestOutput output;
        output.result = std::accumulate(input.values.begin(), input.values.end(), 0.0);
        return output;
    }
};

// Sum metric
class SumMetric : public IMetric<TestOutput> {
public:
    std::string name() const override { return "sum"; }
    double extract(const TestOutput& output) const override {
        return output.result;
    }
};

int main() {
    // Create a simulation builder
    auto builder = Simulation<TestInput, TestOutput>::create()
        .set_range(10, 50, 10)  // From size 10 to 50 in steps of 10
        .set_repetitions(3)     // 3 repetitions per size
        .set_input_generator(std::make_shared<TestInputGenerator>())
        .set_simulator(std::make_shared<TestSimulator>())
        .add_metric(std::make_shared<SumMetric>(), std::make_shared<MeanAggregator>());

    // Build and run the simulation
    auto simulation = builder.build();
    simulation->run();

    // Get and print results with different aggregators
    std::cout << "Results with Mean aggregation:\n";
    auto mean_results = simulation->get_results(std::make_shared<MeanAggregator>());
    for (const auto& [metric, values] : mean_results) {
        std::cout << "Metric: " << metric << "\n";
        for (const auto& [size, value] : values) {
            std::cout << "  Size " << size << ": " << value << "\n";
        }
    }

    std::cout << "\nResults with Max aggregation:\n";
    auto max_results = simulation->get_results(std::make_shared<MaxAggregator>());
    for (const auto& [metric, values] : max_results) {
        std::cout << "Metric: " << metric << "\n";
        for (const auto& [size, value] : values) {
            std::cout << "  Size " << size << ": " << value << "\n";
        }
    }

    return 0;
}
```

## Notes

* The framework is currently header-only, so no separate compilation is required.
* You can disable installation by setting `SIMULATIONFRAMEWORK_ENABLE_INSTALL=OFF` when configuring with CMake.

---

Happy simulating!

