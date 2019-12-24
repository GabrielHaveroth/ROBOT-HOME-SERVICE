# ROBOT-HOME-SERVICE
# TURTLEBOT USING 
In this ROS project, using the Turtlebot, a home service robot simulation was developed.    
For this task, we employed the following Turtlebot's standard .launch  files:

- **_For localization_**:  amcl_demo.launch (from turtlebot_gazebo);
- **_To send the commands_**: keyboard_teleop.launch (from turtlebot_teleop);
- **_To start the simulation environment_**: turtlebot_world.launch (from turtlebot_gazebo).
- **_For mapping_**: gmapping_demo.launch (from turtlebot_gazebo).

We developed a custom .rviz file used in all tasks of this project *home_service.rviz* (from rviz_home_service).
# NODES
Also, we developed two nodes:

- **_pick_objects_**: this node sends the position goal to the Turtlebot, and publishes a boolean value on the */goalstatus* topic when the robot reached on the position (pick up or drop off).

- **_add_markers_**: this node draws or deletes a virtual object after it subscribes a boolean value from the */goalstatus* topic. It deletes the virtual object when the robot reached in the pick up position and draws when the robot reached in the drop off zone.

# SHELL SCRIPTS
Five shell scripts are available for testing this simulation:

- *test_navigation.sh*: it launches the simulation with custom .world file,  tests Turtlebot's navigation using rviz's manual markers, and aml_demo.
- *pick_objects.sh*: it launches the simulation with custom .world file, sends goals for Turtlebot moves to the position of pick up or drops off. 
- *add_markers.sh*: it launches the simulation with custom .world file, adds and removes the virtual objects in pick up and drop off position sequentially.
- *test_slam.sh*: it launches the simulation with custom .world file, tests Tuttlebot's mapping using the gmapping package, and keyboard_teleop.
- *home_service.sh*: It is the complete system. We send the goal position to the robot (pick_object node), and simulates the pickup and drop off using a virtual object (add_markers node).
- *home_service_my_robot.sh*: It is the same as home_service.sh but uses a custom robot model (it is in developing and fine-tuning).
