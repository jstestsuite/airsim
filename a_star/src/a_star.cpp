#include <a_star.h>
#include <g_node.h>
#include <stack> 
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <ctime>
#include <algorithm>

bool isValid(vox in)
{
  int x = in.x;
  int y = in.y;
  int z = in.z;
  if(x <0 || y<0|| z<0 || x>10 ||y>10 ||z> 10)
    return false;
  return true;
}

double calc_d(voxf in, voxf dest)
{
  return (sqrt(abs((in.x-dest.x)*(in.x-dest.x))+abs((in.y-dest.y)*(in.y-dest.y))+abs((in.z-dest.z)*(in.z-dest.z))));
}

void add_g_node(g_node &new_g, g_node* graph)
{
  for(int j = 0; j<ELEMENTS; j++)
  {

    double dist = calc_d(new_g.data, (graph+j)->data);
    for (int l = 0; l<N; l++)
    {
      if(dist < new_g.head_dist[l])
      { 
        float big = dist;
        int count = l;
        for (int z = l; z<N;z++)
        {
          if(big < new_g.head_dist[z])
          {
            count = z;                
            big = new_g.head_dist[z];
          }
        }
        new_g.head_dist[count] = dist;
        new_g.head[count]  = (graph+j);
          break;
      }
    }
  }
}
voxf rand_vox()
{
  voxf new_vox;
//srand (static_cast <unsigned> (time(0)));
  new_vox.x = x_min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(x_max-x_min)));
  new_vox.y =  y_min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(y_max-y_min)));
  new_vox.z = z_min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(z_max-z_min)));
  return new_vox;

}


void printGraph(struct g_node* graph)
{
  int i;
  for(int j = 0; j< 1; j++)
  {
    printf("start x = %f \n", (graph+j)->data.x);
    for (i = 0; i < N; i++)
    {

      // print current vertex and all ts neighbors
      struct g_node* ptr = (graph+j)->head[i];
      //while (ptr != NULL)
      {
        printf("(%d -> %f)\t", i, ptr->data.x );//,ptr->data.y, ptr->data.z);
        //ptr = ptr->next;
      }

      printf("\n");
    }
}
}







void g_explore(g_node* vin)
{
  for(int i = 0; i < ELEMENTS; i++) 
  { 
    for(int j = 0; j<ELEMENTS; j++)
    {
      if( i !=j)
      {
        double dist = calc_d((vin+i)->data, (vin+j)->data);
        for (int l = 0; l<N; l++)
        {
          if(dist < (vin+i)->head_dist[l])
          { 
            float big = dist;
            int count = l;
            for (int z = l; z<N;z++)
            {
              if(big < (vin+i)->head_dist[z])
              {
                count = z;                
                big = (vin+i)->head_dist[z];
              }
            }
            (vin+i)->head_dist[count] = dist;
            (vin+i)->head[count]  = (vin+j);
              break;
          }
        }
      }
    }
  }
}

bool isDestination(voxf in, voxf dest)
{
  if (sqrt(abs((in.x-dest.x)*(in.x-dest.x))+abs((in.y-dest.y)*(in.y-dest.y))+abs((in.z-dest.z)*(in.z-dest.z))) <= 0.5)
  {
    return true;
  }
  else
  {
    return false;
  }
}

double calculateH(voxf in, voxf dest)
{
  return (sqrt(abs((in.x-dest.x)*(in.x-dest.x))+abs((in.y-dest.y)*(in.y-dest.y))+abs((in.z-dest.z)*(in.z-dest.z))));
}



std::vector<g_node*> makePath(g_node &start, g_node &dest) 
{

    g_node *place;
    place = &dest;

    std::stack<g_node*> path;
    std::vector<g_node*> usablePath;

    while (place->parent->id != start.id)
    {
        path.push(place->parent);
        place = place->parent;          
    }

    path.push(place->parent);

    while (!path.empty())
    {
        g_node *top = path.top();
        path.pop();
        usablePath.emplace_back(top);
    }

    return usablePath;

}


std::vector<g_node*> astar_calc( g_node &start, g_node &dest)
{
  start.h = calculateH(start.data, dest.data);

  bool closedList[ELEMENTS+1]= {false};
  std::vector<g_node*> openList;
  openList.emplace_back(&start);

  while(!openList.empty())
  {
    g_node *node = *openList.begin();
    openList.erase(openList.begin());
    closedList[node->id] = true;

    for (int n = 0; n <N; n++)
    {
      double gNew, hNew, fNew;
      g_node *new_node;
      new_node = node->head[n];
      if (isDestination(new_node->data, dest.data))
      {
       printf("found end \n");
       dest.parent =node;
       return makePath(start, dest);
      }
      if(closedList[new_node->id] == false)
      {
       closedList[new_node->id] = true;
       gNew = node->g + calculateH(node->data,new_node->data);
       hNew = calculateH(new_node->data, dest.data);
       fNew = gNew + hNew;
       //  Check if this path is better than the one already present
        if (new_node->f == FLT_MAX || new_node->f > fNew)
        {
        //set new nodes values and add to open list
         new_node->f = fNew;
         new_node->g = gNew;
         new_node->h = hNew;
         new_node->parent =node;
         openList.emplace_back(new_node);
        }
      }
    }
  }
  //doesnt' actually return anything... should have it make error or something
  printf("ERROR NO END IN SIGHT");
  return openList;
}


int main(int argc, char **argv)
{
;
    ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle nr;
  ros::Publisher path_pub = nr.advertise<nav_msgs::Path>("Path", 50);
  ros::Publisher p_pub = nr.advertise<geometry_msgs::PoseStamped>("pose_path", 50);
 

  int x = 7;
  int y = 3;
  int  z = 10;  
float LO = -10.0;
 float HI = 10.0;
 srand (static_cast <unsigned> (time(0)));

g_node r_g[ELEMENTS];
g_node *rp;
rp = r_g;
 
 for (int i = 0; i<ELEMENTS; i++)
 {
  r_g[i].data= rand_vox();
  r_g[i].id = i;
 }

g_explore(rp);
printf("Built graph \n");

g_node s;
s.id = ELEMENTS+1;
s.data = {0,0,0}; 
g_node e;
e.data = {4,4,4};

add_g_node(s,rp);
add_g_node(e,rp);

std::vector<g_node*> test1 =  astar_calc( s, e);



printf("%d \n \n", x);

nav_msgs:: Path drone_path;  
geometry_msgs::PoseStamped pose;
pose.header.frame_id = "world_enu";
ros::Time current_time, last_time;
current_time = ros::Time::now();
pose.header.stamp = current_time;
drone_path.header.frame_id = "world_enu";
ros::Rate r(3.0);

 
g_node *n;
n = test1.back();
  test1.pop_back();



  pose.pose.position.x = n->data.x;
  pose.pose.position.y = n->data.y;
  pose.pose.position.z = n->data.z;
  drone_path.poses.push_back(pose);

  printf("Starting to advertise path\n");
while (!test1.empty())
{
  n = test1.back();
  test1.pop_back();
  pose.pose.position.x = n->data.x;
  pose.pose.position.y = n->data.y;
  pose.pose.position.z = n->data.z;
  drone_path.poses.push_back(pose);

}
 //while(nr.ok())
  //{

   r.sleep();              
  current_time = ros::Time::now();
    
    path_pub.publish(drone_path);
    p_pub.publish(pose);

 // }




  return 0;
}

