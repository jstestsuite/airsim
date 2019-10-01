#include <global_map.h>
#include <stack> 
//#include <cstdint>
#include <gsl/span>
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/PointCloud2.h>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <map>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

float hex_float(char buff[])
{
  return float (*(float*)buff);
}

void cam_img_cb(const sensor_msgs::PointCloud2::ConstPtr& depth_cam)
{
  //ROS_INFO_STREAM(" got osition_.yaw ");
  int row = depth_cam->row_step;
  ROS_INFO_STREAM("float = "<< 21504*32*32);
  int pointstep = depth_cam->point_step;
  ROS_INFO_STREAM("float = "<< depth_cam->data.size());
  auto value = depth_cam->data;
  //int  value1 = int(value);
  //auto  value2 = depth_cam->data[0];
  //auto  value3 = depth_cam->data[0];
//LOOP THROUGH EVERY 32 BYTES, GRABBING X, Y,Z, AND RGB. USE ITERATOR?
//  CANT MAKE SUBVECTOR EASILY, SO i THINK i NEED TO FIND A GOOD WAY TO CREATE EACH BUFFER WITHOUT JUST DOING  BUF[1] = DATA[1] FOR ALL 32...
 // LOOK INTO USING SPAN
  /*



*/
//for (int i = 0; i < 64; i+32)

//Dont want span, I want to not make a bunch of copies
 // auto start_pos = 1;
//auto length = 10;
//auto span_of_myvec = gsl::make_span(value);
//char my_subspan[10] = span_of_myvec.subspan(start_pos, length);

char arr[4];
//std::clock_t start;


//start = std::clock();


float x;// = 0;
char a[depth_cam->data.size()];
copy(depth_cam->data.begin(),depth_cam->data.end(),a);
//char *p;
NOW I NEED TO GET THE READ IN POINTS PUT INTO A MAP... SO I SHOULD START ON THE H FILE, AND THE FUNCTIONS I WILL USE
STILL NOT CERTAIN I AM DOING THIS IN A GOOD WAY.  I WOULD LIKE TO NOT HAVE TO COPY AND RECREATE ALL KINDS OF DATA
WANT AN EFFICIENT SOLUTION
 auto t1 = Clock::now();
for (auto it = depth_cam->data.begin(); it != depth_cam->data.end(); it+32)
{
 // &arr[0] = it;
  //std::memcpy(&x,a,4);
  std::copy(it,it+4, &x);
  //x = hex_float(arr);
  ROS_INFO_STREAM("float = "<<x);
  std::copy(it+4,it+8, arr);
  x =hex_float(arr);
//  ROS_INFO_STREAM("float = "<<hex_float(arr));
  std::copy(it+8,it+12, arr);
  x =hex_float(arr);
 // ROS_INFO_STREAM("float = "<<hex_float(arr));
  //std::copy(it+16,it+8, arr);
  it = depth_cam->data.end();
}
auto t2 = Clock::now();

 //duration = ( std::clock() - start );// / (double);// CLOCKS_PER_SEC;
    ROS_INFO_STREAM("duration = "<<std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count());

//BUT IT+32


    //Cast to float
   // float value =  hex_float(buffer);

string temptest = "";// value[0]+value[1]+value[2]+value[3];
temptest = char(value[0]) +char(value[1])+char(value[2])+char(value[3]);
    //ROS_INFO_STREAM("value 1 =" << int(value[0])<< " " <<int(value[1])<< " " <<int(value[2])<< " " <<int(value[3]));// << " " << value[2] << " " << value[3]<< " " << value[4]<< " " << value[5]<< " " << value[6]);

}

int main(int argc, char **argv)
{
  //ros::Subscriber cam_img;
  ros::init(argc, argv, "global_map");
  ros::NodeHandle nr;

  ros::Subscriber cam_img;
  cam_img = nr.subscribe("airsim_node/drone_1/front_left_custom/DepthPlanner/registered/points", 1, cam_img_cb);

  printf("this is running \n");  
  std::vector<char> buffer;

  buffer.push_back(0);
  buffer.push_back(192);
  buffer.push_back(164);
  buffer.push_back(193);
      char buff [5];
      buff[1] = 0;
    buff[2] = 192; //c0
    buff[3] = 164; //a4
    buff[4] = 193; //c1

    //Cast to float
    float value;
    char buff2[4];
    //value =  buff[0];
    std::memcpy(&value,&buff[1],4);
   // value = hex_float(&buff[1]);
 // float value =  (*(float*)buff); 
    copy(buffer.begin(),buffer.end(),buff2);
    std::memcpy(&value,buff2,4);
  printf("This is my float : %f \n", value);
 //   printf("This is my float : %i \n", *h);


  map<tuple<int,int,int>,int> test;
  voxf t = { 1, 1, 1,};
  auto te = make_pair(make_tuple(1,1,1),1);
  test.insert(te);
  //test[t] = 1;
  //auto x = get<0>(te);
ros::spin();
  return 0;
}



/*
add a timer like in airsim_ros_wrapper.cpp line 272 for grabbing the points.  Then work on adding them into the "map"
            ros::TimerOptions timer_options(ros::Duration(update_airsim_img_response_every_n_sec), boost::bind(&AirsimROSWrapper::img_response_timer_cb, this, _1), &img_timer_cb_queue_);
            airsim_img_response_timer_ = nh_private_.createTimer(timer_options);

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