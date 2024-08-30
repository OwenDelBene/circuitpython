# This top-level micropython.cmake is responsible for listing
# the individual modules we want to include.
# Paths are absolute, and ${CMAKE_CURRENT_LIST_DIR} can be
# used to prefix subdirectories.

# Add the C example.
include(${CMAKE_CURRENT_LIST_DIR}/cexample/micropython.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/sqlite/micropython.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/lora_c_module/micropython.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/structures/micropython.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/c_aes/micropython.cmake)

#include(${CMAKE_CURRENT_LIST_DIR}/cppexample/micropython.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Igrf/micropython.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/PSA/micropython.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/C_ADCS/micropython.cmake)
