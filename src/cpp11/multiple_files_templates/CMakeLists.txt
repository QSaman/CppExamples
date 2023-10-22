project(Templates)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(GLOB_RECURSE SRC_LIST src/*.c* src/*.h*)
set(project_name multiple_files_template)

################################################################################

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${project_name} ${SRC_LIST})
# Enabling C++11. Add these two lines after add_executable
set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${project_name} PROPERTY LINKER_LANGUAGE CXX)


