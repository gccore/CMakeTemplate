cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(DeveloperTest 
  LANGUAGES CXX
  VERSION 0.0.0
  DESCRIPTION "Just a testing project for the idiot developer"
  HOMEPAGE_URL "https://github.com/gccore/CMakeTemplate"
)

set(CMAKE_VERBOSE_MAKEFILE on)

set(configs_directory_path ${PROJECT_SOURCE_DIR}/../Configs)
file(GLOB directories ${PROJECT_SOURCE_DIR}/*)
foreach(directory ${directories})
  if(IS_DIRECTORY ${directory})
    get_filename_component(directory_name ${directory} NAME)
    option(configuration_${directory_name} "Enable ${directory_name}" off)
    if (${configuration_${directory_name}})
      add_subdirectory(${directory})
      file(
        COPY ${directory}/CMakeLists.txt
        DESTINATION ${configs_directory_path}/${directory_name}
      )
    endif()
  endif()
endforeach()
