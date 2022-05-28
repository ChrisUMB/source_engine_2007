load_sources_file()
add_library(launcher SHARED ${SE_SOURCES})

target_include_directories(launcher PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(launcher PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE LAUNCHERONLY
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(launcher PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(launcher PRIVATE
        /NOLOGO /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86
        $<$<CONFIG:Release>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(launcher PROPERTIES
        OUTPUT_NAME launcher
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(launcher PUBLIC
        tier0 tier1 tier2 tier3 vstdlib appframework
        ${SE_LIBS}/dx9sdk/lib/dinput8.lib
        ${SE_LIBS}/dx9sdk/lib/ddraw.lib
        )