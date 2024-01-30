
set(CMAKE_ASM_FLAGS_DEBUG "\
    ${CMAKE_ASM_FLAGS}\
    -DDEBUG\
    -D__STARTUP_CLEAR_BSS\
    -g\
    -Wall\
    -mthumb\
    -fno-common\
    -ffunction-sections\
    -fdata-sections\
    -ffreestanding\
    -fno-builtin\
    -mapcs\
    -std=gnu99\
")

set(CMAKE_ASM_FLAGS_RELEASE "\
    ${CMAKE_ASM_FLAGS}
")

set(CMAKE_ASM_FLAGS_MINSIZEREL "\
    ${CMAKE_ASM_FLAGS}
")

set(CMAKE_ASM_FLAGS_RELWITHDEBINFO "\
    ${CMAKE_ASM_FLAGS}
")

set(CMAKE_C_FLAGS_DEBUG "\
    ${CMAKE_C_FLAGS_DEBUG}\
    -DDEBUG\
    -O0\
    -mthumb\
    -MMD\
    -MP\
    -fno-common\
    -ffunction-sections\
    -fdata-sections\
    -ffreestanding\
    -fno-builtin\
    -mapcs\
    -std=gnu99\
")

set(CMAKE_C_FLAGS_RELEASE "\
    ${CMAKE_C_FLAGS}\
")

set(CMAKE_C_FLAGS_MINSIZEREL "\
    ${CMAKE_C_FLAGS}\
")

set(CMAKE_C_FLAGS_RELWITHDEBINFO "\
    ${CMAKE_C_FLAGS}\
")

set(CMAKE_CXX_FLAGS_DEBUG "\
    ${CMAKE_CXX_FLAGS}\
    -DDEBUG\
    -O0\
    -Wall\
    -mthumb\
    -MMD\
    -MP\
    -fno-common\
    -ffunction-sections\
    -fdata-sections\
    -ffreestanding\
    -fno-builtin\
    -mapcs\
    -fno-rtti\
    -fno-exceptions\
")

set(CMAKE_CXX_FLAGS_RELEASE "\
    ${CMAKE_CXX_FLAGS}\
")

set(CMAKE_CXX_FLAGS_MINSIZEREL "\
    ${CMAKE_CXX_FLAGS}\
")

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "\
    ${CMAKE_CXX_FLAGS}\
")

set(CMAKE_EXE_LINKER_FLAGS_DEBUG "\
    ${CMAKE_EXE_LINKER_FLAGS}\
    -g\
    -Wall\
    --specs=nano.specs\
    --specs=nosys.specs\
    -fno-common\
    -ffunction-sections\
    -fdata-sections\
    -ffreestanding\
    -fno-builtin\
    -mthumb\
    -mapcs\
    -Xlinker\
    --gc-sections\
    -Xlinker\
    -static\
    -Xlinker\
    -z\
    -Xlinker\
    muldefs\
")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE  "\
    ${CMAKE_EXE_LINKER_FLAGS}\
")

set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "\
    ${CMAKE_EXE_LINKER_FLAGS}\
")

set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "\
    ${CMAKE_EXE_LINKER_FLAGS}\
")
