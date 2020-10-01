set(SOURCE_FILES
        model/model.h model/model.cpp
        model/field.h model/field.cpp
        common.h
        coordinates.h coordinates.cpp
        model/minefield.h model/minefield.cpp
        fields_manager.h fields_manager.cpp
        mines_generator.h mines_generator.cpp
        fields_uncoverer.h fields_uncoverer.cpp)

add_library(lib${PROJECT_NAME}Backend ${SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Backend PUBLIC .)
target_link_libraries(lib${PROJECT_NAME}Backend PUBLIC Qt${QT_VERSION_MAJOR}::Core)
