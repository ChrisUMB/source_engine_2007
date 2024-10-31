load_sources_file()
add_library(vguimatsurface SHARED ${SE_SOURCES})

target_include_directories(vguimatsurface PRIVATE headers
        ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS}
        ../vgui2/include

        )

target_compile_definitions(vguimatsurface PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE
        fopen=dont_use_fopen BENCHMARK VGUIMATSURFACE_DLL_EXPORT GAMEUI_EXPORTS DONT_PROTECT_FILEIO_FUNCTIONS
        PROTECTED_THINGS_ENABLE ENABLE_HTMLWINDOW

        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(vguimatsurface PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(vguimatsurface PRIVATE
        /NOLOGO /DLL /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT
        $<$<CONFIG:Release>:/INCREMENTAL:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/INCREMENTAL /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(vguimatsurface PROPERTIES
        OUTPUT_NAME vguimatsurface
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/${CMAKE_BUILD_TYPE}
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(vguimatsurface PUBLIC
        bitmap mathlib tier0 tier1 tier2 tier3 vgui_controls vgui_surfacelib vstdlib
        ${SE_LIBS}/public/nvtc.lib
        )