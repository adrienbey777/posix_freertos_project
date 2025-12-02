cmake_minimum_required(VERSION 3.20)
project(posix_freertos_demo)

# Enable debug mode
set(CMAKE_BUILD_TYPE Debug)

# Main directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(FREERTOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../FreeRTOS-Kernel)

# Include directories
include_directories(
    ${SRC_DIR}                                      # src/ folder
    ${INC_DIR}                                      # inc/ folder 
    ${FREERTOS_DIR}/include                         # FreeRTOS includes
    ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix
    ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/utils
)

# List all source files
file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/*.c
    ${FREERTOS_DIR}/tasks.c
    ${FREERTOS_DIR}/queue.c
    ${FREERTOS_DIR}/list.c
    ${FREERTOS_DIR}/timers.c
    ${FREERTOS_DIR}/event_groups.c
    ${FREERTOS_DIR}/portable/MemMang/heap_3.c   
    ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
    ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/port.c
)

# Create the executable
add_executable(main ${SOURCES})

# Compilation options
target_compile_options(main PRIVATE -ggdb3)
target_compile_definitions(main PRIVATE BUILD_DIR="${CMAKE_BINARY_DIR}")

# Linker options
target_link_libraries(main PRIVATE pthread)
