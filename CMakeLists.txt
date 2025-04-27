cmake_minimum_required(VERSION 3.10.0)
project(NPSLib VERSION 0.1.0 LANGUAGES C CXX)

# Add the NPS_Pack implementation file to the library
add_library(NPSLib NPSLib.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Ensure the test executable is built and linked correctly
add_executable(test_library test.cpp)
target_link_libraries(test_library PRIVATE NPSLib)

# Register individual tests with CTest
add_test(NAME TestSayHello COMMAND test_library test_say_hello)
add_test(NAME TestPack COMMAND test_library test_pack)
add_test(NAME TestUnpack COMMAND test_library test_unpack)
