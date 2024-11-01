load_sources_file()
add_library(FileSystem_Stdio SHARED ${SE_SOURCES})

target_include_directories(FileSystem_Stdio PRIVATE include ../shared/include
        ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS}
        )

target_compile_definitions(FileSystem_Stdio PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE
        FILESYSTEM_STDIO_EXPORTS DONT_PROTECT_FILEIO_FUNCTIONS PROTECTED_THINGS_ENABLE _USE_32BIT_TIME_T
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(FileSystem_Stdio PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(FileSystem_Stdio PRIVATE
        /NOLOGO /DLL /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT
        $<$<CONFIG:Release>:/INCREMENTAL:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/INCREMENTAL /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(FileSystem_Stdio PROPERTIES
        OUTPUT_NAME FileSystem_Stdio
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(FileSystem_Stdio PUBLIC tier0 tier1 tier2 vstdlib)