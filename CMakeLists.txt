project(RType CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})
include_directories("inc/")

################ RTYPE SERVER BINARY CONFIG ##################

# SOURCES FILES
file(GLOB_RECURSE RTYPE_SERVER_SOURCES "src/server/*.cpp")

# BINARY CONFIG
add_executable(rtype_server ${RTYPE_SERVER_SOURCES})
SET_TARGET_PROPERTIES(rtype_server PROPERTIES COMPILE_FLAGS "-D RTYPE_SERVER")

# HEADER FILES
file(GLOB_RECURSE RTYPE_SERVER_HEADERS "inc/server/*.hpp")
set (RTYPE_SERVER_INCLUDE_DIRS "")
foreach (_headerFile ${RTYPE_SERVER_HEADERS})
  get_filename_component(_dir ${_headerFile} PATH)
  list (APPEND RTYPE_SERVER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES RTYPE_SERVER_INCLUDE_DIRS)

# LIB INCLUDE
target_include_directories(rtype_server PRIVATE ${RTYPE_SERVER_INCLUDE_DIRS})
target_link_libraries(rtype_server ${CONAN_LIBS})


################ RTYPE CLIENT BINARY CONFIG ##################

# SOURCES FILES
file(GLOB_RECURSE RTYPE_CLIENT_SOURCES "src/client/*.cpp")

# HEADER FILES
file(GLOB_RECURSE RTYPE_CLIENT_HEADERS "inc/client/*.hpp")
set (RTYPE_CLIENT_INCLUDE_DIRS "")
foreach (_headerFile ${RTYPE_CLIENT_HEADERS})
  get_filename_component(_dir ${_headerFile} PATH)
  list (APPEND RTYPE_CLIENT_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES RTYPE_CLIENT_INCLUDE_DIRS)

# BINARY CONFIG
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_executable(rtype_client ${RTYPE_CLIENT_SOURCES})
SET_TARGET_PROPERTIES(rtype_client PROPERTIES COMPILE_FLAGS "-D RTYPE_CLIENT")

# LIB INCLUDE
target_include_directories(rtype_client PRIVATE ${RTYPE_CLIENT_INCLUDE_DIRS})
target_link_libraries(rtype_client ${CONAN_LIBS})
