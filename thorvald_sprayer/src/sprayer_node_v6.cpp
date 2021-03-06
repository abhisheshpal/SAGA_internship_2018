#include "ros/ros.h"
#include <thorvald_sprayer/CANFrame.h>
#include "commands.h"
#include <cstring>
#include "std_msgs/String.h"
#include <std_srvs/Trigger.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Int8.h>
#include <bitset>


#define NODE_ID 5
#define STICK_WIDTH 165 //cm

using namespace std;

/*List of used TPDO, for more informations look at the roboteq datasheet*/
enum RPDO {rpdo1=0x200,rpdo2=0x300,rpdo3=0x400,rpdo4=0x500};

//https://sprayers101.com/selecting-the-best-nozzle-for-the-job/
/*List of known flow for each mode of the pump in L/h and for 4 nozzles*/
enum flow {LOW=141,MEDIUM=150,HIGH=156};

/*Structure used to store the service request*/
struct Request {
  string state;
  int mode;
};

/*Global variable use to know if the speed of the pump has to be incremented or decremented when pushing the xbox controller button*/
bool g_botToTop = true;



/*##########################################  DECLARATION OF THE CLASS ##########################################*/

class ThorvaldSprayer {

public:

  /* Constructor */
  ThorvaldSprayer() {

    /*Initialing the array of data*/
    for(int i=0;i<8;i++) {
      msg.data.push_back(0);
    }
    serviceRequest.state = "OFF";
    serviceRequest.mode = 1;

    pub_ = n_.advertise<thorvald_sprayer::CANFrame>("/can_frames_device_t",1000);
    sub_pump = n_.subscribe("/can_frames_device_r",1000,&ThorvaldSprayer::pump_feedback,this);
    sub_velocity = n_.subscribe("/odometry/base_raw",1000,&ThorvaldSprayer::tora_feedback,this);
    sub_tasks = n_.subscribe("/sprayer_task",1000,&ThorvaldSprayer::task_callback,this);
    ss_mode = n_.advertiseService("sprayer_MODE",&ThorvaldSprayer::modeCallback,this);
    ss_onoff = n_.advertiseService("sprayer_ONOFF",&ThorvaldSprayer::onoffCallback,this);
  }

  ~ThorvaldSprayer(void) {
  }

  /* Getters and Setters */
  Request getRequest() const { return serviceRequest; };
  ros::Publisher getPublisher() const { return pub_; };
  thorvald_sprayer::CANFrame getMsg() { return msg; };
  int getPressure() { return pressure; };
  void setMsg(const string command[9]);


  /* class member functions */

  void process_data(Request request);
  void display_infos(thorvald_sprayer::CANFrame msg, int count, Request request);
  int* decToBinary(int dec, int binary[8]);


  /*Callback used to trigger commands with the xbox controller*/
  bool onoffCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res) {
    res.success = true;
    res.message = "Trigger command for starting/stopping the sprayer sent";

    if(pump_status == 0) {
      ROS_INFO("Sending ON request\n");
      serviceRequest.state = "ON";
    }
    else {
      ROS_INFO("Sending OFF request\n");
      serviceRequest.state = "OFF";
      serviceRequest.mode = 0;
    }

    return true;
  }


  /*callback for the service client, increment or decrement the motorspeed of the pump (3 modes)*/
  bool modeCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res) {
    res.success = true;
    res.message = "Trigger command for changing mode sent";

    if(pump_status == 0) {
      ROS_WARN("You need to launch the pump before choosing a mode \n");
    }
    else if(g_botToTop && pump_status<4 && serviceRequest.mode<4){
      serviceRequest.mode++;
    }
    else if(g_botToTop && pump_status==4) {  ros::ServiceServer ss_watering;
      g_botToTop = false;
      serviceRequest.mode--;
    }
    else if(!g_botToTop && pump_status>0 && serviceRequest.mode>1) {
      serviceRequest.mode--;
    }
    else if(!g_botToTop && pump_status==1) {
      g_botToTop = true;
      serviceRequest.mode++;
    }

    return true;
  }


  /* Callback for the pump feedback */
  void pump_feedback(const thorvald_sprayer::CANFrame &fb) {
    if(fb.id == 389) {
       pressure = 0;
       pump_status = fb.data[4];

       int binary[8];
       decToBinary(fb.data[1],binary);
       for(int i = 0; i < 8; i++) {
          pressure += (double)binary[i]*pow(2,15-i);
       }
       pressure += (double)fb.data[0];

       //We receive a pressure value between 0 and 10000mV and the sensor can measure from 0 to 6 bar
       pressure = (pressure*6.0)/10000.0;
       ROS_INFO("Current pressure: %0.3f",pressure);

       if(pump_status != 0) {
          ROS_INFO("Pump status: ON");
       }
       else {
          ROS_INFO("Pump status: OFF");
       }

       //TO BE MODIFIED WHEN WELL BE USING MORE PRECISE VALUES
       switch(pump_status) {
         case(2) : { flow = (double)LOW; break; }
         case(3) : { flow = (double)MEDIUM; break; }
         case(4) : { flow = (double)HIGH; break; }
         default : { flow = 0.0; break; }
       }
       ROS_INFO("Current flow: %0.2f", flow);

       //to be modified eventually
       /*Check if the tank is empty*/
       /*
       if(pump_status > 1 && pressure < 1.5) {
         serviceRequest.state = "OFF";
         serviceRequest.mode = 0;
         ROS_ERROR("The tank must be empty, refill it and restart");
       }*/


    }
  }

  //http://docs.ros.org/kinetic/api/nav_msgs/html/msg/Odometry.html
  //Twist for velocity => maybe look at linear x and something else if a rotation occurs
  /* Callback for tora's feedback */
  void tora_feedback(const nav_msgs::Odometry &fb) {
    tora_velocity = fb.twist.twist.linear.x; //m/s   => 1 m/s should be fine
  }

  /*Callback for every tasks send to the pump*/
  void task_callback(const std_msgs::Int8 &task_msg) {
    if(task_msg.data == 1) {
      setMsg(commands::ON);
      serviceRequest.mode = 4;
    }
    else {
      setMsg(commands::ON);
      serviceRequest.mode = 1;
    }
  }



