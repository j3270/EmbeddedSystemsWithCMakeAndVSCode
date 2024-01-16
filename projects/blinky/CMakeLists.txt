cmake_minimum_required(VERSION 3.0.0)
project(blinky VERSION 0.1.0)


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
)

set(INCLUDE_DIRS 
        ${CMAKE_CURRENT_SRC_DIR}
        ${CMAKE_CURRENT_SRC_DIR}cmsis/include
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.51.0/sam0/utils/cmsis/samd21/include
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.51.0/sam0/utils/cmsis/samd21/include/component
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.51.0/sam0/utils/cmsis/samd21/include/instance
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.51.0/sam0/utils/cmsis/samd21/include/pio
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.51.0/thirdparty/CMSIS/Include
        ${CMAKE_CURRENT_SRC_DIR}../../xdk-asf-3.51.0/thirdparty/CMSIS/Lib/GCC 
)

set(DEFINES 
        -D__SAMD21
        -D__SAMD21J18A__
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

set(EXECUTABLE blinky.elf)

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

target_link_libraries(${EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../../xdk-asf-3.51.0/thirdparty/CMSIS/Lib/GCC/libarm_cortexM0l_math.a)

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