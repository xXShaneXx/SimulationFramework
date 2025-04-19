include(GNUInstallDirs)

install(TARGETS SimulationFramework
        EXPORT SimulationFrameworkTargets)

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT SimulationFrameworkTargets
        FILE SimulationFrameworkTargets.cmake
        NAMESPACE simframework::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimulationFramework)

# Optional: Add a version file
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
