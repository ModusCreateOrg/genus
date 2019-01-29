# Genus

[![Modus Create](./readme-images/modus.logo.svg)](https://moduscreate.com)

[![Build Status](https://ci.moduscreate.com/buildStatus/icon?job=ModusCreateOrg/genus/master&build=1)](https://ci.moduscreate.com/job/ModusCreateOrg/job/genus/job/master/1/)


Genus is a cross-platform a puzzle game created by [Modus Create](https://moduscreate.com) for the 2018 holiday sesaon. Genus runs on the [ODROID GO](https://www.hardkernel.com/shop/odroid-go/), macOS and Linux and implements the following technologies on their respective hosts:

`(All platforms)`
[Creative Engine](https://github.com/ModusCreateOrg/creative-engine)
[Lib XMP](http://xmp.sourceforge.net/)(Audio)

`(macOS, Linux)`
[SDL2](https://www.libsdl.org/download-2)

`(ODROID GO)`
[Espressif IoT development Framework (ESP IDF)](https://github.com/espressif/esp-idf)


## How to Play
Genus is a simple puzzle game where the objective is to match colors in 2x2 patterns. Once a 2x2 pattern is found, the blocks will be darken as they are marked for clearing. A bonus timer will appear. As the timer runs out, you can create additional color matches. Themore matches you create, the higher your score will be.  Play until you run out of spaces to place new blocks.  


![genus-gameplay.gif](./readme-images/genus-gameplay.gif)

The game's difficulty increases as you progress through levels. There are a total of five stages in the game, each with different backgrounds, songs and color themes.

On the ODROID GO, the instructions can be found on our play cards (front, back).
[genus-card-odroid-cutout.jpg](./readme-images/genus-card-odroid-cutout.jpg)



## Keymap for computer-based players:

## Global (all screens)
  Q Quits the game
  2 Mute / Unmute audio
  3 Move menu cursor down

### Main Menu
  1 Shortcut to enter Options from the main menu
  ↑ ↓ Move menu cursor
  4 RETURN X Z SPACE: Select item in the menu

### Options Screen
  1  Exit options

### Instructions screens
  ← →  Navigate how to play screens

### Game
  ← → ↑ ↓  moves the bocks
  Z  Rotate the blocks
  X SPACE  Place blocks on the gameboard

## License
Genus is licensed under [GPL v3](https://www.gnu.org/licenses/quick-guide-gplv3.en.html).

# Contributing
Interested in contributing to Genus? Please see our [developing](./DEVELOPING.md) and [contributions](./CONTRIBUTIONS.MD) guideilnes. 