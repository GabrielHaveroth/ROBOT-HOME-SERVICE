#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "std_msgs/Bool.h"

class AddMarker
{
  private:
    ros::Publisher marker_pub;
    uint32_t shape;
    visualization_msgs::Marker marker;
    ros::Subscriber goalStatusSubscriber;
    bool statusGoal; 
       
  public:
    AddMarker(ros::NodeHandle *nh)
    {
      
      shape = visualization_msgs::Marker::CYLINDER;
      statusGoal = false;
      marker_pub = nh -> advertise<visualization_msgs::Marker>("visualization_marker", 1);
      goalStatusSubscriber = nh -> subscribe("goalstatus", 10, &AddMarker::callbackGoalStatus, this);
      marker.header.frame_id = "map";
      marker.header.stamp = ros::Time::now();
      
      marker.scale.x = 0.4;
      marker.scale.y = 0.4;
      marker.scale.z = 0.4;
            
      marker.color.r = 0.8f;
      marker.color.g = 1.0f;
      marker.color.b = 0.0f;
      marker.color.a = 1.0;

      marker.ns = "add_markers";
      marker.id = 0;
      marker.type = shape;
      marker.action = visualization_msgs::Marker::ADD;
      marker.lifetime = ros::Duration();
    }

    void setPositionMarker(float x, float y, float w)
    {   
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = x;
        marker.pose.position.y = y;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = w;
        while (marker_pub.getNumSubscribers() < 1)
        {
          ROS_WARN_ONCE("Please create a subscriber to the marker");
          sleep(1);
        }
        marker_pub.publish(marker);
    }

    void setTimeHide(float time)
    {
      marker.lifetime = ros::Duration(time);
    }

    void deleteMarker()
    {
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
    }

    void callbackGoalStatus(const std_msgs::Bool &msg)
    {
      statusGoal = msg.data;
    }

    bool getStatusGoal()
    {
      if(statusGoal)
      {
        ROS_INFO("true received");
        statusGoal = false;
        return true;
      }
      else
      {
        return false;
      }
    }
    
};

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  AddMarker am = AddMarker(&n);
  int goal = 0;
  am.setPositionMarker(0.0, 5.0, 1.0);
  ROS_INFO("Virtual object is on pickup zone");

  while (ros::ok)
  {
    ros::spinOnce();
    if (am.getStatusGoal())
    {
      if (goal == 0)
      {
        ROS_INFO("Virtual removed from pickup zone");
        am.deleteMarker();
      }
      else if (goal == 1)
      {
        ROS_INFO("Virtual object is on drop off zone");
        am.setPositionMarker(0.5, 3.0, 1.0);
      }
      goal++;
    }
  }

}