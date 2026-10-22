find_package(GTest CONFIG REQUIRED)

add_executable(string_tests
    test_variant.cpp
    ../src/string.cpp
)

target_include_directories(string_tests PRIVATE ../include)
target_link_libraries(string_tests PRIVATE GTest::gtest_main)

if(WIN32)
    add_custom_command(TARGET string_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:GTest::gtest>
            $<TARGET_FILE:GTest::gtest_main>
            $<TARGET_FILE_DIR:string_tests>
    )
endif()

include(GoogleTest)
gtest_discover_tests(string_tests)
