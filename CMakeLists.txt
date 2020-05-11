# Parts of this CMakeLists.txt is derived from the files of the tpie project.

cmake_minimum_required(VERSION 3.8)
project (coom
  VERSION 0.1
  DESCRIPTION "Cache-Oblivious OBDD Manipulation"
)

# ============================================================================ #
# Compiler settings
# ============================================================================ #
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-O2 ${CMAKE_C_FLAGS}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O2 ${CMAKE_CXX_FLAGS}")

# ============================================================================ #
# Common Dependencies
# ============================================================================ #
add_subdirectory (external/tpie tpie)

# ============================================================================ #
# Core project
# ============================================================================ #
option(COOM_SHARED "Build coom as a shared library" OFF)
option(COOM_DEBUG "Build coom with debug information" ON)

add_subdirectory (src)

# ============================================================================ #
# Test Files
# ======================================2====================================== #
option(COMPILE_TEST "Build coom unit tests" ON)
if (COMPILE_TEST)
  # enable_testing() # No need, as we use Bandit
  add_subdirectory (test)
endif()
