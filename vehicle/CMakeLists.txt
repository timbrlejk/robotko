cmake_minimum_required(VERSION 2.8.3)
project(vehicle)

add_compile_options(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  tf
)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
FIND_LIBRARY(WIRINGPI_LIBRARY wiringPi /laco/wiringPi)
catkin_package(
  INCLUDE_DIRS include/vehicle
  LIBRARIES vehicle
  CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs tf
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

# add_executable(${PROJECT_NAME}_node src/kb_controller_node.cpp)
add_executable(${PROJECT_NAME} src/vehicle.cpp)

 target_link_libraries(${PROJECT_NAME}
   ${catkin_LIBRARIES} ${CURSES_LIBRARIES} ${WIRINGPI_LIBRARY}
 )


