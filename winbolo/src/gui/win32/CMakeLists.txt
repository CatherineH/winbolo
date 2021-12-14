cmake_minimum_required(VERSION 3.20)
project(Winbolo)

set(CMAKE_WIN32_EXECUTABLE ON)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)
get_filename_component(GUI_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(SRC_DIR ${GUI_DIR} DIRECTORY)
aux_source_directory(${SRC_DIR}/bolo BOLO_SOURCES)
aux_source_directory(${SRC_DIR}/winbolonet WINBOLONET_SOURCES)
aux_source_directory(${SRC_DIR}/server SERVER_SOURCES)
aux_source_directory(${SRC_DIR}/server/BigDigits BIGDIG_SOURCES)

aux_source_directory(${SRC_DIR}/lzw LZW_SOURCES)
set(winbolo_SRC ${SOURCES} ${WINBOLONET_SOURCES} ${BIGDIG_SOURCES} ${SERVER_SOURCES} ${BOLO_SOURCES} ${LZW_SOURCES})
find_package(PkgConfig REQUIRED)
find_package(zlib REQUIRED)
pkg_check_modules(minizip minizip>=1.2)

add_executable(Winbolo WIN32 ${winbolo_SRC})


target_include_directories(Winbolo PUBLIC ${ZLIB_INCLUDE_DIRS} ${minizip_INCLUDE_DIRS})
target_link_libraries(Winbolo ${ZLIB_LIBRARY_RELEASE} ws2_32 minizip)