cmake_minimum_required(VERSION 3.0.0)
project(blinky_same70_x_plained_ultra VERSION 0.1.0)

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

set(SOURCES 
        ${CMAKE_CURRENT_SRC_DIR}main.cpp
        ${CMAKE_CURRENT_SRC_DIR}cmsis/source/gcc/startup_same70.c
        ${CMAKE_CURRENT_SRC_DIR}cmsis/source/gcc/system_same70.c
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/common/utils/interrupt/interrupt_sam_nvic.c
)

set(INCLUDE_DIRS 
        ${CMAKE_CURRENT_SRC_DIR}
        ${CMAKE_CURRENT_SRC_DIR}cmsis/include
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/common/boards
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/common/utils
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/common/utils/interrupt
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/common2/services/delay
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/sam/utils
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/sam/utils/cmsis/same70/include
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/sam/utils/fpu
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/sam/utils/header_files
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/sam/utils/preprocessor
        ${CMAKE_CURRENT_SRC_DIR}../../../xdk-asf-3.52.0/thirdparty/CMSIS/Include
)

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


set(EXECUTABLE blinky_SAME70.elf)

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