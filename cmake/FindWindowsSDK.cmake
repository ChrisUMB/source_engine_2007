IF (DEFINED ENV{WINSDK_INCLUDE_DIR})
    message(STATUS "`WINSDK_INCLUDE_DIR` environment variable present: $ENV{WINSDK_INCLUDE_DIR}")
    set(WINSDK_INCLUDE_DIR "$ENV{WINSDK_INCLUDE_DIR}")
ELSE ()
    cmake_host_system_information(
            RESULT WINSDK_VERSION
            QUERY WINDOWS_REGISTRY
            "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows\\v10.0"
            VALUE "ProductVersion"
    )

    cmake_host_system_information(
            RESULT WINSDK_KITS_DIR
            QUERY WINDOWS_REGISTRY
            "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows\\v10.0"
            VALUE "InstallationFolder"
    )

    IF (NOT WINSDK_VERSION)
        message(FATAL_ERROR "Could not determine Windows SDK version from registry keys, please set env variable WINSDK_INCLUDE_DIR to Windows SDK Include/<version> path.")
    ENDIF ()

    IF (NOT WINSDK_KITS_DIR)
        message(FATAL_ERROR "Could not determine Windows SDK directory from registry keys, please set env variable WINSDK_INCLUDE_DIR to Windows SDK Include/<version> path.")
    ENDIF ()

    IF (WINSDK_VERSION AND NOT WINSDK_VERSION STREQUAL "10.0.19041")
        set(WINSDK_HOPEFUL_DIR "${WINSDK_KITS_DIR}\\Include\\10.0.19041.0")
        IF (NOT IS_DIRECTORY ${WINSDK_HOPEFUL_DIR})
            message(WARNING "Windows SDK Version mismatch, recommended version is 10.0.19041, host is using ${WINSDK_VERSION}.\nIf build failure occurs, install 10.0.19041 and point env variable 'WINSDK_INCLUDE_DIR' to it's install directory.")
        ELSE ()
            set(WINSDK_VERSION "10.0.19041")
        ENDIF ()
    ENDIF ()

    IF (WINSDK_VERSION AND WINSDK_KITS_DIR)
        set(WINSDK_INCLUDE_DIR "${WINSDK_KITS_DIR}Include\\${WINSDK_VERSION}.0")
    ENDIF ()
ENDIF ()

set(WINSDK_INCLUDE_DIRS "${WINSDK_INCLUDE_DIR}")

# List of required subdirectories to check
set(REQUIRED_SUBDIRS
        "shared"
        "um"
        "winrt"
        "ucrt"
)

# Flag to track if all required directories are found
set(ALL_FOUND TRUE)

# Loop through each required subdirectory and check if it exists
FOREACH (SUBDIR ${REQUIRED_SUBDIRS})
    set(FULL_PATH "${WINSDK_INCLUDE_DIR}/${SUBDIR}")
    IF (NOT IS_DIRECTORY ${FULL_PATH})
        message(STATUS "Directory not found: ${FULL_PATH}")
        set(ALL_FOUND FALSE)
    ENDIF ()

    set(WINSDK_INCLUDE_DIRS "${WINSDK_INCLUDE_DIRS}" "${WINSDK_INCLUDE_DIR}\\${SUBDIR}")
ENDFOREACH ()

# If any required directory is missing, stop with an error
IF (NOT ALL_FOUND)
    message(FATAL_ERROR "One or more required SDK subdirectories were not found, check env variable `WINSDK_INCLUDE_DIR` is pointing to the right Windows SDK folder.\nIt is recommended to install and use Windows SDK version 10.0.19041.0")
ENDIF ()