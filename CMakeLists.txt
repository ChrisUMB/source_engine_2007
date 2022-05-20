cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0091 NEW)
project(source_engine_2007)

set(CMAKE_CXX_STANDARD 11)

# This clears out all cmake and MSVC defaults, hopefully.
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "")
# These two are most definitely unnecessary but I'd rather be safe than sorry.
set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "")

set(SE_LIBS ${CMAKE_SOURCE_DIR}/lib)
set(SE_ENGINE ${CMAKE_SOURCE_DIR}/engine)
set(SE_ENGINE_MODULES ${CMAKE_SOURCE_DIR}/engine/modules)
set(SE_COMMON ${CMAKE_SOURCE_DIR}/engine/common)
set(SE_PUBLIC ${CMAKE_SOURCE_DIR}/engine/public)
set(SE_GAMES ${CMAKE_SOURCE_DIR}/games/modules)
set(SE_GAMES_COMMON ${CMAKE_SOURCE_DIR}/games/common)

set(SE_RUN_DIR ${CMAKE_SOURCE_DIR}/run)

macro("load_sources_file")
    file(READ sources.txt SE_SOURCES)
    STRING(REGEX REPLACE ";" "\\\\;" SE_SOURCES "${SE_SOURCES}")
    STRING(REGEX REPLACE "\n" ";" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_COMMON}" "${SE_COMMON}" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_PUBLIC}" "${SE_PUBLIC}" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_GAMES}" "${SE_GAMES}" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_GAMES_COMMON}" "${SE_GAMES_COMMON}" SE_SOURCES "${SE_SOURCES}")
endmacro()

add_subdirectory(engine/modules/launcher_main)
add_subdirectory(engine/modules/tier0)
add_subdirectory(engine/modules/tier1)
add_subdirectory(engine/modules/tier2)
add_subdirectory(engine/modules/tier3)
add_subdirectory(engine/modules/bzip2)
add_subdirectory(engine/modules/vtf)
add_subdirectory(engine/modules/mathlib)
add_subdirectory(engine/modules/bitmap)
add_subdirectory(engine/modules/vstdlib)
add_subdirectory(engine/modules/dmxloader)
add_subdirectory(engine/modules/shaderlib)
add_subdirectory(engine/modules/materialsystem)
add_subdirectory(engine/modules/particles)
add_subdirectory(engine/modules/choreoobjects)
add_subdirectory(engine/modules/vgui_controls)

add_subdirectory(engine/modules/launcher)
add_subdirectory(engine/modules/engine)


add_subdirectory(games/modules/portal/client)
add_subdirectory(games/modules/portal/server)