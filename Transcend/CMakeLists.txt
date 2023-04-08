cmake_minimum_required(VERSION 3.16)

# Use `ccache` if it is installed in system's PATH.
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# Export compilation database in JSON format.
set( CMAKE_EXPORT_COMPILE_COMMANDS on )

project(TSC)

add_executable(
    tsc
    src/TSC.cpp
    src/main.cpp
)

target_include_directories(
  tsc
  PUBLIC src/
)