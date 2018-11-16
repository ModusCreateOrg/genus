cmake_minimum_required(VERSION 3.12)
project(genus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-exception-spec-mismatch")
set(CMAKE_VERBOSE_MAKEFILE ON)

# creative-engine path
if (EXISTS $ENV{CREATIVE_ENGINE_PATH})
    # set ENV variable in CLion project settings
    set(CREATIVE_ENGINE_PATH $ENV{CREATIVE_ENGINE_PATH})
    message(STATUS "Using user-defined creative-engine path: ${CREATIVE_ENGINE_PATH}")
else ()
    set(CREATIVE_ENGINE_PATH "${CMAKE_SOURCE_DIR}/../creative-engine")
    message(STATUS "Falling back to default creative-engine path: ${CREATIVE_ENGINE_PATH}")
endif ()

# resource compiler
set(RCOMP "${CREATIVE_ENGINE_PATH}/tools/rcomp")

INCLUDE_DIRECTORIES(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/GameState
        ${CMAKE_SOURCE_DIR}/src/GameState/Powerups
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR} /usr/local/include
        ${CREATIVE_ENGINE_PATH}/src
        ${CREATIVE_ENGINE_PATH}/src/Widgets
        ${CREATIVE_ENGINE_PATH}/src/libxmp
        ${CREATIVE_ENGINE_PATH}/src/libxmp/loaders
        ${CREATIVE_ENGINE_PATH}/src/libxmp/loaders/prowizarde
)

# external libraries
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

# build rcomp
add_custom_command(
        OUTPUT rcomp
        COMMAND cd ${CREATIVE_ENGINE_PATH}/tools && make
        OUTPUTS rcomp
        COMMENT "Building rcomp ${CREATIVE_ENGINE_PATH}"
)

# build Resources.bin
add_custom_command(
        OUTPUT Resources.bin
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/src && ${RCOMP} Resources.r
        OUTPUTS Resources.bin
        DEPENDS rcomp
        COMMENT "Compiling Resources ${CMAKE_CURRENT_SOURCE_DIR}"
)

# gather creative-engine sources
file(GLOB_RECURSE CREATIVE_ENGINE ${CREATIVE_ENGINE_PATH}/src/*.cpp)

# gather LibXMP sources
add_compile_definitions(LIBXMP_CORE_PLAYER=true)
add_compile_definitions(LIBXMP_CORE_DISABLE_IT=true)
file(
        GLOB LIBXMP_SRC
        ${CREATIVE_ENGINE_PATH}/src/libxmp/loaders/*.h
        ${CREATIVE_ENGINE_PATH}/src/libxmp/loaders/*.c
        ${CREATIVE_ENGINE_PATH}/src/libxmp/*.h
        ${CREATIVE_ENGINE_PATH}/src/libxmp/*.c
)

# gather Genus sources
file(GLOB_RECURSE GENUS_SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(
        genus
        Resources.bin
        ${LIBXMP_SRC}
        ${CREATIVE_ENGINE}
        ${GENUS_SRC}
        src/GameState/GGameOverProcess.cpp src/GameState/GGameOverProcess.h src/SplashState/GDropProcess.cpp src/SplashState/GDropProcess.h src/SplashState/GSplashPlayfield.cpp src/SplashState/GSplashPlayfield.h src/SplashState/GSplashProcess.cpp src/SplashState/GSplashProcess.h)

# make genus.app
if (APPLE)
    SET_TARGET_PROPERTIES(genus PROPERTIES MACOSX_BUNDLE TRUE)
    INSTALL(TARGETS genus DESTINATION ".")
endif (APPLE)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} -L/usr/local/lib ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
