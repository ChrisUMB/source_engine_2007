load_sources_file()
add_library(GameUI SHARED ${SE_SOURCES})

target_include_directories(GameUI PRIVATE include include/matchmaking ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ../vgui2/include ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(GameUI PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE GAMEUI_EXPORTS
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(GameUI PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(GameUI PRIVATE
        /NOLOGO /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86
        $<$<CONFIG:Release>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        $<$<CONFIG:RelWithDebInfo>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF /DEBUG>
        )

set_target_properties(GameUI PROPERTIES
        OUTPUT_NAME GameUI
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(GameUI PUBLIC
        bitmap jpeglib mathlib tier0 tier1 tier2 tier3 vgui_controls vstdlib vtf
        ${SE_LIBS}/common/vc8/cryptlib.lib
        )