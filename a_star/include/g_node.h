/*

#include "ros/ros.h"
//#include <a_star.h>
#include "std_msgs/String.h"
#include <sstream>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>


//how do I want this?
//the graph as a thing kept in the class?
//graph in the g_node as pointers? need a flexible pointer declaration though...


struct voxf
{
	float x;
	float y;
	float z;
};

struct g_node
{
	voxf data;
	float head_dist[N];
	g_node* head[N];
	struct g_node *parent;
	double f, g, h;

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



struct edge
{
	//g_node *src;
	//g_node *dest;
	voxf src;//, dest;
};

class graph
{
public:
	int neighbors = 2;
	//graph();
	
		//neighbors = n;
	
	voxf rand_vox();
	struct g_node* create_g(struct edge edges[], int n);	
	void printGraph(struct g_node* graph);
	void find_graph(std::vector<g_node> nodes);
	void g_explore(g_node*  vin);
 double calc_d(voxf in, voxf dest);
	//~graph();
private:

};
/* 
need to add node
	node needs sub nodes

*/
