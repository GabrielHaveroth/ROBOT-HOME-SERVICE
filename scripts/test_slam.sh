#!/bin/sh
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/src/map/gabriel-world.world" &
sleep 8
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 5
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch  rviz_home_service view_navigation.launch " &
sleep 5
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch " 
