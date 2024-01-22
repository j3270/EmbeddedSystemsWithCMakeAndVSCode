# Call Cmake from the 'build' subfolder with the command below.
# For using Make:
# cmake -DCMAKE_MAKE_PROGRAM=make.exe -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-gcc.cmake" -G "Unix Makefiles" ..
# followed by
# 'make' or 'cmake --build .' to build it
#
# For using Ninja:
# cmake -DCMAKE_MAKE_PROGRAM=ninja.exe -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-gcc.cmake" -G "Ninja" ..
# followed by
# 'ninja' or 'cmake --build .' to build it

if (NOT DEFINED ENV{ARM_NONE_EABI_TOOLCHAIN})
	message(FATAL_ERROR "ARM_NONE_EABI_TOOLCHAIN environment variable is not defined!")
endif()

find_program(CMAKE_ASM_COMPILER arm-none-eabi-gcc PATHS "$ENV{ARM_NONE_EABI_TOOLCHAIN}/bin" NO_DEFAULT_PATH)
find_program(CMAKE_C_COMPILER arm-none-eabi-gcc PATHS "$ENV{ARM_NONE_EABI_TOOLCHAIN}/bin" NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER arm-none-eabi-g++ PATHS "$ENV{ARM_NONE_EABI_TOOLCHAIN}/bin" NO_DEFAULT_PATH)
find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy PATHS "$ENV{ARM_NONE_EABI_TOOLCHAIN}/bin" NO_DEFAULT_PATH)
find_program(CMAKE_SIZE_UTIL arm-none-eabi-size PATHS "$ENV{ARM_NONE_EABI_TOOLCHAIN}/bin" NO_DEFAULT_PATH)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
