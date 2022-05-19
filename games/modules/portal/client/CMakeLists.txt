cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 11)

message("DO SOMETHING")

#add_compile_definitions(
#        WINVER=0x600 WIN32 _WIN32 NDEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE NO_STRING_T
#        CLIENT_DLL VECTOR PROTECTED_THINGS_ENABLE fopen=dont_use_fopen strncpy=use_Q_strncpy_instead _snprintf=use_Q_snprintf_instead
#        ENABLE_HTMLWINDOW PORTAL HL2_EPISODIC HL2_CLIENT_DLL _WINDLL _MBCS)

add_compile_definitions(
        WIN32
        _WIN32
        _DEBUG
        DEBUG
        _WINDOWS
        _USRDLL
        _CRT_SECURE_NO_DEPRECATE
        _CRT_NONSTDC_NO_DEPRECATE
        NO_STRING_T
        CLIENT_DLL
        VECTOR
        PROTECTED_THINGS_ENABLE
        fopen=dont_use_fopen
        strncpy=use_Q_strncpy_instead
        _snprintf=use_Q_snprintf_instead
        ENABLE_HTMLWINDOW
        PORTAL
        HL2_EPISODIC
        HL2_CLIENT_DLL)

include_directories(
        headers
        ${SE_COMMON}
        ${SE_PUBLIC}
        ${SE_PUBLIC}/tier0
        ${SE_PUBLIC}/tier1

        #TODO: Organize game_controls into src / headers, or something.
        ${SE_GAMES_COMMON}/client/game_controls

        ${SE_GAMES_COMMON}/client/headers
        ${SE_GAMES_COMMON}/server/headers
        ${SE_GAMES_COMMON}/shared/headers
        ${SE_GAMES}/hl2/client/headers
        ${SE_GAMES}/hl2/shared/headers
        ${SE_GAMES}/portal/shared/headers
)

# TODO: Investigate why the game won't build with these source files here. /hl2/hud_credits.cpp /hl2/hud_flashlight.cpp /portal/src/portal_credits.cpp

load_sources_file()
add_library(cl_portal SHARED ${SE_SOURCES})

target_link_options(cl_portal PRIVATE /DEBUG /DLL /MACHINE:X86 /NODEFAULTLIB:libc,libcd,libcmtd /INCREMENTAL:NO /SUBSYSTEM:WINDOWS /OPT:ICF /ERRORREPORT:PROMPT /NOLOGO)
#                                       /EHsc /MT -MD /MT /Od /GF /Gm /RTC1 /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt /O2 /Ob2 /Oi /Ot /FD /Gy /Zi /Be /Bd /EP
target_compile_options(cl_portal PRIVATE /Od /GF /Gm /RTC1 /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt)

#set_property(TARGET cl_portal PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#target_link_options(cl_portal PRIVATE
#        "$<$<CONFIG:Release>:${SEBUILD_LINKER_OPTIONS_RELEASE}>"
#        "$<$<CONFIG:Debug>:${SEBUILD_LINKER_OPTIONS_DEBUG}>"
#        )

#target_compile_options(cl_portal PRIVATE
#        "$<$<CONFIG:Release>:${SEBUILD_CXX_OPTIONS_RELEASE}>"
#        "$<$<CONFIG:Debug>:${SEBUILD_CXX_OPTIONS_DEBUG}>"
#        )

#TODO: Can I combine all of this into one set_target_properties call?
set_property(TARGET cl_portal PROPERTY RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/portal/bin/)
set_target_properties(cl_portal PROPERTIES OUTPUT_NAME "client")


target_link_libraries(cl_portal PUBLIC bitmap choreoobjects dmxloader mathlib particles tier0 tier1 tier2 tier3 vgui_controls vstdlib)