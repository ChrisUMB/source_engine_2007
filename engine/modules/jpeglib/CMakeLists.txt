load_sources_file()
add_library(jpeglib STATIC ${SE_SOURCES})

target_include_directories(jpeglib PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/jpeglib ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1)

target_compile_definitions(jpeglib PRIVATE
        WIN32 _WIN32 _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE STRICT
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(jpeglib PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TC /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /Gm /RTC1 /Zi>
        )

target_link_options(jpeglib PRIVATE
        $<$<CONFIG:Release>:/NOLOGO>
        $<$<CONFIG:Debug>:/NOLOGO /DEBUG>
        )

set_target_properties(jpeglib PROPERTIES
        OUTPUT_NAME jpeglib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(jpeglib PUBLIC)