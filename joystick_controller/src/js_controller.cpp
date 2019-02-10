#include "joystick_controller/joystick.hh"
#include <unistd.h>
#include <ros/ros.h>
#include <stdlib.h> 
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <iostream>


int main(int argc, char **argv)
{
std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
//deklarovanie pomocnej premennej
int pomocna = 0;
;       
// inicializácia systému, vytvorenie uzla a publishera  	
ros::init(argc, argv, "js_controller");
ros::NodeHandle nh;
ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

// nasledujúci riadok vytvorí a vyplní správu nulami
geometry_msgs::Twist msg;

//nastavenie vstupu joysticku
Joystick joystick("/dev/input/js0");

//vypísanie možnosti ovládania
printf("\n\n X-ova os : pohyb dopredu/dozadu   Y-os : pohyb vlavo/vpravo\n 4 : rovno-vlavo    3: rovno-vpravo    6 : dozadu-vlavo    8 : dozadu-vravo \n zadne tlacidlo paky : zvysenie rychlosti    2 : znizenie rychlosti\n");

//parameter v zátvorkach určuje rýchlosť spúšťania slučky v Hz.
ros::Rate rate(100);
while(ros::ok()){


  //zistenie, či je joystick zapojený (ak nie, podá hlásenie a program vypne)
  if (!joystick.isFound())
  {
    printf("\nJoystick nie je zapojeny!\n");
    exit(1);
  }


  while (true)
  {
   // usleep(1000);
    JoystickEvent event;

    //rozpoznanie toho, či nastala zmena polohy páky, alebo či je lačidlo stlačené
   // if (joystick.sample(&event))
   joystick.sample(&event);
   // {

   
      //rospozná, či sa zmenila poloha páky
      // if (event.isAxis()) {

		// po posune páky dopredu sa vozidlo začne pohybovať rovnakým smerom
		if (event.number == 1 ){//dopredu
		 	msg.linear.x =float((event.value / 15000.0)*10);
		 	
		 		if(msg.linear.x > -5 && msg.linear.x < 5 )
		 			msg.linear.x =0;
		 			
				if(msg.linear.x > 0)
					msg.linear.x = msg.linear.x -5;
				if(msg.linear.x < 0)
					msg.linear.x = msg.linear.x +5;
//		std::cout<< "X: " << float((event.value / 15000.0)*10) << std::endl;
		  // pub.publish(msg); 
		//break;    
                                 }

         // po posune páky dolava sa začne vozidlo otáčať okolo svojej osi smerom dolava
		if (event.number == 0 ){//dolava
		 	msg.angular.z =  float((event.value / 15000.0)*10);
		 	msg.angular.z = (-1) * msg.angular.z;
				if(msg.angular.z > -5 && msg.angular.z < 5 )
		 			msg.angular.z =0;
		 			
		 		if(msg.angular.z > 0)
		 			msg.angular.z =msg.angular.z - 5;
		 		if(msg.angular.z < 0)
		 			msg.angular.z =msg.angular.z + 5;
			//std::cout << "angluar Z: "<< float((event.value / 15000.0)*10) << std::endl;  
            // pub.publish(msg);                      
		//break;  
		}
		std::cout<< "linear X: " << msg.linear.x << std::endl;
		std::cout << "angluar Z: "<< msg.angular.z << std::endl;
		pub.publish(msg);
		//msg.linear.x=0;msg.angular.z=0; 
		//pub.publish(msg);
    // }


	//ros::spinOnce();
	//čaká do spustenia ďalšieho cyklu
	rate.sleep();
    }
 // }
 } 
}
