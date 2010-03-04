INCLUDE_DIRECTORIES(${CALPP_SOURCE_DIR}/include)

ADD_EXECUTABLE(peekflops peekflops.cpp)
ADD_EXECUTABLE(matrixmult matrixmult.cpp)
ADD_EXECUTABLE(coalescingtest coalescingtest.cpp)

TARGET_LINK_LIBRARIES(peekflops aticalrt aticalcl ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(matrixmult aticalrt aticalcl ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(coalescingtest aticalrt aticalcl ${Boost_LIBRARIES})
