
cmake_minimum_required(VERSION 3.22)
project(binary-training)

enable_testing()
add_subdirectory(lib)

add_executable(
    binary-training
    src/main.cpp
    src/clock.cpp
    )

target_compile_features(
    binary-training
    PRIVATE
    cxx_std_17
    )

if(NOT EMSCRIPTEN)
    target_sources(binary-training PRIVATE src/terminal.cpp)
endif()

if(EMSCRIPTEN)
    # Generate a standalone exercise page alongside the WebAssembly binary.
    set_target_properties(binary-training PROPERTIES
        OUTPUT_NAME "index"
        SUFFIX ".html"
        LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html"
    )
    target_link_options(binary-training PRIVATE
        "--shell-file=${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html"
        "-sEXPORTED_RUNTIME_METHODS=ccall"
    )
endif()

find_package(Threads)
target_link_libraries(
    binary-training
    PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    )

add_subdirectory(test)

