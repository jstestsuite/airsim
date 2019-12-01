#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <map>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>
#include "pcl_ros/point_cloud.h"
#include "pcl/point_cloud.h"
#include "pcl_conversions/pcl_conversions.h"

struct voxf
{
	float x;
	float y;
	float z;
};

class global_map
{
public:
	global_map(const ros::NodeHandle &nh, const ros::NodeHandle &nh_private);
	

	//	map<voxf, bool> m;
	




	void cam_img_cb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& depth_cam);
	static bool isOcupied(voxf check);
    void initialize_ros();
private:

    ros::NodeHandle nh_;
	ros::NodeHandle nh_private_;

	bool add_point(voxf point);
	bool delete_point(voxf point);
	void clear_map();
	ros::Subscriber cam_img;
	


};