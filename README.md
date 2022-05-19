# Source Engine 2007 - CLion/CMake

Trying to build the Source Engine 2007 leak in CLion using CMake, one module at a time.

## Built Modules

These are just modules within the engine that currently build in this project.

- bitmap
- dmxloader
- materialsystem
- mathlib
- particles
- shaderlib
- tier0
- tier1
- tier2
- tier3
- vstdlib
- vtf
- choreobjects
- vgui_controls

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
