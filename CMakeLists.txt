cmake_minimum_required(VERSION 3.12)
project(genus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-exception-spec-mismatch")
set(CMAKE_VERBOSE_MAKEFILE ON)
# resource compiler
set(RCOMP "${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/tools/rcomp")

INCLUDE_DIRECTORIES(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/src
        ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/src/Widgets
        ${CMAKE_BINARY_DIR} /usr/local/include
        )

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

# gather creative-engine s\ources
file(GLOB_RECURSE CREATIVE_ENGINE RELATIVE ${CMAKE_SOURCE_DIR} "creative-engine/src/*.cpp")

# gather game sources
file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

# LibXMP
add_compile_definitions(LIBXMP_CORE_PLAYER=true)
add_compile_definitions(LIBXMP_CORE_DISABLE_IT=true)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/loaders/prowizarde
    ${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/loaders
    ${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp
)


file(GLOB LIBXMP_SRC
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/loaders/*.h"
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/loaders/*.c"
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/*.h"
    "${CMAKE_SOURCE_DIR}/creative-engine/src/libxmp/*.c"
)
file(GLOB_RECURSE GENUS_SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
#file(GLOB GENUS_SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(genus
        Resources.bin
        ${LIBXMP_SRC}
        ${CREATIVE_ENGINE}
        ${GENUS_SRC}
        creative-engine/src/Widgets/BWidget.cpp creative-engine/src/Widgets/BWidget.h src/MainOptionsState/GMainOptionsWIdget.cpp src/MainOptionsState/GMainOptionsWIdget.h creative-engine/src/Widgets/BSelectWidget.cpp creative-engine/src/Widgets/BSelectWidget.h creative-engine/src/Widgets/BMenuWidget.cpp creative-engine/src/Widgets/BMenuWidget.h creative-engine/src/Widgets/Widgets.h creative-engine/src/Widgets/BContainerWidget.cpp creative-engine/src/Widgets/BContainerWidget.h creative-engine/src/Widgets/BDialogWidget.cpp creative-engine/src/Widgets/BDialogWidget.h creative-engine/src/Widgets/BWidgetTheme.cpp creative-engine/src/Widgets/BWidgetTheme.h src/MainOptionsState/GMusic.cpp src/MainOptionsState/GMusic.h)

# make genus.app
if(APPLE)
        SET_TARGET_PROPERTIES(genus PROPERTIES MACOSX_BUNDLE TRUE)
        INSTALL(TARGETS genus DESTINATION ".")
endif(APPLE)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} -L/usr/local/lib ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
#target_link_libraries(${GAME_ENGINE})






