set(TESTS_NAME segment_tree_tests)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
            -g
            -O0
            -march=native
            -fconcepts-diagnostics-depth=3
    )
else()
    add_compile_options(
            -O3
            -march=native
            -Wno-error=maybe-uninitialized #Google Tests complains if not
    )
endif()
add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)

find_package(GTest REQUIRED)
if(GTest_FOUND)
    message(STATUS "TESTS FOUND: including and linking...")
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    message(STATUS "NOT FOUND GTest")
endif()

add_executable(${TESTS_NAME}
        ./tests_basic_functionality.cpp
        ./tests_user_defined_data_type.cpp
        ./tests_random_test.cpp
        ./main.cpp
)
target_compile_definitions(${TESTS_NAME} PUBLIC CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
target_link_libraries(${TESTS_NAME}
        GTest::GTest
        pthread
)
target_compile_options(${TESTS_NAME}
        PRIVATE
        -fsanitize=address -g -fno-omit-frame-pointer -fno-optimize-sibling-calls
        -fsanitize=undefined -g -fno-omit-frame-pointer
)
target_link_options(${TESTS_NAME}
        PRIVATE
        -fsanitize=address
        -fsanitize=undefined
)