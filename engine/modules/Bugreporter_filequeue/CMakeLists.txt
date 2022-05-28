load_sources_file()
add_library(Bugreporter_filequeue SHARED ${SE_SOURCES})

target_include_directories(Bugreporter_filequeue PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1
        ${SE_UTILS}/common ${WINSDK_INCLUDE_DIRS}
        )

target_compile_definitions(Bugreporter_filequeue PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE BUGREPORTER_EXPORTS
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(Bugreporter_filequeue PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(Bugreporter_filequeue PRIVATE
        /NOLOGO /DLL /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT
        $<$<CONFIG:Release>:/INCREMENTAL:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/INCREMENTAL /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(Bugreporter_filequeue PROPERTIES
        OUTPUT_NAME Bugreporter_filequeue
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(Bugreporter_filequeue PUBLIC
        tier0 tier1 vstdlib mathlib
        ${SE_LIBS}/common/expdlln.lib
        ${SE_LIBS}/common/trktooln.lib
        )