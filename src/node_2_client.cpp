#include "ros/ros.h"

//Header of the service message. 
//	The service message belongs to the ros_service package
#include "classwork4/pose.h"

#include "tf/transform_broadcaster.h"

using namespace std;

int main(int argc, char **argv) {
	
	//Init the ROS node with service_client name
	ros::init(argc, argv, "service_client");
	ros::NodeHandle n;

	tf::TransformBroadcaster br;
    tf::Transform transform;

	//Init the service client. Data to use for the service (the .srv file) and the name of the service
	ros::ServiceClient client = n.serviceClient<classwork4::pose>("pose");
	
	//Define and initialize the service data structure 
	//	This datastructure brings with it the input value (in the request fields) and the output values, in the response field
	classwork4::pose srv;
	cout<<"Inserisci prima terna: ";
	cin>>srv.request.frame_a.data;
	cout<<"\nInserisci seconda terna: ";
	cin>>srv.request.frame_b.data;
    //ROS_INFO("Waiting for the client server");
	ros::Rate r(1); 
	client.waitForExistence();
    while (ros::ok()) {
	
	     //cout<<"SONO prima sendtrasform"<<endl;
          
			
	        //ROS_INFO("Client server up now");

      //  client.waitForExistence();
	  if (!client.call(srv)) {
		ROS_ERROR("Error calling the service");
		return 1;
		}
		

	    transform.setOrigin( tf::Vector3(srv.response.frmb_in_frma.position.x, srv.response.frmb_in_frma.position.y, srv.response.frmb_in_frma.position.z) );
        tf::Quaternion q(srv.response.frmb_in_frma.orientation.x,srv.response.frmb_in_frma.orientation.y,srv.response.frmb_in_frma.orientation.z,srv.response.frmb_in_frma.orientation.w);
		
		

        transform.setRotation(q);
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), srv.request.frame_a.data, "/camera_link"));
        //cout<<"SONO dodo sendtrasform"<<endl;
        r.sleep();
    }

	
	//Wait that in the ROS network, the service sum is advertised
	//	If you call a service and the service has not been advertised, you will have back an error

	
	//Call the service callback
	//	The return value is false if:
	//		- the callback returns false
	//		- the service has not been found in the ROS network


	//Just print the output

	
	return 0;
}
