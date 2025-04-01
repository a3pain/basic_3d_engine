# Find GTest package
find_package(GTest REQUIRED)

# Add test executable
add_executable(engine_tests
    main.cpp
)

# Link against GTest and our engine
target_link_libraries(engine_tests
    PRIVATE
        GTest::GTest
        GTest::Main
        ${PROJECT_NAME}
)

# Add tests to CTest
add_test(NAME engine_tests COMMAND engine_tests) 