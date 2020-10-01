set(UI_FORMS_DIR ui_forms)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_FORMS_DIR})

set(SOURCE_FILES
        main_window.h main_window.cpp ${UI_FORMS_DIR}/main_window.ui
        game_dimensions_dialog_window.h game_dimensions_dialog_window.cpp ${UI_FORMS_DIR}/game_dimensions_dialog_window.ui
        end_game_dialog.h end_game_dialog.cpp
        field_button.h field_button.cpp
        gui_config.h)

add_library(lib${PROJECT_NAME}Frontend ${SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Frontend PUBLIC ${BACKEND_DIR})
target_link_libraries(lib${PROJECT_NAME}Frontend PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
