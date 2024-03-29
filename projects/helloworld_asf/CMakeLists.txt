cmake_minimum_required(VERSION 3.0.0)
project(HelloWorld_asf VERSION 0.1.0)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
        include(CTest)
	enable_testing()
	
	include(${CMAKE_CURRENT_SOURCE_DIR}/../../tools/cmake_files/utils.cmake)
	CheckBuildType()
	OutputBuildConfigFlags(${CMAKE_CURRENT_SOURCE_DIR}/../../tools/cmake_files/gccFlags.cmake)
	include(../../tools/cmake_files/gccFlags.cmake)
endif()

set(ASSEMBLY_FILES 
)

set(SOURCES 
        ${CMAKE_CURRENT_SRC_DIR}main.cpp
        ${CMAKE_CURRENT_SRC_DIR}cmsis/source/gcc/startup_samd21.c
        ${CMAKE_CURRENT_SRC_DIR}cmsis/source/gcc/system_samd21.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/common/utils/interrupt/interrupt_sam_nvic.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/common2/services/delay/sam0/systick_counter.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/boards/samd21_xplained_pro/board_init.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/port/port.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/sercom/sercom.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/sercom/usart/usart.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/system.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/pinmux/pinmux.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/interrupt/system_interrupt.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/clock/clock_samd21_r21_da_ha1/clock.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/clock/clock_samd21_r21_da_ha1/gclk.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/stdio/read.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/stdio/write.c
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/syscalls/gcc/syscalls.c
)

set(INCLUDE_DIRS 
        ${CMAKE_CURRENT_SRC_DIR}
        ${CMAKE_CURRENT_SRC_DIR}cmsis/include
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/common/boards
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/common/services/serial
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/common/utils
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/common/utils/interrupt
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/common2/services/delay
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/common2/services/delay/sam0
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/boards
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/boards/samd21_xplained_pro
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/boards/samd21_xplained_pro/board_config
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/port
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/sercom
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/sercom/usart
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/clock
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/clock/clock_samd21_r21_da_ha1
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/clock/clock_samd21_r21_da_ha1/module_config
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/interrupt
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/interrupt/system_interrupt_samd21
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/pinmux
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/power/power_sam_d_r_h
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/drivers/system/reset/reset_sam_d_r_h
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/cmsis/samd21/include
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/cmsis/samd21/include/component
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/cmsis/samd21/include/instance
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/cmsis/samd21/include/pio
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/cmsis/samd21/source
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/header_files
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/preprocessor
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/sam0/utils/stdio/stdio_serial  
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/thirdparty/CMSIS/Include
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.52.0/thirdparty/CMSIS/Lib/GCC 
)

set(DEFINES 
        -D__SAMD21J18A__
        -DBOARD=SAMD21_XPLAINED_PRO
        -DSYSTICK_MODE
)

set(CPU_FLAGS
        -mcpu=cortex-m0plus
)

set(FPU_FLAGS 
        -mfloat-abi=soft
        -mfpu=auto
)

set(CMAKE_CXX_COMPILE_OBJECT "${CMAKE_CXX_COMPILE_OBJECT} -Wa,-alhn=<OBJECT>.lst")
set(CMAKE_C_COMPILE_OBJECT "${CMAKE_C_COMPILE_OBJECT} -Wa,-alhn=<OBJECT>.lst")

set(EXECUTABLE HelloWorld_asf.elf)

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
        -T ${CMAKE_CURRENT_SOURCE_DIR}/cmsis/samd21j18a_flash.ld)

target_link_libraries(${EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../../xdk-asf-3.52.0/thirdparty/CMSIS/Lib/GCC/libarm_cortexM0l_math.a)

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