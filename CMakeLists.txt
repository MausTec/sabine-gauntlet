cmake_minimum_required(VERSION 3.8)
set(PROJECT_NAME GauntletControl)
set(AUTO_SET_SKETCHBOOK_PATH true)

project(${PROJECT_NAME})
arduino_cmake_project(${PROJECT_NAME} BOARD_NAME diecimila BOARD_CPU atmega328)

### Main sketch file
add_arduino_executable(${PROJECT_NAME} GauntletControl.cpp)
target_sources(${PROJECT_NAME}
    PUBLIC
        src/lcd.cpp
        src/RTC.cpp
        src/PS2Keyboard.cpp
        src/Settings.cpp
        src/freeMemory.cpp
        src/Pages.cpp
        src/Transmitter.cpp
        src/UserInterface.cpp
        src/Aurebesh.cpp
        src/Buttons.cpp
        src/ShiftRegister.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        app
        include
)

# 3rd Party Libs
find_arduino_library(rtc_lib RTClib)
link_arduino_library(${PROJECT_NAME} rtc_lib)

find_arduino_library(thread_lib ArduinoThread)
link_arduino_library(${PROJECT_NAME} thread_lib)

find_arduino_library(eeprom_lib EEPROM HEADER_ONLY)
link_arduino_library(${PROJECT_NAME} eeprom_lib HEADER_ONLY)

find_arduino_library(onebtn_lib OneButton)
link_arduino_library(${PROJECT_NAME} onebtn_lib)

# Upload:
set_target_upload_port(${PROJECT_NAME} COM5)