set(GOOGLETEST_VERSION 1.17.0)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()

add_subdirectory(googletest)

set(TEST_SOURCES
        src/tiles_manager_test.cpp
        src/tile_test.cpp
        src/tiles_uncoverer_test.cpp
        src/minefield_test.cpp
        src/mines_generation_test.cpp)

add_executable(${PROJECT_NAME}Test_run ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}Test_run PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest_main ${PROJECT_NAME}Backend)
