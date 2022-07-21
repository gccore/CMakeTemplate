cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(PROJECT_MAJOR_VERSION 1)
set(PROJECT_MINOR_VERSION 0)
set(PROJECT_PATCH_VERSION 0)
set(PROJECT_VERSION ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION})

project(SharedLibrary
  LANGUAGES CXX
  VERSION ${PROJECT_VERSION}
  DESCRIPTION "Shared Library CMake Template"
)
set(project_with_version_name ${PROJECT_NAME}-${PROJECT_VERSION})

cmake_policy(SET CMP0100 NEW) # For *.hh, MOC

option(option_install_private_headers
  "Do you want to define an install role for the private headers?" on)

set(headers_dir ${PROJECT_SOURCE_DIR}/Include)
set(public_headers_dir ${headers_dir}/Public)
set(private_headers_dir ${headers_dir}/Private)

file(GLOB source_files Source/*.cc)
file(GLOB public_header_files ${public_headers_dir}/${PROJECT_NAME}/*.hh)
file(GLOB private_header_files ${private_headers_dir}/${PROJECT_NAME}/*.hh)

source_group("Source Files" FILES ${source_files})
source_group("Public Headers" FILES ${public_header_files})
source_group("Private Headers" FILES ${private_header_files})

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
    OUTPUT_NAME ${project_with_version_name}
    AUTOMOC on
    AUTOUIC on
    AUTORCC on
)
target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_NAME}_VERSION="${PROJECT_VERSION}"
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
)

set(headers_install_dir include/${project_with_version_name})
set(public_headers_install_dir ${headers_install_dir}/Public)
set(private_headers_install_dir ${headers_install_dir}/Private)

set(generated_headers_dir
  ${PROJECT_BINARY_DIR}/Include/${project_with_version_name})
set(generated_public_headers_dir ${generated_headers_dir}/Public)
set(generated_private_headers_dir ${generated_headers_dir}/Private)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    $<BUILD_INTERFACE:${public_headers_dir}>
    $<BUILD_INTERFACE:${private_headers_dir}>
    $<BUILD_INTERFACE:${generated_public_headers_dir}>
    $<BUILD_INTERFACE:${generated_private_headers_dir}>

  PUBLIC
    $<INSTALL_INTERFACE:${public_headers_install_dir}>
    $<INSTALL_INTERFACE:${private_headers_install_dir}>
)

set(cmake_configs_dir lib/cmake/${project_with_version_name})

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Config
)
install(
  EXPORT ${PROJECT_NAME}Config
  NAMESPACE gccore::
  DESTINATION ${cmake_configs_dir}
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
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake)
write_basic_package_version_file(
  ${project_config_version_path}
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)
install(
  FILES
    ${project_config_version_path}
  DESTINATION ${cmake_configs_dir}
)

include(GenerateExportHeader)

set(project_export_macro_path
  ${generated_public_headers_dir}/${PROJECT_NAME}/${PROJECT_NAME}Export.hh)
generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME ${project_export_macro_path}
)
install(
  FILES
    ${project_export_macro_path}
  DESTINATION ${public_headers_install_dir}/${PROJECT_NAME}
)
list(APPEND public_header_files ${project_export_macro_path})
target_sources(${PROJECT_NAME} PRIVATE ${project_export_macro_path})
