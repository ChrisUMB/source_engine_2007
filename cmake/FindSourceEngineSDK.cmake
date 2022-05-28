set(SE_DIR ${CMAKE_CURRENT_SOURCE_DIR}..)

set(SE_PUBLIC_DIR ${SE_DIR}/engine/public)
set(SE_MODULES_DIR ${SE_DIR}/engine/modules)
set(SE_COMMON_DIR ${SE_DIR}/engine/common)

set(SE_LIB_DIR_BASE ${SE_DIR}/lib/source-engine)
set(SE_LIB_DIR_RELEASE ${SE_LIB_DIR_BASE}/release)
set(SE_LIB_DIR_DEBUG ${SE_LIB_DIR_BASE}/debug)

set(SE_LIB_DIR $<$<CONFIG:Release>:${SE_LIB_DIR_RELEASE}>$<$<CONFIG:Debug>:${SE_LIB_DIR_Debug}>)

set(SE_INCLUDES
        ${SE_PUBLIC_DIR}
        ${SE_PUBLIC_DIR}/engine
        ${SE_PUBLIC_DIR}/tier0
        ${SE_PUBLIC_DIR}/tier1
        ${SE_COMMON_DIR}/

        )

set(SE_LINK_LIBRARIES
        ${SE_LIB_DIR}/tier0.lib
        ${SE_LIB_DIR}/tier1.lib
        ${SE_LIB_DIR}/tier2.lib
        ${SE_LIB_DIR}/tier3.lib
        #        ${SE_LIB_DIR}/engine.lib
        )