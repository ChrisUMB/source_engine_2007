load_sources_file()
add_library(bitmap STATIC ${SE_SOURCES})


target_include_directories(bitmap PRIVATE ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${SE_PUBLIC}/mathlib

        ${WINSDK_INCLUDE_DIRS}
        ${SE_LIBS}/dx9sdk/Include
        ${SE_LIBS}/x360xdk/include/win32/vs2005
        )

target_compile_definitions(bitmap PRIVATE
        WIN32 _WIN32 _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(bitmap PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(bitmap PRIVATE
        $<$<CONFIG:Release>:/NOLOGO>
        $<$<CONFIG:Debug>:/NOLOGO /DEBUG>
        )

set_target_properties(bitmap PROPERTIES
        OUTPUT_NAME bitmap
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(bitmap PUBLIC
        ${CMAKE_SOURCE_DIR}/lib/public/ati_compress_mt_vc8.lib
        ${CMAKE_SOURCE_DIR}/lib/public/nvtc.lib
        )