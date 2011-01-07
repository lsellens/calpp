INCLUDE_DIRECTORIES(${CALPP_SOURCE_DIR}/include)

ADD_EXECUTABLE(uav uav.cpp)
ADD_EXECUTABLE(rsqrt rsqrt.cpp)

TARGET_LINK_LIBRARIES(uav aticalrt aticalcl ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(rsqrt aticalrt aticalcl ${Boost_LIBRARIES})
