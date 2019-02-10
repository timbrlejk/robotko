#!/bin/bash

cd ~/catkin_ws
source devel/setup.bash 
cd src/robotko
roslaunch robotko robotko.launch
