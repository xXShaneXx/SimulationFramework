# SimulationFramework

SimulationFramework is a lightweight, flexible, and extensible C++ framework for running simulations. It provides a modular design that allows users to define custom input generators, simulators, metrics, and aggregators to analyze simulation results.

## Features

- **Modular Design**: Easily extend the framework by implementing interfaces for input generation, simulation, metrics, and aggregation.
- **Builder Pattern**: Simplifies the creation and configuration of simulations.
- **Header-Only Library**: No need for additional compilation; just include the headers.
- **Custom Metrics and Aggregators**: Define your own metrics and aggregation strategies for analyzing simulation results.
- **Multiple Aggregation Methods**: Built-in support for mean, median, min, and max aggregations.

## Getting Started

### Prerequisites

- C++17 or later
- [CMake](https://cmake.org/) 3.16 or later (optional, for installation)
- [GoogleTest](https://github.com/google/googletest) (for testing)

### Installation

#### Option 1: Header-only usage
Simply include the `include/` directory in your project's include path.

#### Option 2: System-wide installation
```bash
git clone https://github.com/your-username/SimulationFramework.git
cd SimulationFramework
mkdir build && cd build
cmake -DSIMULATIONFRAMEWORK_ENABLE_INSTALL=ON ..
cmake --install .