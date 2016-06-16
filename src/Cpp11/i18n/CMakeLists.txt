project(I18n)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(GLOB_RECURSE SRC_LIST src/*.c* src/*.h*)

################################################################################

foreach (SRC ${SRC_LIST})
    get_filename_component(SRC_FILE ${SRC} NAME_WE)
    add_executable(${SRC_FILE} ${SRC})
    # Enabling C++11. Add these two lines after add_executable
    set_property(TARGET ${SRC_FILE} PROPERTY CXX_STANDARD 11)
    set_property(TARGET ${SRC_FILE} PROPERTY CXX_STANDARD_REQUIRED ON)
endforeach (SRC ${SRC_LIST})


