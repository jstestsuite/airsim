#include "ros/ros.h"
///#include <a_star.h>
#include "std_msgs/String.h"
#include <sstream>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>


//how do I want this?
//the graph as a thing kept in the class?
//graph in the g_node as pointers? need a flexible pointer declaration though...
#define N 10
#define ELEMENTS 1000
#define x_max 6
#define x_min 0
#define y_max 6
#define y_min 0
#define z_max 6
#define z_min 0

struct vox
{
	float x;
	float y;
	float z;
};

struct g
{
	vox data;
	float head_dist[N];
	g* head[N];
	struct g_node *parent;

	g()
	{
		for (int i = 0; i <N; i++)
		{
		head_dist[i] = FLT_MAX; //head[i](NULL);
		head[i] = NULL;
		}
	}
	~g()
	{
		for(int i = 0; i<N; i++)
			delete head[i];

	}
};

struct g_node
{
	vox data;
	vox dest;
	struct g_node *next;
	struct g_node *parent;
};

struct edge
{
	//g_node *src;
	//g_node *dest;
	vox src;//, dest;
};
class graph
{
public:
	int neighbors;
	graph(int n)
	{
		neighbors = n;
	}
	vox rand_vox();
	struct g* create_g(struct edge edges[], int n);	
	void printGraph(struct g* graph);
	void find_graph(std::vector<g_node> nodes);
	void g_explore(g*  vin);
 double calc_d(vox in, vox dest);
	~graph();
private:

};
/* 
need to add node
	node needs sub nodes

*/