load_sources_file()
add_library(sv_portal SHARED ${SE_SOURCES})

target_include_directories(sv_portal PRIVATE headers
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

target_compile_definitions(sv_portal PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE GAME_DLL VECTOR
        PROTECTED_THINGS_ENABLE fopen=dont_use_fopen sprintf=use_Q_snprintf_instead_of_sprintf strncpy=use_Q_strncpy_instead
        _snprintf=use_Q_snprintf_instead PORTAL HL2_DLL HL2_EPISODIC USES_SAVERESTORE

        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(sv_portal PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /Gm /RTC1 /Zi>
        )

target_link_options(sv_portal PRIVATE
        /NOLOGO /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86
        $<$<CONFIG:Release>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(sv_portal PROPERTIES
        OUTPUT_NAME server
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/portal/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(sv_portal PUBLIC particles dmxloader tier2 vstdlib mathlib tier3 tier1 choreoobjects vgui_controls tier0)