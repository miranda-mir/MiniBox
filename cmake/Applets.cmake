include_guard(GLOBAL)

function(minibox_add_applet name)
    cmake_parse_arguments(
        PARSE_ARGV 1 APPLET
        ""
        "ENTRY"
        "SOURCES"
    )

    if(APPLET_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR
            "Unknown arguments for applet '${name}': ${APPLET_UNPARSED_ARGUMENTS}"
        )
    endif()

    if(APPLET_KEYWORDS_MISSING_VALUES)
        message(FATAL_ERROR
            "Missing values for applet '${name}': ${APPLET_KEYWORDS_MISSING_VALUES}"
        )
    endif()

    if(NOT APPLET_ENTRY OR NOT APPLET_SOURCES)
        message(FATAL_ERROR
            "Applet '${name}' requires ENTRY and SOURCES"
        )
    endif()

    if(NOT name MATCHES "^[a-zA-Z0-9_-]+$")
        message(FATAL_ERROR "Invalid applet name: ${name}")
    endif()

    if(NOT APPLET_ENTRY MATCHES "^[a-zA-Z_][a-zA-Z0-9_]*$")
        message(FATAL_ERROR "Invalid entry function: ${APPLET_ENTRY}")
    endif()

    get_property(registered GLOBAL PROPERTY MINIBOX_APPLET_NAMES)
    if(name IN_LIST registered)
        message(FATAL_ERROR "Duplicate applet name: ${name}")
    endif()

    get_property(entries GLOBAL PROPERTY MINIBOX_APPLET_ENTRY_NAMES)
    if(APPLET_ENTRY IN_LIST entries)
        message(FATAL_ERROR "Duplicate applet entry function: ${APPLET_ENTRY}")
    endif()

    string(MAKE_C_IDENTIFIER "${name}" option_name)
    string(TOUPPER "${option_name}" option_name)

    get_property(option_names GLOBAL PROPERTY MINIBOX_APPLET_OPTION_NAMES)
    if(option_name IN_LIST option_names)
        message(FATAL_ERROR
            "Applet '${name}' maps to a duplicate CMake option name: ${option_name}"
        )
    endif()

    set_property(GLOBAL APPEND PROPERTY MINIBOX_APPLET_NAMES "${name}")
    set_property(GLOBAL APPEND PROPERTY MINIBOX_APPLET_ENTRY_NAMES "${APPLET_ENTRY}")
    set_property(GLOBAL APPEND PROPERTY MINIBOX_APPLET_OPTION_NAMES "${option_name}")

    option(
        MINIBOX_APPLET_${option_name}
        "Build ${name} applet"
        ON
    )

    if(NOT MINIBOX_APPLET_${option_name})
        message(STATUS "Applet disabled: ${name}")
        return()
    endif()

    set(applet_sources "")

    foreach(source IN LISTS APPLET_SOURCES)
        if(IS_ABSOLUTE "${source}")
            set(source_path "${source}")
        else()
            set(source_path "${PROJECT_SOURCE_DIR}/${source}")
        endif()

        if(NOT EXISTS "${source_path}")
            message(FATAL_ERROR "Source not found for '${name}': ${source}")
        endif()

        list(APPEND applet_sources "${source_path}")
    endforeach()

    target_sources(minibox PRIVATE ${applet_sources})

    set_property(GLOBAL APPEND PROPERTY
        MINIBOX_APPLET_DECLARATIONS
        "MINIBOX_DECLARE(${APPLET_ENTRY})"
    )

    set_property(GLOBAL APPEND PROPERTY
        MINIBOX_APPLET_ENTRIES
        "{\"${name}\", ${APPLET_ENTRY}},"
    )

    message(STATUS "Applet enabled: ${name}")
endfunction()
