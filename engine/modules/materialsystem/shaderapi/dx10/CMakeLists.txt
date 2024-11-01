load_sources_file()
add_library(shaderapidx10 SHARED ${SE_SOURCES})

target_include_directories(shaderapidx10 PRIVATE
        include ../shared/include ../../materialsystem/include
        ${SE_UTILS} ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1
        ${WINSDK_INCLUDE_DIRS} ${SE_LIBS}/dx9sdk/Include)

target_compile_definitions(shaderapidx10 PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE SHADERAPIDX9
        SHADER_DLL_EXPORT PROTECTED_THINGS_ENABLE strncpy=use_Q_strncpy_instead _snprintf=use_Q_snprintf_instead
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(shaderapidx10 PRIVATE
        /GF /GS- /fp:fast /W4 /nologo /c /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(shaderapidx10 PRIVATE
        /NOLOGO /DLL /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT
        $<$<CONFIG:Release>:/INCREMENTAL:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF>
        $<$<CONFIG:Debug>:/INCREMENTAL /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        $<$<CONFIG:RelWithDebInfo>:/MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF /DEBUG>
        )

set_target_properties(shaderapidx10 PROPERTIES
        OUTPUT_NAME shaderapidx10
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(shaderapidx10 PUBLIC
        bitmap bzip2 mathlib tier0 tier1 tier2 vstdlib
        ${SE_LIBS}/dx10sdk/Lib/x86/d3d10.lib
        ${SE_LIBS}/dx10sdk/Lib/x86/d3d9.lib
        ${SE_LIBS}/dx10sdk/Lib/x86/d3dx10.lib
        ${SE_LIBS}/dx10sdk/Lib/x86/d3dx9.lib
        ${SE_LIBS}/dx10sdk/Lib/x86/dxgi.lib
        )