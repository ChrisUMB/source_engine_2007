add_library(vtf STATIC
        headers/cvtf.h
        headers/s3tc_decode.h

        src/convert_x360.cpp
        src/s3tc_decode.cpp
        src/vtf.cpp
        )

target_include_directories(vtf PRIVATE
        headers
        ${SE_COMMON}
        ${SE_PUBLIC}
        ${SE_PUBLIC}/tier0
        ${SE_PUBLIC}/tier1
        ${CMAKE_SOURCE_DIR}/lib/dx9sdk/include
        )

target_compile_definitions(vtf PRIVATE
        WIN32
        _WIN32
        NDEBUG
        _LIB
        _CRT_SECURE_NO_DEPRECATE
        _CRT_NONSTDC_NO_DEPRECATE
        )

target_link_options(vtf PRIVATE
        /NODEFAULTLIB:libc
        /NODEFAULTLIB:libcd
        /NODEFAULTLIB:libcmtd
        )

set_target_properties(vtf PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/public/
        MSVC_RUNTIME_LIBRARY "MultiThreaded"
        )

