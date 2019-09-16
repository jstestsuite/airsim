#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <map>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>

struct voxf
{
	float x;
	float y;
	float z;
};

class global_map
{
public:
	global_map()
	{
	//	map<voxf, bool> m;
	}

	~global_map()
	{
	//	delete m;
	}


private:
	static bool isOcupied(voxf check);
	bool add_point(voxf point);
	bool delete_point(voxf point);
	void clear_map();


};