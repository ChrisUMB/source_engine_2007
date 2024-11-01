load_sources_file()
add_library(inputsystem SHARED ${SE_SOURCES})

target_include_directories(inputsystem PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS} ${SE_LIBS}/dx9sdk/Include)

target_compile_definitions(inputsystem PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(inputsystem PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(inputsystem PRIVATE
        /NOLOGO /MANIFEST:NO /DLL /SUBSYSTEM:WINDOWS /MACHINE:X86
        $<$<CONFIG:Release>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        )

set_target_properties(inputsystem PROPERTIES
        OUTPUT_NAME inputsystem
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(inputsystem PUBLIC tier0 tier1 tier2 vstdlib Winmm)