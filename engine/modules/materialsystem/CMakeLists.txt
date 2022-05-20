load_sources_file()
add_library(materialsystem SHARED ${SE_SOURCES})

target_include_directories(materialsystem PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(materialsystem PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE DEFINE_MATERIALSYSTEM_INTERFACE MATERIALSYSTEM_EXPORTS PROTECTED_THINGS_ENABLE strncpy=use_Q_strncpy_instead _snprintf=use_Q_snprintf_instead fopen=dont_use_fopen>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE DEFINE_MATERIALSYSTEM_INTERFACE MATERIALSYSTEM_EXPORTS PROTECTED_THINGS_ENABLE strncpy=use_Q_strncpy_instead _snprintf=use_Q_snprintf_instead fopen=dont_use_fopen>
        )

target_compile_options(materialsystem PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Zi /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt>
        )

target_link_options(materialsystem PRIVATE
        $<$<CONFIG:Release>:/NOLOGO /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /MACHINE:X86 /ERRORREPORT:PROMPT>
        $<$<CONFIG:Debug>:/INCREMENTAL /NOLOGO /DLL /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT /FORCE:MULTIPLE>
        )

set_target_properties(materialsystem PROPERTIES
        OUTPUT_NAME materialsystem
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(materialsystem PUBLIC
        bitmap
        mathlib
        tier1
        tier2
        vtf
        shaderlib
        tier0
        vstdlib
        )