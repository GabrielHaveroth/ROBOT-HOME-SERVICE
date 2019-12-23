#!/bin/sh
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/src/map/gabriel-world.world" &
sleep 8
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/src/map/map.yaml" &
sleep 5
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch  rviz_home_service view_navigation.launch " &
sleep 5
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; rosrun pick_objects pick_objects" &
sleep 5
