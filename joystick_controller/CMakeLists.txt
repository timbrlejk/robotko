cmake_minimum_required(VERSION 2.8.3)
project(joystick_controller)


add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rviz
  tf

)



catkin_package(
 INCLUDE_DIRS include/joystick_controller
 LIBRARIES joystick
 CATKIN_DEPENDS geometry_msgs roscpp rviz tf 
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_library(js_controller src/js_controller.cpp)
target_link_libraries(js_controller ${catkin_LIBRARIES})

add_library(joystick src/joystick.cpp)
target_link_libraries(joystick ${catkin_LIBRARIES})


#add_executable(joystick_controller src/js_controller.cpp src/joystick.cpp)
add_executable(joystick_controller src/js_controller.cpp src/joystick.cpp)
target_link_libraries(joystick_controller js_controller joystick ${catkin_LIBRARIES})

