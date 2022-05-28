load_sources_file()
add_library(shaderapidempty SHARED ${SE_SOURCES})

target_include_directories(shaderapidempty PRIVATE
        include ../shared/include ../../materialsystem/include
        ${SE_UTILS} ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1
        ${WINSDK_INCLUDE_DIRS} ${SE_LIBS}/dx9sdk/Include)

target_compile_definitions(shaderapidempty PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE SHADER_DLL_EXPORT PROTECTED_THINGS_ENABLE
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(shaderapidempty PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(shaderapidempty PRIVATE
        /NOLOGO /DLL /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT
        $<$<CONFIG:Release>:/INCREMENTAL:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/INCREMENTAL /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(shaderapidempty PROPERTIES
        OUTPUT_NAME shaderapidempty
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(shaderapidempty PUBLIC tier0 tier1 vstdlib)