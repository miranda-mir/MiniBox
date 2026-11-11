cmake_minimum_required(VERSION 3.20.3)

project(MiniBox VERSION 0.1.2)

set(TARGET_BINARY "minibox")

option(ECHO "compile ECHO command" ON)
option(TRUE "compile TRUE command" ON)
option(FALSE "compile FALSE command" ON)
option(CLEAR "compile CLEAR command" ON)
option(RESET "compile RESET command" ON)

set(ECHO_BUILD ${ECHO})
set(TRUE_BUILD ${TRUE})
set(FALSE_BUILD ${FALSE})
set(CLEAR_BUILD ${CLEAR})
set(RESET_BUILD ${RESET})

configure_file(MiniBoxConfig.h.in config.h)

# Echo command
if(ECHO STREQUAL ON)
	set(COREUTILS_ECHO_SOURCE src/coreutils/echo.cpp)
else()
	set(COREUTILS_ECHO_SOURCE "")
endif()

# True command
if(TRUE STREQUAL ON)
	set(COREUTILS_TRUE_SOURCE src/coreutils/true.cpp)
else()
	set(COREUTILS_TRUE_SOURCE "")
endif()

# False command
if(FALSE STREQUAL ON)
	set(COREUTILS_FALSE_SOURCE src/coreutils/false.cpp)
else()
	set(COREUTILS_FALSE_SOURCE "")
endif()

# Clear command
if(CLEAR STREQUAL ON)
	set(TERMUTILS_CLEAR_SOURCE src/termutils/clear.cpp)
else()
	set(TERMUTILS_CLEAR_SOURCE "")
endif()

# Reset command
if(RESET STREQUAL ON)
	set(TERMUTILS_RESET_SOURCE src/termutils/reset.cpp)
else()
	set(TERMUTILS_RESET_SOURCE "")
endif()


add_executable(
	${TARGET_BINARY}

	src/MiniBox.cpp
	src/applets.cpp

	${COREUTILS_ECHO_SOURCE}
        ${COREUTILS_TRUE_SOURCE}
        ${COREUTILS_FALSE_SOURCE}
        ${TERMUTILS_CLEAR_SOURCE}
        ${TERMUTILS_RESET_SOURCE}
)

target_include_directories(
	${TARGET_BINARY} PUBLIC
	include/
	${CMAKE_BINARY_DIR}
)

target_compile_options(
	${TARGET_BINARY} PRIVATE
	-Wall
	-Wextra
	-std=c++98
	-pedantic-errors
	-fno-exceptions
	-fno-unwind-tables
	-fno-asynchronous-unwind-tables
)
