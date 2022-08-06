
// Include the necessary packages
#include "ros/ros.h"
#include "std_msgs/Float64.h"

// Main function
int main(int argc, char** argv) {
    
    // Initialize the arm_mover node with the ROS Master
    ros::init(argc, argv, "arm_mover");
    
    // Initialize a node handle object n from the NodeHandle class (this will fully initialize the node AND permits it to communicate with the ROS Master)
    ros::NodeHandle n;
    
    // Create a publisher object that commands joint 1 to move counter-clockwise
    ros::Publisher joint1_pub = n.advertise<std_msgs::Float64>("/simple_arm/joint_1_position_controller/command", 10);
    
    // Create a publisher object that commands joint 2 to move counter-clockwise
    ros::Publisher joint2_pub = n.advertise<std_msgs::Float64>("/simple_arm/joint_2_position_controller/command", 10);
    
    // Set the frequency to 10HZ using the loop_rate object
    // Rates are used to limit the frequency at certain loops cycle (high frequency = unnecessary high CPU usage, low frequency = high latency).
    ros::Rate loop_rate(10);
    
    // Declare variables for starting time, and elapsed
    int start_time, elapsed;

    // While start_time is non-zero (when using ROS with simulated time, ros::Time::now() will initially return 0 until the first message has been received on the /clock topic])
    while (not start_time) {

        // Set the start time to now
        start_time = ros::Time::now().toSec();
    }

    // Infinite loop as long as ROS is working fine
    while (ros::ok()) {

        // Get the elapsed time
        elapsed = ros::Time::now().toSec() - start_time;

        // Set the angles for joint 1 and joint 2. The joint angles are sampled from a sine wave with a period of 10 seconds, and in magnitude from [-pi/2, +pi/2]
        std_msgs::Float64 joint1_angle, joint2_angle;                       // Declare angles for joint 1 and joint 2
        joint1_angle.data = sin(2 * M_PI * 0.1 * elapsed) * (M_PI / 2);     // Set the angle for joint 1
        joint2_angle.data = sin(2 * M_PI * 0.1 * elapsed) * (M_PI / 2);     // Set the angle for joint 1

        // Publish the arm joint angles
        joint1_pub.publish(joint1_angle);
        joint2_pub.publish(joint2_angle);

        // Sleep for the time remaining until 10 Hz is reached
        // Due to this call, the loop is traversed at approximately 10 Hz. If the node receives the signal to shut down (from ROS Master, or the console window), the loop will exit.
        loop_rate.sleep();
    }

    return 0;
}