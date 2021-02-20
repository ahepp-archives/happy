add_library(
happy
    Drv2605.cpp
    Debouncer.cpp
    EdgeDetector.cpp
    PulsePlayer.cpp
    PulseRecorder.cpp
)

target_include_directories(
happy
    PUBLIC
        ${HAPPY_ROOT_DIR}/include
)
