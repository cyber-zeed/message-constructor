cmake_minimum_required(VERSION 3.16)
project(message_constructor LANGUAGES CXX)

add_library(message_constructor INTERFACE)
target_include_directories(message_constructor INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_features(message_constructor INTERFACE cxx_std_11)

option(MESSAGE_CONSTRUCTOR_BUILD_TESTS "Build native tests" ON)
if(MESSAGE_CONSTRUCTOR_BUILD_TESTS)
    enable_testing()
    add_executable(message_constructor_tests tests/test_message_constructor.cpp)
    target_link_libraries(message_constructor_tests PRIVATE message_constructor)
    add_test(NAME message_constructor_tests COMMAND message_constructor_tests)
endif()
