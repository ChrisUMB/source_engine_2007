cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0091 NEW)
set(CMAKE_CXX_STANDARD 17)

# Find Windows SDK
include(cmake/FindWindowsSDK.cmake)

project(source_engine_2007)

IF (NOT SE_RUN_DIR)
    set(SE_RUN_DIR ${PROJECT_SOURCE_DIR}/run)
ENDIF ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SE_RUN_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SE_RUN_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin)
set(CMAKE_OBJECT_PATH_MAX 512)

add_compile_definitions(
        WINVER=0x600
        _CRT_NO_VA_START_VALIDATION
        _HAS_AUTO_PTR_ETC
)

set(SE_LIBS ${PROJECT_SOURCE_DIR}/lib)
set(SE_ENGINE ${PROJECT_SOURCE_DIR}/engine)
set(SE_ENGINE_MODULES ${PROJECT_SOURCE_DIR}/engine/modules)

set(SE_COMMON ${PROJECT_SOURCE_DIR}/engine/common)
set(SE_PUBLIC ${PROJECT_SOURCE_DIR}/engine/public)
set(SE_UTILS ${PROJECT_SOURCE_DIR}/engine/modules/utils)

set(SE_GAMES ${PROJECT_SOURCE_DIR}/games/modules)
set(SE_GAMES_COMMON ${PROJECT_SOURCE_DIR}/games/common)

set(SE_INCLUDES
        ${SE_GAMES}
        ${SE_PUBLIC}
        ${SE_PUBLIC}/engine
        ${SE_PUBLIC}/tier0
        ${SE_PUBLIC}/tier1
        ${SE_COMMON}/

        ${SE_GAMES_COMMON}/client/game_controls

        ${SE_GAMES_COMMON}/client/headers
        ${SE_GAMES_COMMON}/server/headers
        ${SE_GAMES_COMMON}/shared/headers
        ${SE_GAMES}/hl2/client/headers
        ${SE_GAMES}/hl2/shared/headers
        ${SE_GAMES}/portal/shared/headers

        CACHE INTERNAL ""
)

macro("load_sources_file")
    file(READ sources.txt SE_SOURCES)
    STRING(REGEX REPLACE ";" "\\\\;" SE_SOURCES "${SE_SOURCES}")
    STRING(REGEX REPLACE "\n" ";" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_COMMON}" "${SE_COMMON}" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_PUBLIC}" "${SE_PUBLIC}" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_UTILS}" "${SE_UTILS}" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_GAMES}" "${SE_GAMES}" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_GAMES_COMMON}" "${SE_GAMES_COMMON}" SE_SOURCES "${SE_SOURCES}")
    STRING(REPLACE "\${SE_ENGINE_MODULES}" "${SE_ENGINE_MODULES}" SE_SOURCES "${SE_SOURCES}")
endmacro()

add_subdirectory(engine/modules/launcher_main)
add_subdirectory(engine/modules/tier0)
add_subdirectory(engine/modules/tier1)
add_subdirectory(engine/modules/tier2)
add_subdirectory(engine/modules/tier3)
add_subdirectory(engine/modules/appframework)
add_subdirectory(engine/modules/avi)
add_subdirectory(engine/modules/matsys_controls)
add_subdirectory(engine/modules/jpeglib)
add_subdirectory(engine/modules/bzip2)
add_subdirectory(engine/modules/vtf)
add_subdirectory(engine/modules/mathlib)
add_subdirectory(engine/modules/bitmap)
add_subdirectory(engine/modules/vstdlib)
add_subdirectory(engine/modules/dmxloader)
add_subdirectory(engine/modules/materialsystem/shaderlib)
add_subdirectory(engine/modules/materialsystem/materialsystem)
add_subdirectory(engine/modules/materialsystem/shaderapi/dx9)
add_subdirectory(engine/modules/materialsystem/shaderapi/dx10)
add_subdirectory(engine/modules/materialsystem/shaderapi/empty)
add_subdirectory(engine/modules/particles)
add_subdirectory(engine/modules/choreoobjects)
add_subdirectory(engine/modules/vgui_surfacelib)
add_subdirectory(engine/modules/vgui_controls)
add_subdirectory(engine/modules/vguimatsurface)
add_subdirectory(engine/modules/vgui2)
add_subdirectory(engine/modules/AdminServer)
add_subdirectory(engine/modules/Bugreporter)
add_subdirectory(engine/modules/Bugreporter_filequeue)
add_subdirectory(engine/modules/Bugreporter_public)
add_subdirectory(engine/modules/Bugreporter_text)
add_subdirectory(engine/modules/datacache)
add_subdirectory(engine/modules/soundemittersystem)
add_subdirectory(engine/modules/inputsystem)
add_subdirectory(engine/modules/unicode)
add_subdirectory(engine/modules/StudioRender)
add_subdirectory(engine/modules/scenefilecache)
add_subdirectory(engine/modules/voice_codecs/miles)

add_subdirectory(engine/modules/filesystem/stdio)
add_subdirectory(engine/modules/filesystem/steam)
add_subdirectory(engine/modules/GameUI)

add_subdirectory(engine/modules/materialsystem/stdshaders/stdshader_dx9)
add_subdirectory(engine/modules/materialsystem/stdshaders/stdshader_dx8)


add_subdirectory(engine/modules/launcher)
add_subdirectory(engine/modules/engine)

add_subdirectory(games/modules/portal/client)
add_subdirectory(games/modules/portal/server)