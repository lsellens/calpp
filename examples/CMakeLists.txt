INCLUDE_DIRECTORIES(${CALPP_SOURCE_DIR}/include)

ADD_EXECUTABLE(peekflops peekflops.cpp)
ADD_EXECUTABLE(matrixmult matrixmult.cpp)
ADD_EXECUTABLE(coalescingtest coalescingtest.cpp)

TARGET_LINK_LIBRARIES(peekflops aticalrt aticalcl)
TARGET_LINK_LIBRARIES(matrixmult aticalrt aticalcl)
TARGET_LINK_LIBRARIES(coalescingtest aticalrt aticalcl)
