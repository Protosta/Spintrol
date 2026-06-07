cmake_minimum_required(VERSION 3.15.3)

# Optional: print out extra messages to see what is going on. Comment it to have less verbose messages
set(CMAKE_VERBOSE_MAKEFILE ON)

# Path to toolchain file. This one has to be before 'project()' below
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/../../../../.vscode/arm-none-eabi-gcc.cmake)

# Setup project, output and linker file
project(project)
set(EXECUTABLE ${PROJECT_NAME}.elf)
set(LINKER_FILE ${CMAKE_SOURCE_DIR}/project.ld)

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Optional: issue a message to be sure it uses the correct toolchain file.
message(STATUS "CMAKE_TOOLCHAIN_FILE is: ${CMAKE_TOOLCHAIN_FILE}")

# List of source files
set(SRC_FILES
        ${CMAKE_SOURCE_DIR}/../main.c
        ${CMAKE_SOURCE_DIR}/../isr.c
        ${CMAKE_SOURCE_DIR}/../meeprom_lib.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/adc.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/can.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/clock.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/comp.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/crc.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/dma.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/ecap.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/epwr.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/gpio.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/hwlib.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/i2c.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/pga.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/phcomp.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/pin.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/power.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/pwm.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/spd1179_hv.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/spi.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/system.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/timer.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/uart.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/src/wdt.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/CMSIS/device/system_spc1169.c
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/CMSIS/device/startup/gcc/startup_spc1169.S
        ${CMAKE_SOURCE_DIR}/../../../../Utilities/delay.c
        ${CMAKE_SOURCE_DIR}/../../../../Utilities/retarget.c
        )

# Build the executable based on the source files
add_executable(${EXECUTABLE} ${SRC_FILES})

# List of compiler defines, prefix with -D compiler option
target_compile_definitions(${EXECUTABLE} PRIVATE

        )

# List of includ directories
target_include_directories(${EXECUTABLE} PRIVATE
        ${CMAKE_SOURCE_DIR}/../
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/inc
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/drivers/inc/reg
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/CMSIS/core
        ${CMAKE_SOURCE_DIR}/../../../../Libraries/CMSIS/device
        ${CMAKE_SOURCE_DIR}/../../../../Utilities
        )

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -fdata-sections
        -ffunction-sections
        -Wall
        -O0
        -g3
        -DSPD1179
        )

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
        -T${LINKER_FILE}
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -specs=nano.specs
        -specs=nosys.specs
        -lc
        -lm
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        -Wl,--no-warn-rwx-segments
        -Xlinker -print-memory-usage -Xlinker
        )

# Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE})

# Optional: Create hex, bin and S-Record files after the build
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        # COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/project.elf  ${CMAKE_SOURCE_DIR}/../../../../.vscode/ )

add_custom_target(clean-all
        rm -rf CMakeFiles
        rm -rf CMakeCache.txt
        rm -rf cmake_install.cmake
        rm -rf Makefile
        rm -rf project.hex
        rm -rf project.map
        rm -rf project.elf
    )