#include <actionlib/client/simple_action_client.h>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include "std_msgs/Bool.h"

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
using namespace move_base_msgs;
typedef actionlib::SimpleActionClient<MoveBaseAction> MoveBaseClient;

class PickObjects
{
  private:
     float positionX;
     float positionY;
     float orientationW;
     MoveBaseGoal goal;
     ros::Publisher goalStatusTalker;
     std_msgs::Bool msg;

  public:
    PickObjects(ros::NodeHandle *nh) 
    {
      goal.target_pose.header.frame_id = "map";
      goal.target_pose.header.stamp = ros::Time::now();
      goalStatusTalker =  nh->advertise<std_msgs::Bool>("goalstatus", 10);
      msg.data = true;
    }

    void goToGoalPickUp(float positionX, float positionY, float orientationW, MoveBaseClient*ac)
    {
      this->positionX = positionX;
      this->positionY = positionY;
      this->orientationW = orientationW;

      goal.target_pose.pose.position.x = positionX;
      goal.target_pose.pose.position.y = positionY;
      goal.target_pose.pose.orientation.w = orientationW;

      ROS_INFO("Sending goal");
      ac->sendGoal(goal);
      ac->waitForResult();

      if(ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
          ROS_INFO("Successfully reached to pick up zone");
          goalStatusTalker.publish(msg);
      }
      else
        ROS_INFO("Failed to move pick up for some reason");
    }

    void goToGoalDropOff(float positionX, float positionY, float orientationW, MoveBaseClient*ac)
    {
      this->positionX = positionX;
      this->positionY = positionY;
      this->orientationW = orientationW;

      goal.target_pose.pose.position.x = positionX;
      goal.target_pose.pose.position.y = positionY;
      goal.target_pose.pose.orientation.w = orientationW;

      ROS_INFO("Sending goal");
      ac->sendGoal(goal);
      ac->waitForResult();

      if(ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
          ROS_INFO("Successfully reached to drop off zone");
          goalStatusTalker.publish(msg);
      }
      else
      ROS_INFO("Failed to move drop off for some reason");
    }
};



int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  ros::NodeHandle nh;
  PickObjects po = PickObjects(&nh);
  po.goToGoalPickUp(0.0, 5.0, 1.0, &ac);
  ros::Duration(5.0).sleep();
  po.goToGoalDropOff(0.5, 3.0, 1.0, &ac);
  ROS_INFO("Wainting more 5.0 seconds");
  ros::Duration(5.0).sleep();

  return 0;
}