load_sources_file()
add_library(StudioRender SHARED ${SE_SOURCES})

target_include_directories(StudioRender PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(StudioRender PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE STUDIORENDER_EXPORTS PROTECTED_THINGS_ENABLE fopen=dont_use_fopen
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(StudioRender PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(StudioRender PRIVATE
        /NOLOGO /MANIFEST:NO /DLL /SUBSYSTEM:WINDOWS /MACHINE:X86
        $<$<CONFIG:Release>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(StudioRender PROPERTIES
        OUTPUT_NAME StudioRender
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(StudioRender PUBLIC bitmap mathlib tier0 tier1 tier2 tier3 vstdlib)