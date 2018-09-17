cmake_minimum_required(VERSION 3.9)
project(genus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-exception-spec-mismatch")
set(CMAKE_VERBOSE_MAKEFILE ON)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

set(RCOMP "${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/tools/rcomp")
#add_custom_target(bar ALL)
#add_custom_command(
#        OUTPUT bar
#        command  "echo foo"
#)

#add_custom_target(link_target ALL
#        DEPENDS .cmake-depend
#        COMMAND ${CMAKE_COMMAND} -e create_symlink ../creative-engine ./creative-engine
#        COMMAND "echo HERE")

add_custom_command(
        OUTPUT creative-engine
        COMMAND rm -f ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine  && ln -sn ${CMAKE_CURRENT_SOURCE_DIR}/../creative-engine ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine
        COMMENT "Creating softlink"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine
)
#add_custom_command(
#        OUTPUT always_rebuild
#        COMMAND ls
#)

#add_dependencies(bar bar)
#add_dependencies(link_target link_target)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/src)
aux_source_directory(creative-engine/lib LIB)

add_custom_command(OUTPUT rcomp
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/creative-engine/tools && make
        OUTPUTS rcomp
        COMMENT "Building rcomp")

add_custom_command(OUTPUT Resources.bin
#        COMMAND ls ${RCOMP}
        COMMAND @echo
        COMMAND ${RCOMP} Resources.r
        OUTPUTS Resources.bin
        DEPENDS rcomp
        COMMENT "Compiling Resources ${CMAKE_CURRENT_SOURCE_DIR} ")

add_executable(genus
        rcomp
        Resources.bin
        creative-engine
        src/main.cpp
        src/GPlayfield.cpp
        src/GGameEngine.cpp
        README.md)

#target_link_libraries(${GAME_ENGINE})

