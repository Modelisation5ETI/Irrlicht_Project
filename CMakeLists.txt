cmake_minimum_required(VERSION 2.6)

set( PROJECT_NAME Irrlicht-Project )
project( ${PROJECT_NAME} )

# Search for /usr/local/lib/libIrrlicht.a
find_library( IRRLICHT_LIBRARY NAMES Irrlicht
  PATHS $ENV{IRRDIR}/lib )

# Configure Project
set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( MEDIA_DIR "${CMAKE_SOURCE_DIR}/media/" )
set( SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders/" )
configure_file( CMake/Project_Config.h.in Project_Config.h @ONLY )

# add_executable sources
file(GLOB_RECURSE SOURCES
  ${CMAKE_SOURCE_DIR}/src/*.[ch]pp)

# Include directories
set( INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}" )
foreach( file_path ${SOURCES} )
 get_filename_component( dir ${file_path} PATH )
 list( APPEND INCLUDE_DIRS ${dir}  )
endforeach()
list( REMOVE_DUPLICATES INCLUDE_DIRS )

include_directories( ${INCLUDE_DIRS} )

# Specify g++ option
add_definitions( -Wall -Wextra -std=c++11 )

add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries( ${PROJECT_NAME} ${IRRLICHT_LIBRARY} -lGL -lXxf86vm -lXext -lX11 -lXcursor )

