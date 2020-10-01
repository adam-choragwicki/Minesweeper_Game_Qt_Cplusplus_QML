set(TEST_SOURCES
        src/main.cpp
        src/field_manager_test.cpp
        src/field_test.cpp
        src/field_uncoverer_test.cpp
        src/minefield_test.cpp
        src/mines_generation_test.cpp)

add_subdirectory(googletest)

add_executable(${PROJECT_NAME}Test_run src/main.cpp ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}Test_run PRIVATE inc)
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest lib${PROJECT_NAME}Backend)
