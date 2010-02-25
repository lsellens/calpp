cmake_minimum_required(VERSION 2.6)

PROJECT(CALPP)

#if you want the full compiler output, remove comment on the following line
#SET(CMAKE_VERBOSE_MAKEFILE ON)

#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-I/opt/ati-stream-sdk-v2.01-lnx64/include)
#ADD_DEFINITIONS(-Wall -O0 -g3 -I/opt/ati-stream-sdk-v2.0-lnx64/include)


ADD_SUBDIRECTORY(examples)

INSTALL( DIRECTORY "${CALPP_SOURCE_DIR}/include" DESTINATION . PATTERN "*~" )
