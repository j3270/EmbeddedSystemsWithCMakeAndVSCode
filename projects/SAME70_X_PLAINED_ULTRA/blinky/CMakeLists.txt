cmake_minimum_required(VERSION 3.0.0)
project(same70_x_plained_ultra_blinky VERSION 0.1.0)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
        include(CTest)
        enable_testing()
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/../../../tools/cmake_files/utils.cmake)
CheckBuildType()
OutputBuildConfigFlags(${CMAKE_CURRENT_SOURCE_DIR}/../../../tools/cmake_files/gccFlags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../../tools/cmake_files/gccFlags.cmake)

set(ASSEMBLY_FILES 
)
list(APPEND SOURCES ${ASSEMBLY_FILES})

# CMSIS src files
set(CMSIS_SOURCES
        ${CMAKE_CURRENT_SRC_DIR}cmsis/source/gcc/startup_same70.c
        ${CMAKE_CURRENT_SRC_DIR}cmsis/source/gcc/system_same70.c
)
list(APPEND SOURCES ${CMSIS_SOURCES})

# ASF src files
set(ASF_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/chipid/chipid.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/pio/pio.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/pio/pio_handler.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/uart/uart.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/usart/usart.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/wdt/wdt.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/utils/syscalls/gcc/syscalls.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/clock/same70/sysclk.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/serial/usart_serial.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/utils/stdio/read.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/utils/stdio/write.c
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/utils/interrupt/interrupt_sam_nvic.c
)
list(APPEND SOURCES ${ASF_SOURCES})

set(APP_SOURCES 
        ${CMAKE_CURRENT_SRC_DIR}main.cpp
)
list(APPEND SOURCES ${APP_SOURCES})

# Compiler inc files
set(COMPILER_INCLUDES
   $ENV{ARM_NONE_EABI_TOOLCHAIN}/lib/gcc/arm-none-eabi/10.3.1/include
   $ENV{ARM_NONE_EABI_TOOLCHAIN}/lib/gcc/arm-none-eabi/include
   $ENV{ARM_NONE_EABI_TOOLCHAIN}/lib/gcc/arm-none-eabi/10.3.1/include-fixed
   $ENV{ARM_NONE_EABI_TOOLCHAIN}/lib/gcc/arm-none-eabi/include/c++/10.3.1
)
list(APPEND INCLUDE_DIRS ${COMPILER_INCLUDES})

# ASF inc files
set(ASF_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/config
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/rstc/example1
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/boards
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/utils/header_files
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/utils/preprocessor
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/thirdparty/CMSIS/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/thirdparty/CMSIS/Lib/GCC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/utils/fpu
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/utils/cmsis/same70/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/utils/cmsis/same70/source/templates
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/boards/user_board
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/storage/ctrl_access
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/afec
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/chipid
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/dacc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/ebi/smc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/efc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/gmac
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/gpbr
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/matrix
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/mcan
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/pio
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/pmc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/pwm
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/rstc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/rtc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/rtt
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/supc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/tc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/twihs
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/uart
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/services/flash_efc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/clock
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/gpio
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/ioport
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/serial/sam_uart
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/serial
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/sleepmgr
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/spi/sam_spi
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/spi
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/spi/sam_usart_spi
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/services/twi
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/common/utils/stdio/stdio_serial
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/qspi
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/spi
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/usart
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/wdt
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/xdmac
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/sam/drivers/mpu
)
list(APPEND INCLUDE_DIRS ${ASF_INCLUDES})


set(DEFINES 
        -D__SAME70Q21B__
        -DBOARD=SAME70_XPLAINED_ULTRA
)

set(CPU_FLAGS
        -mcpu=cortex-m7
)

set(FPU_FLAGS 
        -mfloat-abi=hard
        -mfpu=auto
)

set(CMAKE_CXX_COMPILE_OBJECT "${CMAKE_CXX_COMPILE_OBJECT} -Wa,-alhn=<OBJECT>.lst")
set(CMAKE_C_COMPILE_OBJECT "${CMAKE_C_COMPILE_OBJECT} -Wa,-alhn=<OBJECT>.lst")


set(EXECUTABLE "${PROJECT_NAME}.elf")

add_executable(${EXECUTABLE} ${SOURCES} ${ASSEMBLY_FILES})


target_include_directories(${EXECUTABLE} PRIVATE ${INCLUDE_DIRS})

target_compile_definitions(${EXECUTABLE} PRIVATE ${DEFINES})

target_compile_options(${EXECUTABLE} PRIVATE 
        ${CPU_FLAGS} 
        ${FPU_FLAGS})

target_link_options(${EXECUTABLE} PRIVATE  
        ${CPU_FLAGS} 
        ${FPU_FLAGS} 
        -Xlinker
        -Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map
        -Wl,--print-memory-usage
        -T ${CMAKE_CURRENT_SOURCE_DIR}/cmsis/flash.ld)

target_link_libraries(${EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../../../xdk-asf-3.52.0/thirdparty/CMSIS/Lib/GCC/libarm_cortexM7lfdp_math.a)

#Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE})

# Optional: Create hex, bin and S-Record files after the build
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len=64 ${EXECUTABLE} ${PROJECT_NAME}.s19
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)