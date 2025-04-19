cmake_minimum_required(VERSION 3.16)
project(SimulationFramework VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

# Header-only simulation library
add_library(SimulationFramework INTERFACE)
target_include_directories(SimulationFramework INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Export targets for installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    DIRECTORY include/SimulationFramework
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    TARGETS SimulationFramework
    EXPORT SimulationFrameworkTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT SimulationFrameworkTargets
    FILE SimulationFrameworkTargets.cmake
    NAMESPACE SimulationFramework::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimulationFramework
)

write_basic_package_version_file(
    SimulationFrameworkConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/SimulationFrameworkConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SimulationFrameworkConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimulationFramework
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/SimulationFrameworkConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/SimulationFrameworkConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimulationFramework
)

# GoogleTest via FetchContent (for testing only)
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(tests)
endif()