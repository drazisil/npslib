cmake_minimum_required(VERSION 3.10.0)
project(NPSLib VERSION 0.1.0 LANGUAGES C CXX)

add_library(NPSLib NPSLib.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Ensure the test executable is built and linked correctly
add_executable(test_library test.cpp)
target_link_libraries(test_library PRIVATE NPSLib)

# Register the test executable with CTest
add_test(NAME TestLibrary COMMAND test_library)
