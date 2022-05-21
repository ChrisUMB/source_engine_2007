load_sources_file()
add_library(jpeglib STATIC ${SE_SOURCES})

target_include_directories(jpeglib PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/jpeglib ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1)

target_compile_definitions(jpeglib PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE TIER1_STATIC_LIB>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE TIER1_STATIC_LIB>)

target_compile_options(jpeglib PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /MT /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Z7 /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /MTd /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt>
        )

target_link_options(jpeglib PRIVATE
        $<$<CONFIG:Release>:/NOLOGO>
        $<$<CONFIG:Debug>:/NOLOGO>
        )

set_target_properties(jpeglib PROPERTIES
        OUTPUT_NAME jpeglib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(jpeglib PUBLIC)