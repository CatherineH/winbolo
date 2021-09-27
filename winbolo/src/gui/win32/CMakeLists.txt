cmake_minimum_required(VERSION 3.20)
project(Winbolo)

set(CMAKE_WIN32_EXECUTABLE ON)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)
get_filename_component(GUI_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(SRC_DIR ${GUI_DIR} DIRECTORY)
aux_source_directory(${SRC_DIR}/bolo BOLO_SOURCES)
aux_source_directory(${SRC_DIR}/winbolonet WINBOLONET_SOURCES)
aux_source_directory(${SRC_DIR}/server SERVER_SOURCES)
set(winbolo_SRC ${SOURCES} ${BOLO_SOURCES} ${WINBOLONET_SOURCES} 
${SRC_DIR}/server/threads.h ${SRC_DIR}/server/threads.c
)
add_executable(Winbolo WIN32 ${winbolo_SRC})