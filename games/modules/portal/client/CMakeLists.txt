load_sources_file()
add_library(cl_portal SHARED ${SE_SOURCES})

target_include_directories(cl_portal PRIVATE headers
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
        ${WINSDK_INCLUDE_DIRS}
        )

target_compile_definitions(cl_portal PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE NO_STRING_T CLIENT_DLL VECTOR
        PROTECTED_THINGS_ENABLE fopen=dont_use_fopen strncpy=use_Q_strncpy_instead _snprintf=use_Q_snprintf_instead
        ENABLE_HTMLWINDOW PORTAL HL2_EPISODIC HL2_CLIENT_DLL

        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(cl_portal PRIVATE
        /GF /GS- /Gy /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GS->
        $<$<CONFIG:Debug>:/Od /RTC1 /GS- /Zi>
        )

target_link_options(cl_portal PRIVATE
        /NOLOGO /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86
        $<$<CONFIG:Release>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        $<$<CONFIG:RelWithDebInfo>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF /DEBUG>
        )

set_target_properties(cl_portal PROPERTIES
        OUTPUT_NAME client
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/portal/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/${CMAKE_BUILD_TYPE}
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(cl_portal PUBLIC bitmap choreoobjects dmxloader mathlib particles tier0 tier1 tier2 tier3 vgui_controls vstdlib)