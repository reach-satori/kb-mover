
#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <keyboard_reader/Key.h>
int last_key = 4;// ugly global indicator, maybe i can replace with something nicer later

void processKey(keyboard_reader::Key kbin) {
    //tf::Quaternion q;
    if(kbin.key_pressed) {
        if(kbin.key_name == "Down") {
            ROS_INFO("TESTING TESTING TESTING");
            last_key = 0;
        }
        else if(kbin.key_name == "Left") {last_key = 1;}
        else if(kbin.key_name == "Right") {last_key = 2;}
        else if(kbin.key_name == "Up") {last_key = 3;}
        else {last_key = 4;}
        //br.sendTransform(rf::StampedTransform(transform, ros::Time::now(), "frontframe", "cameraframe");
    }
};

//int moveCam(

int main(int argc, char** argv) {
    ros::init(argc, argv, "kb_mover");

    ros::NodeHandle node;

    
    ros::Subscriber kbsub = node.subscribe("keyboard", 20, processKey);
    tf::TransformBroadcaster br;
    tf::TransformListener tfer;
    
    //static tf::TransformBroadcaster br;
    //tf::Transformer transformer;
    while (ros::ok()){
        if (last_key != 4) {//put a switch here after testing
            tf::StampedTransform frontlook; 
            tfer.lookupTransform("/rviz_plugin_osvr/head", "frontframe", ros::Time::now(), frontlook);
            br.sendTransform(frontlook) ;
         }
         ros::spinOnce();
    }

    return 0;
};
