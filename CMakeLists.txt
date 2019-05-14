CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(genus)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-exception-spec-mismatch")
#set(CMAKE_VERBOSE_MAKEFILE ON)

INCLUDE(FindPkgConfig)

# CMake Module path (additional cmake files via find_package)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake.files")

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_image REQUIRED)

INCLUDE_DIRECTORIES(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
)

# Creative Engine
FIND_PACKAGE(Creative-Engine REQUIRED)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/GameState
    ${CMAKE_SOURCE_DIR}/src/GameState/Playfields
    ${CMAKE_SOURCE_DIR}/src/GameState/Powerups
    ${CMAKE_SOURCE_DIR}/src/GameOverState
    ${CMAKE_SOURCE_DIR}/src/HighScoresState
    ${CMAKE_SOURCE_DIR}/src/MainMenuState
    ${CMAKE_SOURCE_DIR}/src/MainOptionsState
    ${CMAKE_SOURCE_DIR}/src/SplashState
    ${CMAKE_SOURCE_DIR}/src/RulesState
    ${CMAKE_BINARY_DIR}/usr/local/include
    ${CREATIVE_ENGINE_INCLUDE_DIRS}
)


## JG: Commented this out because it broke debugging.
# include creative-engine sources
# when using out-of-tree source paths add_subdirectory's build_dir argument is required
# use the project's current build directory
# https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html
# https://cmake.org/cmake/help/latest/command/add_subdirectory.html
# https://stackoverflow.com/questions/35260552/how-do-i-explicitly-specify-an-out-of-tree-source-in-cmake
#add_subdirectory(${CREATIVE_ENGINE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/creative-engine)


# gather Genus sources
FILE(GLOB_RECURSE GENUS_SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

ADD_EXECUTABLE(
    ${PROJECT_NAME}
    Resources.bin
    ${CREATIVE_ENGINE_SOURCE_FILES}
    ${GENUS_SRC}
)

# make genus.app
if (APPLE)
    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
    INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ".")
endif (APPLE)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CE_LINK_LIBRARIES})

