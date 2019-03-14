# Modus Create's Genus Holiday Game

[![Modus Create](./images/modus.logo.svg)](https://moduscreate.com)

[![Build Status](https://ci.moduscreate.com/buildStatus/icon?job=ModusCreateOrg/genus/master&build=1)](https://ci.moduscreate.com/job/ModusCreateOrg/job/genus/job/master/1/)

## Quick Start

On macOS or Ubuntu or Raspbian Stretch with git installed, run:

    git clone https://github.com/ModusCreateOrg/genus.git # Clone src
    genus/scripts/build.sh                                # Build it
    genus/build/genus                                     # Run genus

Once this is built, you can make changes to the sources and rebuild with just these commands:

    cd genus/build
    cmake ..        # only needed if you change CMakeLists.txt
    make

Alternatively you may use the [CLion IDE](https://www.jetbrains.com/clion/) to develop the project and run the builds.

Run this in the project root to build the documentation:

    make docs

View the [documentation](docs/html/index.html) after it is built.
 
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

> Modus Create team members should refer to [ModusCreateOrg GitHub Guidelines](https://docs.google.com/document/d/1eBFta4gP3-eZ4Gcpx0ww9SHAH6GrOoPSLmTFZ7R8foo/edit#heading=h.sjyqpqnsjmjl)


