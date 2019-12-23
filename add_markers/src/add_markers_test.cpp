#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
class AddMarker
{
  private:
    ros::Publisher marker_pub;
    uint32_t shape = visualization_msgs::Marker::CYLINDER;
    visualization_msgs::Marker marker;       
  public:
    AddMarker(ros::NodeHandle *nh)
    {
      
      marker_pub = nh -> advertise<visualization_msgs::Marker>("visualization_marker", 1);
      marker.header.frame_id = "map";
      marker.header.stamp = ros::Time::now();
      
      marker.scale.x = 0.5;
      marker.scale.y = 0.5;
      marker.scale.z = 0.5;
            
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
};

int main( int argc, char** argv )
{

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  AddMarker am = AddMarker(&n);
  am.setPositionMarker(0.0, 5.0, 1.0);
  ROS_INFO("Virtual object is on pickup zone");
  ros::Duration(5.0).sleep();
  am.deleteMarker();
  ROS_INFO("Virtual object removed from pickup zone");
  ros::Duration(5.0).sleep();
  ROS_INFO("Virtual object is on drop off zone");

  while(ros::ok) 
  {
    am.setPositionMarker(-0.5, 3.0, 1.0);
  } 
  return 0;
}