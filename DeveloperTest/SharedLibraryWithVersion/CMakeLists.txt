cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(PROJECT_MAJOR_VERSION 1)
set(PROJECT_MINOR_VERSION 0)
set(PROJECT_PATCH_VERSION 0)

project(SharedLibraryWithVersion
  LANGUAGES CXX
  VERSION
    ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION}
)

cmake_policy(SET CMP0100 NEW) # For *.hh, MOC

option(option_install_private_headers
  "Do you want to define an install role for the private headers?" on)

set(headers_dir ${PROJECT_SOURCE_DIR}/Include)
set(public_headers_dir ${headers_dir}/Public)
set(private_headers_dir ${headers_dir}/Private)

file(GLOB source_files Source/*.cc)
file(GLOB public_header_files ${public_headers_dir}/${PROJECT_NAME}/*.hh)
file(GLOB private_header_files ${private_headers_dir}/*.hh)

source_group("Source Files"
  FILES
    ${source_files}
)
source_group("Public Headers"
  FILES
    ${public_header_files}
)
source_group("Private Headers"
  FILES
    ${private_header_files}
)

add_library(${PROJECT_NAME}
  SHARED
    ${source_files}
    ${public_header_files}
    ${private_header_files}
)
add_library(gccore::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_program(ccache_binary_path ccache REQUIRED)
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    CXX_COMPILER_LAUNCHER ${ccache_binary_path}
    OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION}
    AUTOMOC on
    AUTOUIC on
    AUTORCC on
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
)

set(headers_install_dir include/${PROJECT_NAME}-${PROJECT_VERSION})
set(public_headers_install_dir ${headers_install_dir}/Public)
set(private_headers_install_dir ${headers_install_dir}/Private)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    $<BUILD_INTERFACE:${public_headers_dir}>
    $<BUILD_INTERFACE:${private_headers_dir}>
  PUBLIC
    $<INSTALL_INTERFACE:${public_headers_install_dir}>
    $<INSTALL_INTERFACE:${private_headers_install_dir}>
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-${PROJECT_VERSION}Config
)
install(
  EXPORT ${PROJECT_NAME}-${PROJECT_VERSION}Config
  NAMESPACE gccore::
  DESTINATION lib/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
)
install(
  FILES
    ${public_header_files}
  DESTINATION ${public_headers_install_dir}/${PROJECT_NAME}
)
if(${option_install_private_headers})
  install(
    FILES
      ${private_header_files}
    DESTINATION ${private_headers_install_dir}/${PROJECT_NAME}
  )
endif()

include(CMakePackageConfigHelpers)

set(project_config_version_path
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}ConfigVersion.cmake)
write_basic_package_version_file(
  ${project_config_version_path}
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)
install(
  FILES
    ${project_config_version_path}
  DESTINATION lib/cmake/${PROJECT_NAME}
)
