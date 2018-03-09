// Include necessary libraries
#include <asf.h>
#include "wifi.h"
#include "camera.h"
#include "timer_interface.h"
#include "conf_clock.h"
#include "conf_board.h"

// Global variables because we're mechanical engineers
volatile uint32_t receivedMessage;


int main (void)
{
	// boilerplate
	sysclk_init();
	wdt_disable(WDT);
	board_init();
	
	// start the clock that counts the seconds
	configure_tc();
	tc_start(TC0, 0);

	// Configure the Wifi UART communication stuff
	configure_usart_wifi();
	configure_wifi_comm_pin();
	configure_wifi_web_setup_pin();
	
	// Reset the wifi by pulling the wifi reset pin low, then bringing it back high.
	ioport_set_pin_level(PIN_WIFI_RESET,LOW); //reset WIFI
	delay_ms(10);
	ioport_set_pin_level(PIN_WIFI_RESET,HIGH); //turn Wifi Back on
	
	//initialize camera
	init_camera();

	// Variable to store all write commands
	char sendString[80];

	// Don't do anything until the wifi chip has connected to the network
	ioport_set_pin_dir(PIN_WIFI_NETWORK_STATUS,IOPORT_DIR_INPUT);
	uint32_t meas_networkPin = 0;

	while(meas_networkPin==0){
		meas_networkPin = ioport_get_pin_level(PIN_WIFI_NETWORK_STATUS);
		// If user has pushed the button to start wifi setup, do so.
		if(wifi_setup_flag == true){
			// clear and initialize the send string
			for(int ii = 0; ii<80; ii++){
				sendString[ii] = 0;
			}
			// Write the desired message to the appropriate string
			sprintf(sendString, "setup web\r\n");
			// Send the string to the wifi chip
			write_wifi_command(&sendString,3);
			// Clear the flag
			wifi_setup_flag = false;
		}
	}
	
	// Main Loop //////////////////////////////////////////////////////////////////////////////////////////////////		
	while(1){
		// If user has pushed the button to enter web setup, enter this routine
		if(wifi_setup_flag == true){
			// clear the send string
			for(int ii = 0; ii<80; ii++){
				sendString[ii] = 0;
			}
			// write the appropriate command to the wifi chip
			sprintf(sendString, "setup web\r\n");
			// Send the string to the wifi chip
			write_wifi_command(&sendString,3);
			// Clear the flag
			wifi_setup_flag = false;
		}
		// If user has not requested web setup, try to capture and display an image
		else{
			//Check if connected to a network by polling the network status pin
			bool wifiNetworkConnected = ioport_get_pin_level(PIN_WIFI_NETWORK_STATUS); 
			//if connected, are there any open streams?
			if(wifiNetworkConnected == true){
				// Clear the send string												
				for(int ii = 0; ii<80; ii++){
					sendString[ii] = 0;
				}
				// Ask the wifi chip if there are any open streams
				sprintf(sendString, "stream_poll all\r\n");// previous: stream_poll 0\r\n
				//int strlength = strlen(sendString);
				//Write the command to the wifi chip
				write_wifi_command(&sendString,3);
				// Unless the wifi chip responds with command failed (no open connections), capture an image
				if(receivedMessage!=RECIEVE_NONE){
					start_capture();
					write_image_to_file();
				}
				// Otherwise wait a second
				else{
					delay_ms(1000);
				}
			}
			else{
				ioport_set_pin_level(PIN_WIFI_RESET,LOW); //reset WIFI
				delay_ms(50);
				ioport_set_pin_level(PIN_WIFI_RESET,HIGH); //turn Wifi Back on

				while(ioport_get_pin_level(PIN_WIFI_NETWORK_STATUS)==LOW){
					if(wifi_setup_flag == true){
						
						write_wifi_command("setup web\r\n", 3);
						//ioport_set_pin_level(PUSH_BUTTON,LOW);
						wifi_setup_flag = false;
					}
				}
			}
		}	
	}
}
