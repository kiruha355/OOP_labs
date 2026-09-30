find_package(GTest CONFIG REQUIRED)

add_executable(array_tests
    test_variant.cpp
    ../src/array_ops.cpp
)

target_include_directories(array_tests PRIVATE ../include)
target_link_libraries(array_tests PRIVATE GTest::gtest_main)

if(WIN32)
    add_custom_command(TARGET array_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:GTest::gtest>
            $<TARGET_FILE:GTest::gtest_main>
            $<TARGET_FILE_DIR:array_tests>
    )
endif()

include(GoogleTest)
gtest_discover_tests(array_tests)
