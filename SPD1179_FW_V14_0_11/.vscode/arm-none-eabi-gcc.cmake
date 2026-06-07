set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER "arm-none-eabi-gcc.exe")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc.exe")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++.exe")

set(CMAKE_OBJCOPY "arm-none-eabi-objcopy.exe" CACHE INTERNAL "objcopy tool")
set(CMAKE_SIZE_UTIL "arm-none-eabi-size.exe" CACHE INTERNAL "size tool")


set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)