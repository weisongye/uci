cmake_minimum_required(VERSION 2.6)

PROJECT(uci C)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
ADD_DEFINITIONS(-O0 -Wall -Werror --std=gnu99 -g3 -ggdb -I. -DUCI_PREFIX="${CMAKE_INSTALL_PREFIX}")

OPTION(UCI_DEBUG "debugging support" OFF)
OPTION(UCI_DEBUG_TYPECAST "typecast debugging support" OFF)
OPTION(BUILD_LUA "build Lua binding" OFF)
OPTION(BUILD_STATIC "statically linking uci" ON)

# FIND_PATH(ubox_include_dir libubox/usock.h)

CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/uci_config.h.in ${CMAKE_SOURCE_DIR}/uci_config.h )

# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${ubox_include_dir})

# SET(LIB_SOURCES libuci.c file.c util.c delta.c parse.c blob.c)
SET(LIB_SOURCES libuci.c file.c util.c delta.c parse.c)

# FIND_LIBRARY(ubox NAMES ubox)
# IF(BUILD_STATIC)
#   FIND_LIBRARY(ubox-static NAMES libubox.a)
# ENDIF(BUILD_STATIC)

ADD_LIBRARY(uci SHARED ${LIB_SOURCES})
SET_TARGET_PROPERTIES(uci PROPERTIES OUTPUT_NAME uci)
TARGET_LINK_LIBRARIES(uci)

ADD_LIBRARY(uci-static STATIC ${LIB_SOURCES})
SET_TARGET_PROPERTIES(uci-static PROPERTIES OUTPUT_NAME uci)
TARGET_LINK_LIBRARIES(uci-static)

ADD_EXECUTABLE(cli cli.c)
SET_TARGET_PROPERTIES(cli PROPERTIES OUTPUT_NAME uci)
 IF(BUILD_STATIC)
   TARGET_LINK_LIBRARIES(cli uci-static)
 ELSE(BUILD_STATIC)
   TARGET_LINK_LIBRARIES(cli uci)
 ENDIF(BUILD_STATIC)

ADD_LIBRARY(ucimap STATIC ucimap.c)

# ADD_SUBDIRECTORY(lua)

INSTALL(FILES uci.h uci_config.h uci_blob.h ucimap.h
	DESTINATION include
)

INSTALL(TARGETS uci cli
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

