load_sources_file()
add_library(engine SHARED ${SE_SOURCES})

target_include_directories(engine PRIVATE headers headers/audio headers/audio/private headers/audio/public
        ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1 ${WINSDK_INCLUDE_DIRS} ${SE_LIBS}/dx9sdk/include)

target_compile_definitions(engine PRIVATE
        WIN32 _WIN32 _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE
        USE_CONVARS VOICE_OVER_IP BUMPMAP __USEA3D _ADD_EAX_ ENGINE_DLL PROTECTED_THINGS_ENABLE fopen=dont_use_fopen
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG DEBUG>
        )

target_compile_options(engine PRIVATE
        /GF /GS- /arch:SSE /fp:fast /W4 /nologo /c /Zi /TP /errorReport:prompt
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /FD /Gy>
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        )

target_link_options(engine PRIVATE
        /NOLOGO /MANIFEST:NO /SUBSYSTEM:WINDOWS /MACHINE:X86
        $<$<CONFIG:Release>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF /ERRORREPORT:PROMPT>
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /DEBUG>
        $<$<CONFIG:RelWithDebInfo>:/NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /OPT:REF /OPT:ICF /DEBUG>
        )

set_target_properties(engine PROPERTIES
        OUTPUT_NAME engine
        MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
        )

target_link_libraries(engine PUBLIC

        bzip2
        dmxloader
        bitmap
        tier2
        vtf
        mathlib
        tier3
        tier1
        vgui_controls
        tier0
        vstdlib
        jpeglib
        appframework
        matsys_controls

        #TODO: Link directories.
        ${SE_LIBS}/common/vc7/ValidateNewValveCDKeyClient.lib
        ${SE_LIBS}/common/binkw32.lib
        ${SE_LIBS}/dx9sdk/lib/dsound.lib
        ${SE_LIBS}/dx9sdk/lib/dxguid.lib

        winmm.lib
        wsock32.lib
        ws2_32.lib
        wininet.lib
        vfw32.lib
        Rpcrt4.lib
        )