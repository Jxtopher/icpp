cmake_minimum_required(VERSION 3.12)

###############################################################################
# Set of compilator parameters
###############################################################################
project(icpp)

set(CMAKE_CXX_STANDARD 20) #-std=c++2a 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER_LAUNCHER "ccache")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  set(FLAGS "-pedantic -Wall -Wextra -Wcast-align -Wctor-dtor-privacy \
  -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
  -Wmissing-include-dirs -Wno-unused -Wshadow \
  -Woverloaded-virtual -Wredundant-decls -Wsign-promo \
  -Wstrict-null-sentinel -Wstrict-overflow=2 -Wundef -Werror \
  -Wswitch-default -Wsign-conversion -Wcast-qual -Wold-style-cast") # -Wmissing-declarations 
  set(COV_FLAGS "-fprofile-arcs -ftest-coverage")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")


###############################################################################
# Load modules cmake
###############################################################################
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CTest)
include(cppcheck)       # apply cppcheck
include(clang-format)   # apply clang-format
include(version)        # Version name generator form git branch, hash
#include(doxygen)        # Create the documentation


###############################################################################
# Get external libs
###############################################################################
find_package(PkgConfig)
find_package(Threads REQUIRED)

###############################################################################
# APPS
###############################################################################
add_executable(${PROJECT_NAME} "apps/main.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
###############################################################################
# Tests
###############################################################################
pkg_check_modules(CPPUNIT cppunit QUIET)

IF (CPPUNIT_FOUND)
enable_testing()
file(GLOB_RECURSE ALL_SOURCE_FILES  "test/*.cpp")
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    get_filename_component(NAME_FILE ${SOURCE_FILE} NAME_WE)
    add_executable(${NAME_FILE}.test ${SOURCE_FILE})
    target_link_libraries(${NAME_FILE}.test LINK_PRIVATE
        ${CPPUNIT_LIBRARIES}
        ${LIBPROJECT}
        gcov)
    target_include_directories(${NAME_FILE}.test PRIVATE 
        "include/"
        "/usr/local/include/"
    )
    set_target_properties(${NAME_FILE}.test PROPERTIES COMPILE_FLAGS "${FLAGS} ${COV_FLAGS}")
    add_test(NAME ${NAME_FILE} COMMAND ${NAME_FILE}.test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endforeach()
else (CPPUNIT_FOUND)
   if (CppUnit_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find CppUnit")
   endif (CppUnit_FIND_REQUIRED)
endif (CPPUNIT_FOUND)
###############################################################################
# Install
###############################################################################
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)