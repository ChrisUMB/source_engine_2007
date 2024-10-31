load_sources_file()
add_library(stdshader_dx9 SHARED ${SE_SOURCES})

target_include_directories(stdshader_dx9 PRIVATE ../headers ../fxctmp9 ../vshtmp9 ${SE_ENGINE_MODULES}/materialsystem/shaderapi/shared/include/ ${SE_ENGINE_MODULES}/materialsystem/materialsystem/include ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS} ${SE_LIBS}/dx9sdk/Include)

target_compile_definitions(stdshader_dx9 PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE STDSHADER_DX9_DLL_EXPORT FAST_MATERIALVAR_ACCESS
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(stdshader_dx9 PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(stdshader_dx9 PRIVATE
        /NOLOGO /MANIFEST:NO /DLL /SUBSYSTEM:WINDOWS /MACHINE:X86
        $<$<CONFIG:Release>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(stdshader_dx9 PROPERTIES
        OUTPUT_NAME stdshader_dx9
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/${CMAKE_BUILD_TYPE}
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(stdshader_dx9 PUBLIC ${SE_LIBS}/dx9sdk/Lib/d3dx9.lib mathlib shaderlib tier0 tier1 vstdlib)