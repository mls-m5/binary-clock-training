if(NOT EMSCRIPTEN)
    include(FetchContent)

    # Pin the latest doctest 2.x release; only native tests need this dependency.
    set(DOCTEST_WITH_MAIN_IN_STATIC_LIB OFF)
    set(DOCTEST_NO_INSTALL ON)
    FetchContent_Declare(doctest
        URL https://github.com/doctest/doctest/archive/refs/tags/v2.5.3.zip
        URL_HASH SHA256=5ddeafa34bece65b9f2e5207186fa70cd8ca44c00f41ae2c25e6e50b427c2b79
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(doctest)

    add_executable(clock-test clock_test.cpp terminal_test.cpp ../src/clock.cpp ../src/terminal.cpp)
    target_compile_features(clock-test PRIVATE cxx_std_17)
    target_link_libraries(clock-test PRIVATE doctest::doctest)
    add_test(NAME clock-test COMMAND clock-test)
endif()
