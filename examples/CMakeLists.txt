INCLUDE_DIRECTORIES(${CALPP_SOURCE_DIR}/include)

ADD_EXECUTABLE(peekflops peekflops.cpp)
ADD_EXECUTABLE(matrixmult matrixmult.cpp)
ADD_EXECUTABLE(matrixmult2 matrixmult2.cpp)
ADD_EXECUTABLE(coalescingtest coalescingtest.cpp)
ADD_EXECUTABLE(nbody nbody.cpp nbody_kernel.cpp nbody_worker.cpp)

TARGET_LINK_LIBRARIES(peekflops aticalrt aticalcl ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(matrixmult aticalrt aticalcl ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(matrixmult2 aticalrt aticalcl ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(coalescingtest aticalrt aticalcl ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(nbody aticalrt aticalcl ${Boost_LIBRARIES})