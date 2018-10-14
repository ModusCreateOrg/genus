cmake_minimum_required(VERSION 3.12)
project(genus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-exception-spec-mismatch")
set(CMAKE_VERBOSE_MAKEFILE ON)
# resource compiler
set(RCOMP "${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/tools/rcomp")

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/src ${CMAKE_BINARY_DIR} /usr/local/include)

# external libraries
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

# Create softlink to creative-engine
add_custom_command(
        OUTPUT creative-engine
        COMMAND rm -f ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine && ln -sn ${CMAKE_CURRENT_SOURCE_DIR}/../creative-engine ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine
        COMMENT "Creating softlink"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine
)

# build rcomp
add_custom_command(OUTPUT rcomp
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/tools && make
        OUTPUTS rcomp
        COMMENT "Building rcomp")

# build Resources.bin
add_custom_command(OUTPUT Resources.bin
        #        COMMAND ls ${RCOMP}
        COMMAND @echo
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/src && ${RCOMP} Resources.r
        OUTPUTS Resources.bin
        DEPENDS rcomp
        COMMENT "Compiling Resources ${CMAKE_CURRENT_SOURCE_DIR} ")

# gather creative-engine sources
file(GLOB_RECURSE LIB RELATIVE ${CMAKE_SOURCE_DIR} "creative-engine/src/*.cpp")


add_executable(genus
        rcomp
        Resources.bin
        ${LIB}
        src/main.cpp
        src/GPlayfield.cpp
        src/GGameEngine.cpp
        README.md creative-engine/src/BFont.cpp creative-engine/src/BFont.h src/GSplashState.cpp src/GSplashState.h src/GMainMenuState.cpp src/GMainMenuState.h src/GGameState.cpp src/GGameState.h src/GGameOverState.cpp src/GGameOverState.h src/GEnterHighScoreState.cpp src/GEnterHighScoreState.h src/GHighScoresState.cpp src/GHighScoresState.h src/GMainOptionsState.cpp src/GMainOptionsState.h src/GCreditsState.cpp src/GCreditsState.h)


# make genus.app
if(APPLE)
        set(CMAKE_MACOSX_RPATH 1)
        set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}")
        SET_TARGET_PROPERTIES(genus PROPERTIES MACOSX_BUNDLE TRUE)
        INSTALL(TARGETS genus DESTINATION ".")
endif(APPLE)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} -L/usr/local/lib ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
#target_link_libraries(${GAME_ENGINE})






