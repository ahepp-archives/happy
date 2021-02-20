add_executable(
pico_happy
    main.cpp
    PicoDin.cpp
    PicoDout.cpp
    PicoI2c.cpp
    PicoMsTimer.cpp
)

target_link_libraries(
pico_happy
    pico_stdlib
    pico_stdio_usb
    hardware_i2c
    happy
)

pico_add_extra_outputs(pico_happy)
pico_set_binary_type(pico_happy no_flash)

