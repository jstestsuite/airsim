#include <a_star.h>
#include <stack> 
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>


bool isValid(vox in)
{
  int x = in.x;
  int y = in.y;
  int z = in.z;
  if(x <0 || y<0|| z<0 || x>10 ||y>10 ||z> 10)
    return false;
  return true;
}


bool isDestination(vox in, vox dest)
{
  if (sqrt(abs((in.x-dest.x)*(in.x-dest.x))+abs((in.y-dest.y)*(in.y-dest.y))+abs((in.z-dest.z)*(in.z-dest.z))) <= 0.1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

double calculateH(vox in, vox dest)
{
  return (sqrt(abs((in.x-dest.x)*(in.x-dest.x))+abs((in.y-dest.y)*(in.y-dest.y))+abs((in.z-dest.z)*(in.z-dest.z))));
}

 std::vector<a_node> makePath(a_node map[10][10][10], vox dest) 
{
      //  try 
       // {
         //   cout << "Found a path" << endl;
            int x = dest.x;
            int y = dest.y;
            int z = dest.z;
            std::stack<a_node> path;
            std::vector<a_node> usablePath;

            while (!isDestination(map[x][y][z].parent, {x,y,z}))
            {
                path.push(map[x][y][z]);
                int tempX = map[x][y][z].parent.x;
                int tempY = map[x][y][z].parent.y;
                int tempZ = map[x][y][z].parent.z;
                x = tempX;
                y = tempY;
                z = tempZ;
                

            }
            path.push(map[x][y][z]);

            while (!path.empty())
            {
                a_node top = path.top();
                path.pop();
                usablePath.emplace_back(top);
            }
            return usablePath;
       // }
       // catch(const exception& e)
       // {
        //  printf(%s, e.what());
      //  }
}

std::vector<a_node> astar_calc(vox start, vox dest)
{
//won't work long term.  I need to use doubles for location, so I can
  //use a doubley linked list as my node.  and just have all the connections no locations.
  printf("started");
  bool closedList[10][10][10];
  a_node map[10][10][10];
  for (int i = 0; i <10; i++)
  {
    for  (int j = 0; j <10; j++)
    {
      for  (int k = 0; k <10; k++)
      {
        map[i][j][k].here.x = i;
        map[i][j][k].here.y = j;
        map[i][j][k].here.z = k;
        map[i][j][k].parent ={-1,-1,-1};
        map[i][j][k].f = FLT_MAX;
        map[i][j][k].g = FLT_MAX;
        map[i][j][k].h = FLT_MAX;
        
        closedList[i][j][k] = false;
      }
    }
  }
  //Starting location initialization
  map[start.x][start.y][start.z].f = calculateH(start, dest); 
  map[start.x][start.y][start.z].g = 0.0;
  map[start.x][start.y][start.z].h = calculateH(start, dest);
  map[start.x][start.y][start.z].parent = start;
 // map[start.x][start.y][start.z].f = 0.0;

  std::vector<a_node> openList;
  openList.emplace_back(map[start.x][start.y][start.z]);
  //HERE I USE size of 1000 instead of actual size

  bool destinationFound = false;

  while(!openList.empty())
  {
    a_node node = *openList.begin();
    openList.erase(openList.begin());
    int x = node.here.x;
    int y = node.here.y;
    int z = node.here.z;
    closedList[x][y][z] = true;

    for (int nx = -1; nx <=1; nx++)
    {
      for (int ny = -1; ny <=1; ny++)
      {
        for (int nz = -1; nz <=1; nz++)
        {
          double gNew, hNew, fNew;
          if (isValid({x + nx, y + ny, z+nz})) 
          {
            if (isDestination({x + nx, y + ny, z+nz}, dest))
            {
              //Destination found - make path
              map[x + nx][y + ny][z+nz].parent.x = x;
              map[x + nx][y + ny][z+nz].parent.y = y;
              map[x + nx][y + ny][z+nz].parent.z = z;
              destinationFound = true;
              printf("found end \n");
              return makePath(map, dest);
              //return map;
            }
            else if (closedList[x + nx][y + ny][z+nz] == false)
            {
              gNew = node.g + calculateH({x,y,z},{x + nx, y + ny, z+nz});
              hNew = calculateH({x + nx, y + ny, z+nz}, dest);
              fNew = gNew + hNew;
              // Check if this path is better than the one already present
              if (map[x + nx][y + ny][z+nz].f == FLT_MAX ||
              map[x + nx][y + ny][z+nz].f > fNew)
              {
                // Update the details of this neighbour node
                map[x + nx][y + ny][z+nz].f = fNew;
                map[x + nx][y + ny][z+nz].g = gNew;
                map[x + nx][y + ny][z+nz].h = hNew;
                map[x + nx][y + ny][z+nz].parent.x = x;
                map[x + nx][y + ny][z+nz].parent.y = y;
                map[x + nx][y + ny][z+nz].parent.z = z;
                openList.emplace_back(map[x + nx][y + ny][z+nz]);
              }
            }
          }
        }
      }
    }
  }
}


int main(int argc, char **argv)
{

    ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle nr;
  ros::Publisher path_pub = nr.advertise<nav_msgs::Path>("Path", 50);
  ros::Publisher p_pub = nr.advertise<geometry_msgs::PoseStamped>("pose_path", 50);
  //tf::TransformBroadcaster odom_broadcaster;
  int x = 7;
  int y = 4;
  int  z = 9;
  

std::vector<a_node> test1;
printf("%d \n \n", x);
test1 = astar_calc({1,1,1},{x,y,z});
nav_msgs:: Path drone_path;  
geometry_msgs::PoseStamped pose;
pose.header.frame_id = "map";
ros::Time current_time, last_time;
current_time = ros::Time::now();
pose.header.stamp = current_time;
drone_path.header.frame_id = "map";
ros::Rate r(3.0);
//drone_path.poses.push_back(pose);
 
a_node n;
n = test1.back();
  test1.pop_back();

  printf("Here is node x: %d  y: %d  z: %d  \n", n.here.x, n.here.y, n.here.z);

  pose.pose.position.x = n.here.x;
  pose.pose.position.y = n.here.y;
  pose.pose.position.z = n.here.z;
  drone_path.poses.push_back(pose);
while (!test1.empty())
{
  n = test1.back();
  test1.pop_back();
  pose.pose.position.x = n.here.x;
  pose.pose.position.y = n.here.y;
  pose.pose.position.z = n.here.z;
  drone_path.poses.push_back(pose);
  printf("Here is node x: %d  y: %d  z: %d  f: %f  g: %f  h: %f \n", n.here.x, n.here.y, n.here.z, n.f, n.g, n.h);
}
 while(nr.ok()){

   r.sleep();              
  current_time = ros::Time::now();
    
    path_pub.publish(drone_path);
    p_pub.publish(pose);
 // printf("here is temp %f \n", vv[0].x);
//vox n;
  }
//  printf("here is h %f  %f  %f\n", vv[543].x, vv[543].y, vv[543].z);
  return 0;
}

