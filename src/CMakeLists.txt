set(SOURCE_FILES
        # Core application & coordination
        game.cpp
        game.h
        controller.cpp
        controller.h
        game_coordinator.cpp
        game_coordinator.h

        # State machine
        state_machine/abstract_state.h
        state_machine/game_state_manager.h
        state_machine/game_state_type.h
        state_machine/i_state_actions.h

        state_machine/states/initialization_state.h
        state_machine/states/ready_to_start_state.h
        state_machine/states/running_state.h
        state_machine/states/escape_menu_state.h
        state_machine/states/ended_victory_state.h
        state_machine/states/ended_defeat_state.h

        # Game configuration
        config/game_config.h
        config/minefield_parameters.h
        game_result.h

        # Model
        model/model.cpp
        model/model.h
        model/tiles_model.cpp
        model/tiles_model.h

        # Assets & audio
        asset_management/asset_loader.cpp
        asset_management/asset_loader.h
        asset_management/asset_repository.h

        sound_player.h

        # Other
        log_manager.cpp
        log_manager.h
        input_handler.cpp
        input_handler.h
        overlay_manager.cpp
        overlay_manager.h
        window_manager.cpp
        window_manager.h
        qml_helper.h

        tile.cpp
        tile.h
        tile_state_manager.h

        coordinates.cpp
        coordinates.h
        coordinates_validator.h

        minefield.cpp
        minefield.h
        mines_generator.cpp
        mines_generator.h

        tiles_manager.cpp
        tiles_manager.h
        tiles_uncoverer.cpp
        tiles_uncoverer.h
)

add_library(${PROJECT_NAME}Backend ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME}Backend PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}Backend PUBLIC Qt6::Core Qt6::Quick Qt6::Multimedia)

target_compile_definitions(${PROJECT_NAME}Backend PRIVATE
        APP_VERSION="${PROJECT_VERSION}"
        BUILD_TYPE="$<CONFIG>"
)

qt_add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Backend MinesweeperQmlLibplugin)

qt_add_resources(${PROJECT_NAME}
        PREFIX /
        FILES "../assets/resources.qrc"
)

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>) # this avoids opening console window on Windows in Release mode
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # Set the output directory for the executable
