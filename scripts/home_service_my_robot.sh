#!/bin/sh

cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch my_robot world.launch" &
sleep 5
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch my_robot amcl.launch" &
sleep 5
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; roslaunch  rviz_home_service view_navigation.launch " &
sleep 5
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; rosrun add_markers add_markers" &
sleep 5
cd ~/catkin_ws && xterm  -e  " source devel/setup.bash; rosrun pick_objects pick_objects" &
sleep 5
