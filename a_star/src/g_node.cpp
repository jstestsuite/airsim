#include <g_node.h>
#include <stack> 
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <ctime>
#include <algorithm>


	struct g* createGraph(struct edge edges[], int n)
{
	unsigned i;

	// allocate memory for graph data structure
	struct g* graph = (struct g*)malloc(sizeof(struct g));

	// initialize head pointer for all vertices
	for (i = 0; i < N; i++)
		graph->head[i] = NULL;

	// add edges to the directed graph one by one
	for (i = 0; i < n; i++)
	{
		//for (int j = 0; j < N; j++)
		{

		
		// get source and destination vertex
		//vox src = edges[i].src;
	//	graph->data = src;
		//printf("%d \n", src.x);
		//vox dest = edges[i].dest;

		// allocate new node of Adjacency List from src to dest
		struct g* newNode = (struct g*)malloc(sizeof(struct g));
		//newNode->dest = dest;
		//newNode->data = src;
		// point new node to current head
		//newNode->next = graph->head[i];

		// point head pointer to new node
		graph->head[i] = newNode;
		}
	}

	return graph;
}

void printGraph(struct g* graph)
{
	int i;
	for (i = 0; i < N; i++)
	{
		// print current vertex and all ts neighbors
		struct g* ptr = graph->head[i];
		//while (ptr != NULL)
		{
			printf("(%d -> %f)\t", i, ptr->data.x );//,ptr->data.y, ptr->data.z);
			//ptr = ptr->next;
		}

		printf("\n");
	}
}
vox rand_vox()
{
	vox new_vox;
	new_vox.x = x_min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(x_max-x_min)));
	new_vox.y =  y_min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(y_max-y_min)));
	new_vox.z = z_min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(z_max-z_min)));
	return new_vox;

}

void find_graph( std::vector<g_node> nodes)
{	float test2 = FLT_MAX;
	for(std::vector<g_node>::iterator it = nodes.begin(); it != nodes.end(); ++it) 
	{
		//make connection graph
		//
		printf("current: %d \n", *it);
		for(std::vector<g_node>::iterator temp = it+1; temp != nodes.end(); ++temp)
		{
			
			printf("temp: %d \n", *temp);
		}
	}
	//for each node
	//	calc_d as array
	//set lowest n d as neighbors

}

double calc_d(vox in, vox dest)
{
  return (sqrt(abs((in.x-dest.x)*(in.x-dest.x))+abs((in.y-dest.y)*(in.y-dest.y))+abs((in.z-dest.z)*(in.z-dest.z))));
}

g* g_explore(g* vin[])
{
	unsigned i;
	vox src;
	for(std::vector<g>::iterator it = vin.begin(); it != vin.end(); ++it) 
	{
		vox data = it->data;
		point_hold small[N];// = {FLT_MAX, NULL};
		for(std::vector<g>::iterator temp = it+1; temp != vin.end(); ++temp)
		{
			double dist = calc_d(data, it->data);
			for (int i = 0; i<N; i++)
			{
			if(dist < small[i].small)
			{	
				float big = small[i].small;
				int count = 0;

				for (int j = i; j<N;j++)
				{
					if(big >= small[j].small)
					{
						count = j;
						big = small[j].small;
					}
				}
				small[count].small = dist;
			    break;
			}
		}
	}
		for (i = 0; i < N; i++)
		{
			//struct g* newNode = (struct g*)malloc(sizeof(struct g))
			//newNode->data = small[i];
		//	it->head[i] = small[i]->spot;
		}	
	}
	struct g* graph = (struct g*)malloc(sizeof(struct g));
	return graph;
}



int main(int argc, char **argv)
{
	printf("Hello \n");
	std::vector<int> ya = {0,1,2,3,4};
	//find_graph(ya);
 float LO = -10.0;
 float HI = 10.0;
 srand (static_cast <unsigned> (time(0)));

// edge edges[] =
//	{
	//	{ 0, 0,0 }, { 1,1,1 },{ 2, 0,1 }, { 3,2, 1 },
	//	 { 4,0,0 }, { 5, 4,2 }
//	};

	// calculate number of edges
//int n = sizeof(edges)/sizeof(edges[0]);

g *r_g[ELEMENTS];

 for (int i = 0; i<ELEMENTS; i++)
 {
 	r_g[i]->data= rand_vox();
 	//g_declare = g_declare+1;
 	//g_declare->data = { 0, 0,0 };
 }

			//{
g_explore(r_g);

//vox one = rand_vox();
//printf ("%f %f %f \n", one.x, one.y, one.z);
	// construct graph from given edges
//printf("%f \n", r3);
	//struct g *graph = createGraph(edges, n);

	// print adjacency list representation of graph
	//printGraph(g_declare[0]);

	return 0;
}