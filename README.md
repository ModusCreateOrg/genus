[![Modus Create](./readme-images/modus.logo.svg)](https://moduscreate.com)

# Genus [![Build Status](https://ci.moduscreate.com/buildStatus/icon?job=ModusCreateOrg/genus/master&build=1)](https://ci.moduscreate.com/job/ModusCreateOrg/job/genus/job/master/1/)

Genus is a cross-platform a puzzle game created by [Modus Create](https://moduscreate.com) for the 2018 holiday season. Genus runs on the [ODROID GO](https://www.hardkernel.com/shop/odroid-go/), macOS and Linux.

## How to Play
Genus is a simple puzzle game where the objective is to match colors in 2x2 patterns. Once a 2x2 pattern is found, the blocks will be darken as they are marked for clearing and a bonus timer will appear. If you create additional create additional color matches while the bonus timer is counting down, your score will increase.  Play until you run out of spaces to place new blocks.  

![genus-gameplay.gif](./readme-images/genus-gameplay.gif)

The game's difficulty increases as you progress through levels. There are a total of six stages in the game, each with different backgrounds, songs and color themes.

Here's the button mapping for the ODROID GO.
![genus-card-odroid-cutout.jpg](./readme-images/genus-card-odroid-cutout.jpg)


## Keymap for computer-based players:

#### Global (all screens)
| Key(s) | Description |
| --- | --- |
| `Q` | Quits the game |
| `2` | Mute / Unmute audio |
| `3` | Move menu cursor down |

#### Main Menu
| Key(s) | Description |
| --- | --- |
| `1` | Shortcut to enter Options from the main menu |
| `↑ ↓` | Move menu cursor |
| `4` `RETURN` `X` `Z` `SPACE` | Select item in the menu |

#### Options Screen
| Key(s) | Description |
| --- | --- |
| `1` | Exit options |


### Instructions screens
| Key(s) | Description |
| --- | --- |
| `← →` | Navigate how to play screens |

### Game
| Key(s) | Description |
| --- | --- |
|`← → ↑ ↓` | Moves the bocks |
| `Z` | Rotate the blocks |
| `X` `SPACE` | Place blocks on the gameboard |

# Building genus

On macOS or Ubuntu or Raspbian Stretch with git installed, run:

```
$ ls ~/github
genus/  creative-engine/
```

In `genus/` you will need to create a soft link:
```
cd genus
ln -s ../creative-engine .
```

Building this has been tested on the x86_64 architecture on macOS X High Sierra and Mojave, in Ubuntu 16.04 and 18.04, and on the `armhf` architecture Raspbian Stretch (9.6). 

### Mac OS X

On Mac OS X, install XCode and then run `scripts/build.sh`. This will ensure you have Homebrew installed, and build the code in the `build` directory.

You can then run the application with this command:
```
build/genus
```

### Raspberry Pi

Genus is tested on Raspbian Stretch (9.6) on the Raspberry Pi 2B+ and 3B+. You will need about 2GB of space in /tmp and about 2GB of space in /home to build this.

The game will run very slowly without enabling the OpenGL desktop driver. You can enable it by running `sudo raspbi-config` and choosing _Advanced Options / GL Driver / GL (Full KMS)_. See this site for complete instructions: https://eltechs.com/how-to-enable-opengl-on-raspberry-pi/

Run `scripts/build.sh` and the build will run. The first time it runs it will have to build `cmake` from source which takes a long time. It will install `cmake` in /usr/local/bin/cmake.

You can then run the application with this command:
```
build/genus
```

## Git Workflow
Read about [GitHub workflow](https://github.com/ModusCreateOrg/creative-engine) at the creative-engine repo.

The gist is that we fork the main repos and work in our private forks.  We push to our forks.  We create Pull Requests against the main repos.

The only way code makes it into master in the main repo is if we merge a PR.

# ModusCreateOrg GitHub Guidelines

Modus Create team members should refer to [ModusCreateOrg GitHub Guidelines](https://docs.google.com/document/d/1eBFta4gP3-eZ4Gcpx0ww9SHAH6GrOoPSLmTFZ7R8foo/edit#heading=h.sjyqpqnsjmjl)

## License
Genus is licensed under [GPL v3](https://www.gnu.org/licenses/quick-guide-gplv3.en.html).

# Contributing
Interested in contributing to Genus? Please see our [developing](./DEVELOPING.md) and [contributions](./CONTRIBUTIONS.MD) guidelines. 
