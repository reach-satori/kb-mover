
#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <keyboard_reader/Key.h>
int last_key = 6;// ugly global indicator, maybe i can replace with something nicer later
#define VELOCITY 0.05

void processKey(keyboard_reader::Key kbin) {
    if(kbin.key_pressed) {
        if(kbin.key_name == "Down") {last_key = 0;}
        else if(kbin.key_name == "Left") {last_key = 1;}
        else if(kbin.key_name == "Right") {last_key = 2;}
        else if(kbin.key_name == "Up") {last_key = 3;}
        else if(kbin.key_name == "RightShift") {last_key = 4;}
        else if(kbin.key_name == "RightCtrl") {last_key = 5;}
        else {last_key = 6;}
    }
};



int main(int argc, char** argv) {
    //initializations: ros, node, keyboard_reader subscriber, tf broadcaster and listener and the transform that will be used for the camera movement.
    ros::init(argc, argv, "kb_mover");
    ros::NodeHandle node;
    ros::Subscriber kbsub = node.subscribe("keyboard", 20, processKey);
    static tf::TransformBroadcaster br;
    tf::TransformListener tfer;
    tf::Transform target;
    target.setIdentity();
    //initialization end

    while (ros::ok()){
        
        br.sendTransform(tf::StampedTransform(target, ros::Time::now(), "world", "camera_mount"));
        if (last_key != 6) {
            tf::StampedTransform frontlook, wrld2cam; 
            tfer.lookupTransform("world", "frontframe", ros::Time(0), frontlook);
            //in the above, what we care about is the rotation: rotation of the camerafront in relation to the world. AKA, the orientation of the camera, or where the user is looking.
            tfer.lookupTransform("world", "camera_mount", ros::Time(0), wrld2cam);
            //and here the origin is the important part.


            tf::Vector3 intermediate;
            switch(last_key) {
                case 3 : intermediate = tf::Vector3(1, 0, 0);
                         break;
                case 0 : intermediate = tf::Vector3(-1, 0, 0);
                         break;
                case 2 : intermediate = tf::Vector3(0, 1, 0);
                         break;
                case 1 : intermediate = tf::Vector3(0, -1, 0);
                         break;
                case 4 : intermediate = tf::Vector3(0, 0, 1);
                         break;
                case 5 : intermediate = tf::Vector3(0, 0, -1);
                         break;
            }
            intermediate = tf::quatRotate(frontlook.getRotation(), intermediate);
            intermediate *= VELOCITY;
            target.setOrigin(wrld2cam.getOrigin() += intermediate);

            last_key = 6;
        } 
    ros::spinOnce();
    }

    return 0;
};
