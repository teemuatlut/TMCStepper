cmake_minimum_required(VERSION 3.12)

set(LIB_TMCSTEPPER_PATH "../..")

include(pico_sdk_import.cmake)

project(RPi2040_Native C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

file(GLOB_RECURSE TMCStepper_source ${LIB_TMCSTEPPER_PATH}/src/*.cpp)
add_library(TMCStepper ${TMCStepper_source})
target_link_libraries(
        TMCStepper
        pico_stdlib
        hardware_spi
        )
        
file(GLOB PROJECT_FILES *.cpp)
add_executable(RPi2040_Native ${PROJECT_FILES})
target_link_libraries(
        RPi2040_Native
        # pico_stdlib
        TMCStepper
)
target_include_directories(
        RPi2040_Native PRIVATE
        ${LIB_TMCSTEPPER_PATH}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(RPi2040_Native)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        -fmax_errors=2
        )
