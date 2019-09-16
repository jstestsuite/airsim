#include <global_map.h>
#include <stack> 
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char **argv)
{
  printf("this is running \n");  

  map<tuple<int,int,int>,int> test;
  voxf t = { 1, 1, 1,};
  auto te = make_pair(make_tuple(1,1,1),1);
  test.insert(te);
  //test[t] = 1;
  //auto x = get<0>(te);

  return 0;
}

//data comes in as:

/*
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