# Find GTest package
find_package(GTest REQUIRED)

# Add test executable
add_executable(engine_tests
    main.cpp
    engine_test.cpp
)

# Link against GTest and our engine library
target_link_libraries(engine_tests
    PRIVATE
        GTest::GTest
        GTest::Main
        engine_lib
)

# Add tests to CTest
add_test(NAME engine_tests COMMAND engine_tests) 