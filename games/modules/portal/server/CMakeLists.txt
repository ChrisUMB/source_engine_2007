cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 11)

add_compile_definitions(
        WIN32
        _WIN32
        NDEBUG
        _WINDOWS
        _USRDLL
        _CRT_SECURE_NO_DEPRECATE
        _CRT_NONSTDC_NO_DEPRECATE
        GAME_DLL
        VECTOR
        PROTECTED_THINGS_ENABLE
        fopen=dont_use_fopen
        sprintf=use_Q_snprintf_instead_of_sprintf
        strncpy=use_Q_strncpy_instead
        _snprintf=use_Q_snprintf_instead
        PORTAL
        HL2_DLL
        HL2_EPISODIC
        USES_SAVERESTORE)

include_directories(headers
        ${SE_COMMON}
        ${SE_PUBLIC}
        ${SE_PUBLIC}/tier0
        ${SE_PUBLIC}/tier1
        ${SE_GAMES}/hl2/server/headers
        ${SE_GAMES}/hl2/shared/headers
        ${SE_GAMES}/portal/shared/headers
        ${SE_GAMES}/episodic/server/headers
        ${SE_GAMES_COMMON}/server/headers
        ${SE_GAMES_COMMON}/shared/headers

        ${SE_ENGINE_MODULES}/utils/common
        )

load_sources_file()
add_library(sv_portal SHARED ${SE_SOURCES})

target_link_options(sv_portal PRIVATE /DEBUG /DLL /MACHINE:X86 /NODEFAULTLIB:libc,libcd,libcmtd /OPT:REF /SAFESEH:NO /INCREMENTAL:NO /SUBSYSTEM:WINDOWS /OPT:ICF /ERRORREPORT:PROMPT /NOLOGO /TLBID:1)

set(MY_RELEASE_OPTIONS /O2 /Ob2 /Oi /Ot /GF /FD /MT /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Zi /TP /errorReport:prompt)
set(MY_DEBUG_OPTIONS /MDd /Zi /Ob0 /Od /RTC1)

target_compile_options(cl_portal PRIVATE
        "$<$<CONFIG:Debug>:${MY_DEBUG_OPTIONS}>"
        "$<$<CONFIG:Release>:${MY_RELEASE_OPTIONS}>"
)

set_target_properties(sv_portal PROPERTIES OUTPUT_NAME "server")
set_property(TARGET sv_portal PROPERTY RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/portal/bin/)

set_property(TARGET sv_portal PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
target_link_libraries(sv_portal PUBLIC particles dmxloader tier2 vstdlib mathlib tier3 tier1 choreoobjects vgui_controls tier0)