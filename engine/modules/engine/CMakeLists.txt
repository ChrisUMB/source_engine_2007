#[[
This project creates the `engine.dll`
]]


load_sources_file()
add_library(engine SHARED ${SE_SOURCES})

target_include_directories(engine PRIVATE headers headers/audio headers/audio/private headers/audio/public
        ${SE_COMMON} ${SE_PUBLIC} ${SE_PUBLIC}/tier0 ${SE_PUBLIC}/tier1  ${WINSDK_INCLUDE_DIRS} ${SE_LIBS}/dx9sdk/include)

target_compile_definitions(engine PRIVATE
        $<$<CONFIG:Release>:WIN32 _WIN32 NDEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE USE_CONVARS VOICE_OVER_IP BUMPMAP __USEA3D _ADD_EAX_ ENGINE_DLL PROTECTED_THINGS_ENABLE fopen=dont_use_fopen>
        $<$<CONFIG:Debug>:WIN32 _WIN32 _DEBUG DEBUG _WINDOWS _USRDLL _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE USE_CONVARS VOICE_OVER_IP BUMPMAP __USEA3D _ADD_EAX_ ENGINE_DLL PROTECTED_THINGS_ENABLE fopen=dont_use_fopen>
        )

target_compile_options(engine PRIVATE
        $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /GF /FD /GS- /Gy /arch:SSE /fp:fast /W4 /nologo /c /TP /errorReport:prompt>
        $<$<CONFIG:Debug>:/Od /GF /Gm /RTC1 /GS- /arch:SSE /fp:fast /W4 /nologo /c /Zi /TP /errorReport:prompt>
        )

target_link_options(engine PRIVATE
        $<$<CONFIG:Release>:/NOLOGO /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmtd /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /MACHINE:X86 /ERRORREPORT:PROMPT>
        $<$<CONFIG:Debug>:/NOLOGO /MANIFEST:NO /NODEFAULTLIB:libc /NODEFAULTLIB:libcd /NODEFAULTLIB:libcmt /SUBSYSTEM:WINDOWS /MACHINE:X86 /FORCE:MULTIPLE>
        )

set_target_properties(engine PROPERTIES
        OUTPUT_NAME engine
        RUNTIME_OUTPUT_DIRECTORY ${SE_RUN_DIR}/bin/
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/source-engine/$<$<CONFIG:Debug>:debug/>$<$<CONFIG:Release>:release/>
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