load_sources_file()
add_library(shaderapidx9 SHARED ${SE_SOURCES})

target_include_directories(shaderapidx9 PRIVATE
        include ../shared/include ../../materialsystem/include
        ${SE_UTILS} ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1
        ${WINSDK_INCLUDE_DIRS} ${SE_LIBS}/dx9sdk/Include)

target_compile_definitions(shaderapidx9 PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE SHADERAPIDX9
        SHADER_DLL_EXPORT PROTECTED_THINGS_ENABLE strncpy=use_Q_strncpy_instead _snprintf=use_Q_snprintf_instead
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(shaderapidx9 PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(shaderapidx9 PRIVATE
        /NOLOGO /DLL /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT
        $<$<CONFIG:Release>:/INCREMENTAL:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/INCREMENTAL /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(shaderapidx9 PROPERTIES
        OUTPUT_NAME shaderapidx9
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(shaderapidx9 PUBLIC
        bitmap bzip2 mathlib tier0 tier1 tier2 vstdlib
        ${SE_LIBS}/dx9sdk/Lib/d3d9.lib
        ${SE_LIBS}/dx9sdk/Lib/d3dx9.lib
        )