load_sources_file()
add_library(bitmap STATIC ${SE_SOURCES})


target_include_directories(bitmap PRIVATE ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${SE_PUBLIC}/mathlib
        ${SE_WIN_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/lib/dx9sdk/Include
        ${CMAKE_SOURCE_DIR}/lib/x360xdk/include/win32/vs2005
        )

file(WRITE stuff.txt ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
target_compile_definitions(bitmap PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE>
        )

target_compile_options(bitmap PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /MT /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Z7 /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /MTd /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt>
        )

target_link_options(bitmap PRIVATE
        $<$<CONFIG:Release>:/NOLOGO>
        $<$<CONFIG:Debug>:/NOLOGO>
        )

set_target_properties(bitmap PROPERTIES
        OUTPUT_NAME bitmap
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/public/
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(bitmap PUBLIC
        ${CMAKE_SOURCE_DIR}/lib/public/ati_compress_mt_vc8.lib
        ${CMAKE_SOURCE_DIR}/lib/public/nvtc.lib
        )