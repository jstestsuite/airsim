
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>


struct vox
{
	int x;
	int y;
	int z;
};

struct a_node
{
	vox here;
	vox parent;


	double f, g, h;


};




class a_star
{
public:
	static bool isValid(vox in);
	static bool isDestination(vox in, vox dest);
	static double calculateH(vox in, vox dest);
	std::vector<a_node> astar_calc(vox start, vox dest);
	std::vector<a_node> makePath(a_node map[10][10][10], vox dest);
private:


};