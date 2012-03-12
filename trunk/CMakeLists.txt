cmake_minimum_required(VERSION 2.8)

project(AITheory)

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
 
set(CMAKE_DEBUG_POSTFIX "_d")

set(BUILD_SHARED_LIBS FALSE CACHE BOOL "TRUE to build project as shared libraries, FALSE to build it as static libraries")
if(NOT BUILD_SHARED_LIBS)
	add_definitions(-D_IRR_STATIC_LIB_)
	add_definitions(-DFT2_BUILD_LIBRARY)
	add_definitions(-D_LIB)
	add_definitions(-DSTATIC_LIB)
	add_definitions(-DNO_GSL)
endif()

# define an option for choosing between static and dynamic C runtime
set(STATIC_STD_LIBS TRUE CACHE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")

if(MSVC)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  
  if(STATIC_STD_LIBS)
	foreach(flag
	  CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
	  CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
	  if(${flag} MATCHES "/MD")
		string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
	  endif()
	endforeach()
  endif()
  
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=c++0x")
endif()

include_directories("${CMAKE_SOURCE_DIR}"
  "${CMAKE_SOURCE_DIR}/src"
  "${CMAKE_SOURCE_DIR}/depends/include/"
)

add_subdirectory(src)
