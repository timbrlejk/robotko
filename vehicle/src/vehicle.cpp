#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

//funkcia ktorú vyvolá subscriber
void kws_dataCallback(const geometry_msgs::Twist& msg );

//hlavná funkcia
int main(int argc, char **argv){

	ros::init(argc, argv, "vehicle");
	ros::NodeHandle n;
	
	wiringPiSetup();
	pinMode(0, OUTPUT);	//set pin 11 (GPIO,GENO) as output
	pinMode(3, OUTPUT);	//set pin 13 (GPIO,GENO) as output	

		
	//vytvorenie subscibera (vyvolá funkciu kws_dataCallback)
	ros::Subscriber sub = n.subscribe("/cmd_vel", 1, kws_dataCallback);

ros::spin();
return 0;
}

void kws_dataCallback(const geometry_msgs::Twist& msg )
{
	//std::cout << "Som vo funkcii" << std::endl;
  //ros::NodeHandle n;
	//zastavilo
	float x = msg.linear.x;
	float z = msg.angular.z;
	
	if(x>16)
		x =16;
	if(x<-16)
		x =-16;
	if(z>16)
		z =16;
	if(z<-16)
		z =-16;
		
	if (x > 0)
		x = x+3;
	if (x < 0)
		x = x-3;

		
	float k2 = 0;
		//x = 0;
		//chod vpred
		if(x <0 )
		{
			x = -x;
			
			k2 = x - (z*x/16)*0.5;
			std::cout << "k2 = " << k2 <<std::endl;
			digitalWrite(0,1); //On
			delay(k2);
			digitalWrite(0,0); //off
			delay(24 - k2);
			x = -x;
			

		}
		
		if(x >0 )
		{
			
			k2 = x - (z*x/16)*0.5;
			std::cout << "k2 = " << k2 <<std::endl;
        	digitalWrite(3,1); //On
			delay(k2);
			digitalWrite(3,0); //off
			delay(24 - k2);
			

		}
		//otacanie okolo vlastnej osi dolava
		if( x == 0  && z > 0)
		{
			
			if (z>3)
				z = 3;
			if(z<2.5)
				z = 0;
			std::cout << "z = " << -z <<std::endl;
			digitalWrite(3,1); //On
			delay(z);
			digitalWrite(3,0); //off
			delay(3.00 - z);
			

		}
		//otacanie okolo vlastnej osi doprava
		if( x == 0  && z < 0)
		{
			z =  -z;
				if (z>3)
				z = 3;
				if(z<2.5)
				z = 0;
			std::cout << "z = " << z <<std::endl;
			digitalWrite(0,1); //On
			delay(z);
			digitalWrite(0,0); //off
			delay(3.00 - z);
			z = -z;
		}
		
		
		x = 0;
		z = 0;
	
		
	
	

	

}