private:

  /*Start the node*/
  ros::NodeHandle n_;

  ros::Publisher pub_;
  ros::Subscriber sub_pump;
  ros::Subscriber sub_velocity;
  ros::Subscriber sub_tasks;
  ros::ServiceServer ss_mode;
  ros::ServiceServer ss_onoff;

  thorvald_sprayer::CANFrame msg;
  Request serviceRequest;
  int pump_status;

  double pressure;
  double tora_velocity;
  double flow;
};



/*##########################################  CLASS MEMBER FUNCTIONS  ##########################################*/


/*Function used to fulfill the message*/
void ThorvaldSprayer::setMsg(const string command[9]) {

  int rpdo = 0;

  if (command[0] == "rpdo1") { rpdo = rpdo1; }
  else if (command[0] == "rpdo2") { rpdo = rpdo2; }
  else if (command[0] == "rpdo3") { rpdo = rpdo3; }
  else if (command[0] == "rpdo4") { rpdo = rpdo4; }
  else {
    ROS_ERROR("Something is wrong with the RPDO used by the command");
  }

  msg.id = rpdo + NODE_ID;

  if(serviceRequest.mode > 1) {
    msg.data[0] = serviceRequest.mode;
    for(int j = 1; j < 8; j++) {
      msg.data[j] = 0;
    }
  }
  else {
    for(int i = 1; i < 9; i++) {
      msg.data[i-1] = atoi(command[i].c_str());
    }
  }

  msg.length = 8;
}



/*Function used to create the correct message according to the action asked by the user*/
void ThorvaldSprayer::process_data(Request request) {

  if(strcmp(request.state.c_str(),"ON") == 0) {
    setMsg(commands::ON);
  }
  else if(strcmp(request.state.c_str(),"OFF") == 0) {
    setMsg(commands::OFF);
  }
  else{
    ROS_WARN("/!\\ Doesn't know which action has to be performed /!\\");
  }
}


/*Conversion from decimal to binary*/
int* ThorvaldSprayer::decToBinary(int dec, int binary[8]) {
   string binarystr = bitset<8>(dec).to_string();
   for(int  i = 0; i < binarystr.length(); i++) {
     //ASCII value for '0'
     if(binarystr[i] == 48) {
        binary[i] = 0;
     }
     //ASCII value for '1'
     else if(binarystr[i] == 49) {
        binary[i] = 1;
     }
   }
   return binary;
}


/*Simple procedure which displays some informations*/
void ThorvaldSprayer::display_infos(thorvald_sprayer::CANFrame msg, int count, Request request) {
  /*Display infos*/
  if(request.state.c_str() != NULL) {
    ROS_INFO("#%d Sending data to RPDO1", count);
  }
  else{
    ROS_INFO("#%d RPDO not implemented yet", count);
  }
  ROS_INFO("ID: %d", msg.id);
  ROS_INFO("Length: %d", msg.length);
  ROS_INFO("Data: [%d,%d,%d,%d,%d,%d,%d,%d]", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6], msg.data[7]);
}




/*##########################################  MAIN  ##########################################*/


int main(int argc, char **argv) {

  /*Initializing the node*/
  ros::init(argc,argv,"sprayer_node_v6");

  ThorvaldSprayer sprayer;

  /*Sleep at a rate of 10Hz*/
  ros::Rate loop_rate(10);

  int count = 0;
  while(ros::ok()) {

    sprayer.process_data(sprayer.getRequest());
    //sprayer.display_infos(sprayer.getMsg(), count, sprayer.getRequest());
    sprayer.getPublisher().publish(sprayer.getMsg());

    ros::spinOnce();

    loop_rate.sleep();
    count++;

  }

  return 0;
}
