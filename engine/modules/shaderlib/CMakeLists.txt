load_sources_file()
add_library(shaderlib STATIC ${SE_SOURCES})

target_include_directories(shaderlib PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ../materialsystem/headers)

target_compile_definitions(shaderlib PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE fopen=dont_use_fopen FAST_MATERIALVAR_ACCESS>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE fopen=dont_use_fopen FAST_MATERIALVAR_ACCESS>
        )

target_compile_options(shaderlib PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Z7 /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt>
        )

target_link_options(shaderlib PRIVATE
        $<$<CONFIG:Release>:/NOLOGO>
        $<$<CONFIG:Debug>:/NOLOGO>
        )

set_target_properties(shaderlib PROPERTIES
        OUTPUT_NAME shaderlib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )