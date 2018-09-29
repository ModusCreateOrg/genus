cmake_minimum_required(VERSION 3.12)
project(genus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-exception-spec-mismatch")
set(CMAKE_VERBOSE_MAKEFILE ON)
# resource compiler
set(RCOMP "${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/tools/rcomp")
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/src ${CMAKE_BINARY_DIR} /usr/local/include)

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
        COMMAND ${RCOMP} ${CMAKE_CURRENT_SOURCE_DIR}/src/Resources.r
        OUTPUTS Resources.bin
        DEPENDS rcomp
        COMMENT "Compiling Resources ${CMAKE_CURRENT_SOURCE_DIR} ")

# gather creagive-engine sources
file(GLOB_RECURSE LIB RELATIVE ${CMAKE_SOURCE_DIR} "creative-engine/src/*.cpp")


# LibXMP
add_compile_definitions(LIBXMP_CORE_PLAYER=true)
add_compile_definitions(LIBXMP_CORE_DISABLE_IT=true)

include_directories(
    ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/loaders/prowizard"
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/loaders"
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp"
)


file(GLOB LIBXMP_SRC
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/loaders/*.h"
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/loaders/*.c"
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/*.h"
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/*.c"
)



add_executable(genus
        rcomp
        Resources.bin
        ${LIB}
        ${LIBXMP_SRC}
        src/main.cpp
        src/GPlayfield.cpp
        src/GGameEngine.cpp
        README.md)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -L/usr/local/lib ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
#target_link_libraries(${GAME_ENGINE})

