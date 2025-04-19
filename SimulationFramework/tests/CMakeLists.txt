add_executable(test_simulation test_simulation.cpp)

target_link_libraries(test_simulation
    PRIVATE
        SimulationFramework
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_simulation)
