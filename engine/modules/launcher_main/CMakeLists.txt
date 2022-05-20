#[[

This project creates the `launcher.exe`, usually named `hl2.exe`.

]]
#

add_executable(launcher_main src/main.cpp)

target_include_directories(launcher_main PRIVATE headers ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1)

target_compile_definitions(launcher_main PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _WINDOWS _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE fopen=dont_use_fopen>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _WINDOWS _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE fopen=dont_use_fopen>
        )

target_compile_options(launcher_main PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /GS- /Gy /fp:fast /W4 /nologo /c /Wp64 /Zi /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /GS- /fp:fast /W4 /nologo /c /Wp64 /ZI /TP /errorReport:prompt>
        )

target_link_options(launcher_main PRIVATE
        $<$<CONFIG:Release>:/NOLOGO /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /MACHINE:X86 /FIXED:No>
        $<$<CONFIG:Debug>:/NOLOGO /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /SUBSYSTEM:WINDOWS /MACHINE:X86 /FIXED:No>
        )

set_target_properties(launcher_main PROPERTIES
        OUTPUT_NAME hl2
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )