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
#include <simframework/simulation.hpp>
#include <simframework/interfaces.hpp>
#include <iostream>

struct MySystem : public simfw::ISystem {
    void update(double dt) override {
        std::cout << "System updated with dt = " << dt << "\n";
    }
};

int main() {
    simfw::Simulation sim;
    sim.addSystem(std::make_shared<MySystem>());

    sim.update(0.1);
    return 0;
}
```

## Notes

* The framework is currently header-only, so no separate compilation is required.
* You can disable installation by setting `SIMULATIONFRAMEWORK_ENABLE_INSTALL=OFF` when configuring with CMake.

---

Happy simulating!

