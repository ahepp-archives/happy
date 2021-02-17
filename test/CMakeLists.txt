find_package(spdlog)

add_executable(
    happy_tests
        FakeTests.cpp
        DebouncerTests.cpp
        EdgeDetectorTests.cpp
        PulseRecorderTests.cpp
        PulsePlayerTests.cpp
        SquareWavePlayerTests.cpp
)
target_link_libraries(
    happy_tests
        PRIVATE
            happy
            spdlog
            gtest_main
)

if(${HAPPY_RUN_TESTS})
    add_custom_command(
        POST_BUILD
        TARGET happy_tests
        COMMAND happy_tests
    )
endif()

