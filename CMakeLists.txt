cmake_minimum_required(VERSION 3.12)
project(Genus)

set(GENUS_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/GameState
        ${PROJECT_SOURCE_DIR}/src/GameState/Playfields
        ${PROJECT_SOURCE_DIR}/src/GameState/Powerups
        ${PROJECT_SOURCE_DIR}/src/GameState/PauseModal
        ${PROJECT_SOURCE_DIR}/src/GameOverState
        ${PROJECT_SOURCE_DIR}/src/HighScoresState
        ${PROJECT_SOURCE_DIR}/src/MainMenuState
        ${PROJECT_SOURCE_DIR}/src/MainOptionsState
        ${PROJECT_SOURCE_DIR}/src/SplashState
        ${PROJECT_SOURCE_DIR}/src/RulesState
        ${PROJECT_BINARY_DIR}/usr/local/include
)

file(GLOB_RECURSE GENUS_SRC CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(Genus ${GENUS_SRC})
set_target_properties(Genus PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES)
target_include_directories(Genus PRIVATE ${GENUS_INCLUDE_DIRS})
target_compile_definitions(Genus PRIVATE CE_SDL2_WINDOW_TITLE="Genus :: by Modus Create")

include("${PROJECT_SOURCE_DIR}/creative-engine/CreativeEngine.cmake")
creative_engine_attach(Genus RESOURCE_ARCHIVE "${PROJECT_SOURCE_DIR}/src/Resources.zip")

if (EMSCRIPTEN)
    include(cmake/GenusWeb.cmake)
elseif (WIN32)
    install(TARGETS Genus RUNTIME DESTINATION ".")
    install(FILES "$<TARGET_FILE:SDL2::SDL2>" DESTINATION ".")
else ()
    compile_rcomp_and_resources()
    # The legacy compiler writes into src, while the engine's assembler reads from the build directory.
    add_custom_command(OUTPUT Resources.bin APPEND
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${PROJECT_SOURCE_DIR}/src/Resources.bin" "${PROJECT_BINARY_DIR}/Resources.bin"
    )
    set_source_files_properties("${CREATIVE_ENGINE_PATH}/src/BResourceManager.cpp"
            PROPERTIES OBJECT_DEPENDS "${PROJECT_BINARY_DIR}/Resources.bin"
    )
    target_sources(Genus PRIVATE "${PROJECT_BINARY_DIR}/Resources.bin")

    if (APPLE)
        set_target_properties(Genus PROPERTIES MACOSX_BUNDLE TRUE
                XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Developer ID Application: Modus Create, Inc.")
        install(TARGETS Genus DESTINATION ".")
    endif ()
endif ()
