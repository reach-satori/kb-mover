
#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>


int main(int argc, char** argv) {
    
    ros::init(argc, argv, "camera_mount");
    ros::NodeHandle node;
    tf::TransformListener tfer;
    tf::TransformBroadcaster br;

    while (ros::ok()) {
        tf::
    }

}
