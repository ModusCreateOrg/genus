# Genus

[![Modus Create](./readme-images/modus.logo.svg)](https://moduscreate.com)

[![Build Status](https://ci.moduscreate.com/buildStatus/icon?job=ModusCreateOrg/genus/master&build=1)](https://ci.moduscreate.com/job/ModusCreateOrg/job/genus/job/master/1/)


Genus a puzzle game created by [Modus Create](https://moduscreate.com) for the 2018 and runs on the [ODROID GO](https://www.hardkernel.com/shop/odroid-go/), an ESP32-based platform.  Genus runs on macOS and Linux by implementing [SDL2](https://www.libsdl.org/download-2.0.php).  



## How to Play
Genus is a simple puzzle game where the objective is to match colors in 2x2 patterns. Once a 2x2 pattern is found, the blocks will be darken as they are marked for clearing. A bonus timer will appear. As the timer runs out, you can create additional color matches. Themore matches you create, the higher your score will be.  Play until you run out of spaces to place new blocks.  


![genus-gameplay.gif](./readme-images/genus-gameplay.gif)

The game's difficulty increases as you progress through levels. There are a total of five stages in the game, each with different backgrounds, songs and color themes.

On the ODROID GO, (jay continue here)


## Keymap for computer-based players:

## Global (all screens)
`Q` Quits the game

`2` Mute / Unmute audio

`3` Move menu cursor down

### Main Menu
`1` Shortcut to enter Options from the main menu

`↑ ↓` Move menu cursor

`4` `return` `X` `Z` `Space`  Select item in the menu

### Options Screen
`1`  Exit options

### Instructions screens
`← →`  Navigate how to play screens

### Game
`← → ↑ ↓`  moves the bocks

`Z`  Rotate the blocks

`X` `SPACE`  Place blocks on the gameboard




## Quick Start

On macOS or Ubuntu 16.04 (and later), with git installed, run:

    git clone https://github.com/ModusCreateOrg/genus.git # Clone src
    genus/scripts/build.sh                                # Build it
    genus/build/genus                                     # Run genus

Once this is built, you can make changes to the sources and rebuild with just these commands:

    cd genus/build
    cmake ..        # only needed if you change CMakeLists.txt
    make

Alternatively you may use the [CLion IDE](https://www.jetbrains.com/clion/) to develop the project and run the builds.

## Repository set up for development

This repo and the [creative-engine](https://github.com/ModusCreateOrg/creative-engine) repo work together. The build scripts (`scripts/build.sh`, `cmake` or `make`) will automatically create a soft link to creative-engine.

Thus you will need to fork and clone this and the `creative-engine` repos AT THE SAME LEVEL:
```
$ ls ~/github
genus/  creative-engine/
```

In `genus/` you will need to create a soft link:
```
cd genus
ln -s ../creative-engine .
```

### Mac OS X

On Mac OS X, install XCode and then run `scripts/build.sh`. This will ensure you have Homebrew installed, and build the code in the `build` directory.

You can then run the application with this command:
```
build/genus
```

## Git Workflow
Read about [GitHub workflow](https://github.com/ModusCreateOrg/creative-engine) at the creative-engine repo.

The gist is that we fork the main repos and work in our private forks.  We push to our forks.  We create Pull Requests against the main repos.

The only way code makes it into master in the main repo is if we merge a PR.

# ModusCreateOrg GitHub Guidelines

> Modus Create team members should refer to [ModusCreateOrg GitHub Guidelines](https://docs.google.com/document/d/1eBFta4gP3-eZ4Gcpx0ww9SHAH6GrOoPSLmTFZ7R8foo/edit#heading=h.sjyqpqnsjmjl)


