find_package(GTest CONFIG REQUIRED)

add_executable(phone_tests
    test_variant.cpp
    ../src/phone.cpp
)

target_include_directories(phone_tests PRIVATE ../include)
target_link_libraries(phone_tests PRIVATE GTest::gtest_main)

if(WIN32 AND TARGET GTest::gtest AND TARGET GTest::gtest_main)
    get_target_property(gtest_type GTest::gtest TYPE)
    if(gtest_type STREQUAL "SHARED_LIBRARY")
        add_custom_command(TARGET phone_tests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:GTest::gtest>
                $<TARGET_FILE:GTest::gtest_main>
                $<TARGET_FILE_DIR:phone_tests>
        )
    endif()
endif()

include(GoogleTest)
gtest_discover_tests(phone_tests)
