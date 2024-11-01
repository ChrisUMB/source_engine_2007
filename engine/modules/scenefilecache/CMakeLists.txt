load_sources_file()
add_library(scenefilecache SHARED ${SE_SOURCES})

target_include_directories(scenefilecache PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${SE_GAMES_COMMON}/shared/headers ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(scenefilecache PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE STUDIORENDER_EXPORTS PROTECTED_THINGS_ENABLE fopen=dont_use_fopen
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(scenefilecache PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(scenefilecache PRIVATE
        /NOLOGO /MANIFEST:NO /DLL /SUBSYSTEM:WINDOWS /MACHINE:X86
        $<$<CONFIG:Release>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(scenefilecache PROPERTIES
        OUTPUT_NAME scenefilecache
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(scenefilecache PUBLIC tier0 tier1 vstdlib)