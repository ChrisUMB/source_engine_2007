#[[

This project creates the `launcher.dll`, which is the library that launches source games.
]]
#

load_sources_file()
add_library(launcher SHARED ${SE_SOURCES})

target_include_directories(launcher PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(launcher PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE LAUNCHERONLY>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE LAUNCHERONLY>
        )

target_compile_options(launcher PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Zi /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt>
        )

target_link_options(launcher PRIVATE
        $<$<CONFIG:Release>:/NOLOGO /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /MACHINE:X86>
        $<$<CONFIG:Debug>:/NOLOGO /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /SUBSYSTEM:WINDOWS /MACHINE:X86>
        )

set_target_properties(launcher PROPERTIES
        OUTPUT_NAME launcher
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(launcher PUBLIC
        tier0 tier1 tier2 tier3 vstdlib
        ${SE_LIBS}/public/appframework.lib
        )