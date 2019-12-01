#include <global_map.h>
#include <stack> 
//#include <cstdint>
#include <gsl/span>
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/PointCloud2.h>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <map>

#include <chrono>
//typedef std::chrono::high_resolution_clock Clock;

using namespace std;

  void global_map::initialize_ros()
  {
    cam_img = nh_.subscribe<pcl::PointCloud<pcl::PointXYZRGB> >("airsim_node/drone_1/front_left_custom/DepthPlanner/registered/points", 1, &global_map::cam_img_cb, this);
  }
  bool global_map::isOcupied(voxf check)
  {

  }

  bool global_map::add_point(voxf point)
  {

  }

  bool global_map::delete_point(voxf point)
  {

  }

  void global_map::clear_map()
  {

  }

  void global_map::cam_img_cb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& depth_cam)
  {
    auto tes = depth_cam->points[0];
    int num_points = depth_cam->points.size();
    ROS_INFO_STREAM("duration = " << tes.x);
  }

/*
int main(int argc, char **argv)
{
  //ros::Subscriber cam_img;
  ros::init(argc, argv, "global_map");

  ros::NodeHandle nh;
  ros::NodeHandle nh_private("~");;
  global_map test_map(nh, nh_private);
  
  //cam_img = nr.subscribe("airsim_node/drone_1/front_left_custom/DepthPlanner/registered/points", 1, cam_img_cb);
  
  
  printf("this is running \n");  
  
  


  map<tuple<int,int,int>,int> test;
  voxf t = { 1, 1, 1,};
  auto te = make_pair(make_tuple(1,1,1),1);
  test.insert(te);
  //test[t] = 1;
  //auto x = get<0>(te);
ros::spin();
  return 0;
}
*/


/*
add a timer like in airsim_ros_wrapper.cpp line 272 for grabbing the points.  Then work on adding them into the "map"
            ros::TimerOptions timer_options(ros::Duration(update_airsim_img_response_every_n_sec), boost::bind(&AirsimROSWrapper::img_response_timer_cb, this, _1), &img_timer_cb_queue_);
            airsim_img_response_timer_ = nh_private_.createTimer(timer_options);

*32 bytes per point
4 byte (float 32) bigendian so 0x3e346000 comes in as 0x0060343e
y = ''
z = ''
4 blank bytes
4 bytes for color (b g r 255 is how it comes, rgb bigendian)

comes in sparce
fields
  [0]
    name: x
    offset:  0
    datatype:  7
    count:  1
  [1]
    name: y
    offset:  4
    datatype:  7
    count:  1
  [2]
    name: z
    offset:  8
    datatype:  7
    count:  1
  [3]
    name: rgb
    offset:  16
    datatype:  7
    count:  1
is_bigendian: False

*/