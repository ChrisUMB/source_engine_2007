load_sources_file()
add_library(vgui_controls STATIC ${SE_SOURCES})

target_include_directories(vgui_controls PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS})

target_compile_definitions(vgui_controls PRIVATE
        WIN32 _WIN32 _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(vgui_controls PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(vgui_controls PRIVATE
        $<$<CONFIG:Release>:/NOLOGO>
        $<$<CONFIG:Debug>:/NOLOGO /DEBUG>
        )

set_target_properties(vgui_controls PROPERTIES
        OUTPUT_NAME vgui_controls
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )