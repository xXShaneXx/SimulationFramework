cmake_minimum_required(VERSION 3.16)
project(SimulationFramework)

option(SIMULATIONFRAMEWORK_ENABLE_INSTALL "Enable install targets" ON)

set(CMAKE_CXX_STANDARD 17)

add_library(SimulationFramework INTERFACE)
target_include_directories(SimulationFramework INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(SIMULATIONFRAMEWORK_ENABLE_INSTALL)
    include(GNUInstallDirs)

    install(TARGETS SimulationFramework
            EXPORT SimulationFrameworkTargets)

    install(DIRECTORY include/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    install(EXPORT SimulationFrameworkTargets
            FILE SimulationFrameworkTargets.cmake
            NAMESPACE simframework::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimulationFramework)

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/SimulationFrameworkConfigVersion.cmake"
        VERSION 1.0
        COMPATIBILITY AnyNewerVersion
    )

    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/SimulationFrameworkConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/SimulationFrameworkConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimulationFramework
    )
endif()
