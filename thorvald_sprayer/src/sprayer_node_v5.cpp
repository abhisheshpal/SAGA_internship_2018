#include "ros/ros.h"
#include <thorvald_base/CANFrame.h>
#include "commands.h"
#include <cstring>
#include "std_msgs/String.h"
#include <std_srvs/Trigger.h>
#include <bitset>

#define NODE_ID 5

using namespace std;

/*List of used TPDO, for more informations look at the roboteq datasheet*/
enum RPDO {rpdo1=0x200,rpdo2=0x300,rpdo3=0x400,rpdo4=0x500};

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

    pub_ = n_.advertise<thorvald_base::CANFrame>("/can_frames_device_t",1000);
    sub_ = n_.subscribe("/can_frames_device_r",1000,&ThorvaldSprayer::feedBack,this);
    ss_mode = n_.advertiseService("sprayer_MODE",&ThorvaldSprayer::modeCallback,this);
    ss_onoff = n_.advertiseService("sprayer_ONOFF",&ThorvaldSprayer::onoffCallback,this);
  }

  /* Getters and Setters */
  Request getRequest() const { return serviceRequest; };
  ros::Publisher getPublisher() const { return pub_; };
  thorvald_base::CANFrame getMsg() { return msg; };
  int getPressure() { return pressure; };
  void setMsg(const string command[9]);


  /* class member functions */

  void process_data(Request request);
  void display_infos(thorvald_base::CANFrame msg, int count, Request request);


  /*Callback used to trigger commands with the xbox controller*/
  bool onoffCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res) {
    res.success = true;
    res.message = "Trigger command from the controller sent";

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


  /*callback for the service client, increment or decrement the motorspeed of the pump*/
  bool modeCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res) {
    res.success = true;
    res.message = "Trigger command from the controller sent";

    if(pump_status == 0) {
      ROS_WARN("You need to launch the pump before choosing a mode \n");
    }
    else if(g_botToTop && pump_status<10 && serviceRequest.mode<10){
      serviceRequest.mode++;
    }
    else if(g_botToTop && pump_status==10) {
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




  /* Callback for the feedback */
  void feedBack(const thorvald_base::CANFrame &fb) {
    if(fb.id == 389) {
       pressure = 0;
       pump_status = fb.data[4];

       int binary[8];
       decToBinary(fb.data[1],binary);
       for(int i = 0; i < 8; i++) {
          pressure += binary[i]*pow(2,15-i); 
       }
       pressure += fb.data[0];
       ROS_INFO("Current pressure: %d",pressure);

       if(pump_status != 0) {
          ROS_INFO("Pump status: ON");
       }
       else {
          ROS_INFO("Pump status: OFF");
       }
    }
  }

  /*Conversion from decimal to binary*/
  int* decToBinary(int dec, int binary[8]) {
     string binarystr = bitset<8>(dec).to_string();
     for(int  i = 0; i < binarystr.length(); i++) {
       if(binarystr[i] == 48) {
          binary[i] = 0;
       }
       else if(binarystr[i] == 49) {
          binary[i] = 1;
       }
     }
     return binary;
  }


private:

  /*Start the node*/
  ros::NodeHandle n_;

  ros::Publisher pub_;
  ros::Subscriber sub_;
  ros::ServiceServer ss_mode;
  ros::ServiceServer ss_onoff;

  thorvald_base::CANFrame msg;
  Request serviceRequest;
  int pump_status;
  int pressure;
};



/*##########################################  CLASS MEMBER FUNCTION ##########################################*/


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


/*Simple procedure which displays some informations*/
void ThorvaldSprayer::display_infos(thorvald_base::CANFrame msg, int count, Request request) {
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
  ros::init(argc,argv,"sprayer_node_v5");

  ThorvaldSprayer sprayer;

  /*Sleep at a rate of 10Hz*/
  ros::Rate loop_rate(1);

  int count = 0;
  while(ros::ok()) {

    sprayer.process_data(sprayer.getRequest());
    sprayer.display_infos(sprayer.getMsg(), count, sprayer.getRequest());
    sprayer.getPublisher().publish(sprayer.getMsg());

    ros::spinOnce();

    loop_rate.sleep();
    count++;

  }

  return 0;
}
