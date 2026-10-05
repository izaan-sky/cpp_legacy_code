cmake_minimum_required(VERSION 3.21)
project(cpp_legacy_code)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS json)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

add_executable(cpp_legacy_code
        main.cpp
        src/OrderFetcher.cpp
        src/ShippingCalculator.cpp
        src/StandardShipping.hpp
        src/StandardShipping.cpp
        src/ExpressShipping.cpp
)

target_include_directories(cpp_legacy_code PRIVATE src)

target_link_libraries(cpp_legacy_code PRIVATE
        Boost::json
        OpenSSL::SSL
        OpenSSL::Crypto
        Threads::Threads
)

enable_testing()
add_executable(cpp_legacy_code_tests
        tests/ShippingCalculatorTest.cpp
        src/OrderFetcher.cpp
        src/ShippingCalculator.cpp
        src/StandardShipping.cpp)
target_link_libraries(cpp_legacy_code_tests PRIVATE
        Boost::json
        OpenSSL::SSL
        OpenSSL::Crypto
        Threads::Threads
        GTest::gtest_main)
target_include_directories(
        cpp_legacy_code_tests PRIVATE src
)

if (WIN32)
    target_compile_definitions(cpp_legacy_code PRIVATE _WIN32_WINNT=0x0601)
    target_link_libraries(cpp_legacy_code PRIVATE ws2_32 mswsock)
    target_link_options(cpp_legacy_code PRIVATE -static-libgcc -static-libstdc++ -static)

    add_custom_command(TARGET cpp_legacy_code POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Boost::json>
            $<TARGET_FILE:OpenSSL::SSL>
            $<TARGET_FILE:OpenSSL::Crypto>
            $<TARGET_FILE_DIR:cpp_legacy_code>
    )
endif ()

include(GoogleTest)
gtest_discover_tests(cpp_legacy_code_tests)
