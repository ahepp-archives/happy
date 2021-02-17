add_library(
happy
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
