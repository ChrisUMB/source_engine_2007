load_sources_file()
add_library(vtf STATIC ${SE_SOURCES})

target_include_directories(vtf PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/lib/dx9sdk/include)

target_compile_definitions(vtf PRIVATE
        WIN32 _WIN32 _LIB _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE fopen=dont_use_fopen
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(vtf PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(vtf PRIVATE
        $<$<CONFIG:Release>:/NOLOGO>
        $<$<CONFIG:Debug>:/NOLOGO /DEBUG>
        )

set_target_properties(vtf PROPERTIES
        OUTPUT_NAME vtf
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )