cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(PROJECT_MAJOR_VERSION 1)
set(PROJECT_MINOR_VERSION 0)
set(PROJECT_PATCH_VERSION 0)

cmake_policy(SET CMP0100 NEW) # For *.hh, MOC

project(%{ProjectName} 
  LANGUAGES CXX 
  VERSION 
    ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION}
)

add_executable(${PROJECT_NAME}
  %{CppFileName}
)
add_executable(gccore::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    VERSION ${PROJECT_VERSION}
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
)
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
