minibox_add_applet(echo
    ENTRY echo_main
    SOURCES src/coreutils/echo.cxx
)

minibox_add_applet(true
    ENTRY true_main
    SOURCES src/coreutils/true.cxx
)

minibox_add_applet(false
    ENTRY false_main
    SOURCES src/coreutils/false.cxx
)

minibox_add_applet(clear
    ENTRY clear_main
    SOURCES src/termutils/clear.cxx
)

minibox_add_applet(reset
    ENTRY reset_main
    SOURCES src/termutils/reset.cxx
)

minibox_add_applet(yes
    ENTRY yes_main
    SOURCES src/coreutils/yes.cxx
)
