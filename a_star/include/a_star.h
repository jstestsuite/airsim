
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>

#define N 24
#define ELEMENTS 10000
#define x_max 10
#define x_min -0
#define y_max 10
#define y_min -0
#define z_max 10
#define z_min -0
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


struct voxf
{
	float x;
	float y;
	float z;
};

struct g_node
{
	int id;
	voxf data;
	float head_dist[N];
	g_node* head[N];
	struct g_node *parent = NULL;
	double f = FLT_MAX;
	double  g = FLT_MAX;
	double  h= FLT_MAX;

	g_node()
	{
		for (int i = 0; i <N; i++)
		{
		head_dist[i] = FLT_MAX; //head[i](NULL);
		head[i] = NULL;
		}
	}
	~g_node()
	{
		for(int i = 0; i<N; i++)
			 head[i] = NULL;
	}
};

class a_star
{
public:
	static bool isValid(voxf in);
	static bool isDestination(voxf in, voxf dest);
	static double calculateH(voxf in, voxf dest);
	std::vector<g_node*> astar_calc( g_node start, g_node dest);
	std::vector<g_node*> makePath(g_node start, g_node dest);
	void add_g_node(g_node new_g, g_node* graph);
	voxf rand_vox();	
	void printGraph(struct g_node* graph);
	void find_graph(std::vector<g_node> nodes);
	void graph_connect(g_node*  vin);
    double calc_d(voxf in, voxf dest);
private:

};