
include(${CMAKE_CURRENT_SOURCE_DIR}/../tools/cmake_files/utils.cmake)
CheckBuildType()
OutputBuildConfigFlags(${CMAKE_CURRENT_SOURCE_DIR}/../tools/cmake_files/gccFlags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../tools/cmake_files/gccFlags.cmake)

add_subdirectory(blinky)
add_subdirectory(blinky_asf)
add_subdirectory(helloworld_asf)
add_subdirectory(I2C_Scan_Bus)
add_subdirectory(read_pot_asf)
add_subdirectory(SeggerRttPrintfTest)
