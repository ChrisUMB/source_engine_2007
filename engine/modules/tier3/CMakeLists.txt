load_sources_file()
add_library(tier3 STATIC ${SE_SOURCES})

target_include_directories(tier3 PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${SE_GAMES_COMMON}/shared/headers)

target_compile_definitions(tier3 PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE>
        )

target_compile_options(tier3 PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Z7 /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt>
        )

target_link_options(tier3 PRIVATE
        $<$<CONFIG:Release>:/NOLOGO>
        $<$<CONFIG:Debug>:/NOLOGO>
        )

set_target_properties(tier3 PROPERTIES
        OUTPUT_NAME tier3
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )