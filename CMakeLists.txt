cmake_minimum_required(VERSION 3.5.1)

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   1   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

project(ecs VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} LANGUAGES CXX)

# find_package(OpenGL REQUIRED)
# find_package(GLEW REQUIRED)
# find_package(assimp REQUIRED)

add_library(ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/ecs_common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/ecs.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/entity_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/component_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/system_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/src/system.cpp
)

add_library(Gamenge::ECS ALIAS ecs)

target_include_directories(ecs
    PUBLIC
        $<INSTALL_INTERFACE:source/inc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/inc>
        # ${OPENGL_INCLUDE_DIRS}
        # ${GLEW_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source/src
        # ${ASSIMP_INCLUDE_DIRS}
)

target_compile_options(ecs
    PRIVATE 
        $<$<CXX_COMPILER_ID:GNU>:-Wall>
)

target_compile_features(ecs
    PUBLIC
        cxx_auto_type
        #cxx_nullptr
        #cxx_lambdas
    PRIVATE
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# target_link_libraries(renderer
#     PUBLIC
#         OpenGL::GL
#         ${GLEW_LIBRARIES}
#         ${ASSIMP_LIBRARIES}
#     PRIVATE
#         # Boost::???
# )

include(GNUInstallDirs)
set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}/gamenge/ecs")

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ecs)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

install(TARGETS ecs
    EXPORT ecs-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(ecs PROPERTIES EXPORT_NAME ECS)

install(DIRECTORY source/inc/gamenge DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ecs-targets
    FILE
        ECSTargets.cmake
    NAMESPACE
        Gamenge::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ECSConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/ECSConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ECSConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ECSConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ECSConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT ecs-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/ECSTargets.cmake
    NAMESPACE Gamenge::
)

export(PACKAGE ECS)

find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )

endif()

enable_testing()
add_subdirectory(test)
