#include "ros/ros.h"
//Header of the service message. 
//	The service message belongs to the ros_service package
#include "classwork4/pose.h"
#include "string.h"
#include <tf/transform_listener.h>

using namespace std;

//Callback function
//	Return value: boolean
//		If this function returns true, the service function has been corretly called
//		You can use this value to check if the function has been called with correct parameters
//		i.e. call a service calculating the square of a number, calling the service with a negative number
//	Input values:  the request part of the servive 
//				   the output of the service to fill

bool service_callback( classwork4::pose::Request &req, classwork4::pose::Response &res) {

	tf::TransformListener listener;
    
    tf::StampedTransform transform;
  
        
        try {
            listener.waitForTransform(req.frame_a.data,req.frame_b.data,ros::Time(0),ros::Duration(3.0));
            listener.lookupTransform(req.frame_a.data, req.frame_b.data,ros::Time(0), transform);
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }

       ROS_INFO_STREAM(" Transform: " << 
        
            transform.getOrigin().x() << ", " << 
            transform.getOrigin().y() << ", " <<
            transform.getOrigin().z() << ", " << 
            transform.getRotation().x() << ", " << 
            transform.getRotation().y() << ", " << 
            transform.getRotation().z()
        );
		res.frmb_in_frma.position.x=transform.getOrigin().x();
		res.frmb_in_frma.position.y=transform.getOrigin().y();
		res.frmb_in_frma.position.z=transform.getOrigin().z();
		res.frmb_in_frma.orientation.x=transform.getRotation().x();
		res.frmb_in_frma.orientation.y=transform.getRotation().y();
		res.frmb_in_frma.orientation.z=transform.getRotation().z();
		res.frmb_in_frma.orientation.w=transform.getRotation().w();
          
    
	


	return true;
}


int main(int argc, char **argv) {

	ros::init(argc, argv, "pose_service");
	ros::NodeHandle n;
    
    //while(ros::ok()){

	//Initialize the service object: name of the service and callback function
	//	Like subscribers, also tje callback function can be declared as a class function
	ros::ServiceServer service = n.advertiseService("pose", service_callback);
     
    //}
	//Call the spin function to maintain the node alive
	ros::spin();

	return 0;
}
