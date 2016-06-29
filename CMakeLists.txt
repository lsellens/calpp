cmake_minimum_required(VERSION 2.6)

PROJECT(CALPP)

IF(DEFINED "ENV{AMDAPPSDKROOT}")
    SET(CMAKE_INSTALL_PREFIX "$ENV{AMDAPPSDKROOT}")
ELSE()
    MESSAGE(FATAL_ERROR "Enviromental variable AMDAPPSDKROOT not found")
ENDIF()


SET(Boost_ADDITIONAL_VERSIONS "1.41" "1.41.0" "1.42" "1.42.0" "1.43" "1.43.0" "1.44" "1.44.0" "1.45" "1.45.0")

#if you want the full compiler output, remove comment on the following line
#SET(CMAKE_VERBOSE_MAKEFILE ON)

#SET(Boost_USE_STATIC_LIBS   ON)
#SET(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost 1.36.0 COMPONENTS date_time )

IF(NOT Boost_FOUND)
    MESSAGE( FATAL_ERROR "Unable to find boost library" )
ENDIF()

FIND_LIBRARY( LIB_ATICALCL aticalcl )
FIND_LIBRARY( LIB_ATICALRT aticalrt )

GET_FILENAME_COMPONENT( LIB_ATICALCL_PATH "${LIB_ATICALCL}" PATH )
GET_FILENAME_COMPONENT( LIB_ATICALRT_PATH "${LIB_ATICALRT}" PATH )

MESSAGE( STATUS "===========================================================" )
MESSAGE( STATUS "ATI CAL cl library directory ${LIB_ATICALCL_PATH}" )
MESSAGE( STATUS "ATI CAL rt library directory ${LIB_ATICALRT_PATH}" )
MESSAGE( STATUS "Boost version ${Boost_LIB_VERSION}" )
MESSAGE( STATUS "===========================================================" )

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${LIB_ATICAL_INCLUDE})
LINK_DIRECTORIES(${LIB_ATICALCL_PATH} ${LIB_ATICALRT_PATH} ${Boost_LIBRARY_DIRS})

#add definitions, compiler switches, etc.
#ADD_DEFINITIONS(-Wall -O0 -g3)

ADD_SUBDIRECTORY(examples)
ADD_SUBDIRECTORY(regression)

INSTALL( DIRECTORY "${CALPP_SOURCE_DIR}/include" DESTINATION . PATTERN "*~" )
