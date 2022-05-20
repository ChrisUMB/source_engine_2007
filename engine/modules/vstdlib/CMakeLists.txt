load_sources_file()
add_library(vstdlib SHARED ${SE_SOURCES})

target_include_directories(vstdlib PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(vstdlib PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE VSTDLIB_DLL_EXPORT>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE VSTDLIB_DLL_EXPORT>
        )

target_compile_options(vstdlib PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Zi /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt>
        )

target_link_options(vstdlib PRIVATE
        $<$<CONFIG:Release>:/NOLOGO /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /MACHINE:X86>
        $<$<CONFIG:Debug>:/NOLOGO /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /SUBSYSTEM:WINDOWS /MACHINE:X86 /FORCE:MULTIPLE>
        )

set_target_properties(vstdlib PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(vstdlib PUBLIC tier0 tier1)