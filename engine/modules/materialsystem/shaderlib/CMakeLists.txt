load_sources_file()
add_library(shaderlib STATIC ${SE_SOURCES})

target_include_directories(shaderlib PRIVATE include ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ../materialsystem/include ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(shaderlib PRIVATE
        WIN32 _WIN32 _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE fopen=dont_use_fopen FAST_MATERIALVAR_ACCESS
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(shaderlib PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(shaderlib PRIVATE
        $<$<CONFIG:Release>:/NOLOGO>
        $<$<CONFIG:Debug>:/NOLOGO /DEBUG>
        )

set_target_properties(shaderlib PROPERTIES
        OUTPUT_NAME shaderlib
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )