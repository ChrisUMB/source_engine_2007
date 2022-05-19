# Source Engine 2007 - CLion/CMake

This is the 2007 Source Engine leak transferred to a raw CMake project, made in CLion. It should be noted
that this project doesn't need CLion to work, it is just a collection of carefully configured CMake projects and should
be able to build with just CMake and The v80 MSVC toolkit.

## Setup Guide [CLion]

1. Install [CLion](https://www.jetbrains.com/clion/). CLion is a paid application developed by [JetBrains](https://www.jetbrains.com/),
however you can get their entire toolkit for $20/month, which is very worth it. Otherwise, you can live off CLions free trials
that they renew with every update, so if you're just a hobbyist you can scrape by that way.

2. 

## Built Modules

These are just modules within the engine that currently build in this project.

- bitmap
- bzip2
- choreoobjects
- dmxloader
- engine
- launcher
- launcher_main
- materialsystem
- mathlib
- particles
- shaderlib
- tier0
- tier1
- tier2
- tier3
- vgui_controls
- vstdlib
- vtf

## Built Games
- Portal

## Reorganization

I reorganized the project pretty heavily, and will probably continue to do so.

### Engine Modules

Engine modules reside in `engine/modules`, this is where you'll find things like `tier0`, `vstdlib`, et cetera. These
weren't changed very much in terms of structure, just my usual `src` and `headers` refactoring.

### Game Modules

Game modules is where you'll find all the different games, like portal, they are in `games/modules`. I put them
in a "modules" subdirectory like that because I needed a place to store common game classes that get shared around
a lot, works well enough. I modified games to be structured like `{game}/client`, `{game}/server`, `{game}/shared`,
that way if you are specifically working on something very game related, all of its sources are adjacent, not spread
about multiple higher level folders.

### CMake Shenanigans

`SE_ENGINE` : /engine/  
`SE_ENGINE_MODULES` : /engine/modules  
`SE_COMMON` : /engine/common  
`SE_PUBLIC` : /engine/public  
`SE_GAMES` : /games/modules  
`SE_GAMES_COMMON` : /games/common  

`load_sources_file` : Macro that populates `SE_SOURCES` with a list of sources in a `sources.txt` in the same folder as the
CMake file. This is useful because source lists for games are huge, so getting them out of the CMake file was necessary.
This macro also does some string replacements, so you can use the aforementioned variables inside the `sources.txt` file.
