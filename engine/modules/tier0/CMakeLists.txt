load_sources_file()
add_library(tier0 SHARED ${SE_SOURCES})

target_include_directories(tier0 PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(tier0 PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE TIER0_DLL_EXPORT>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE TIER0_DLL_EXPORT>
        )

target_compile_options(tier0 PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Zi /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt>
        )

target_link_options(tier0 PRIVATE
        $<$<CONFIG:Release>:/INCREMENTAL:NO /NOLOGO /DLL /MANIFEST:NO /NODEFAULTLIB:libc,libcd,libcmtd /DEBUG /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /MACHINE:X86 /ERRORREPORT:PROMPT>
        $<$<CONFIG:Debug>:/INCREMENTAL /NOLOGO /DLL /MANIFEST:NO /NODEFAULTLIB:libc,libcd,libcmt /DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT>
        )

set_target_properties(tier0 PROPERTIES
        OUTPUT_NAME tier0
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(tier0 PUBLIC ws2_32.lib)