// Include necessary libraries
#include <asf.h>
#include "wifi.h"
#include "camera.h"
#include "timer_interface.h"
#include "conf_clock.h"
#include "conf_board.h"

// Global variables because 2/3 of us are mechanical engineers and that's just how we roll
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
	
	// Reset the wifi
	resetWifi();
	
	//initialize camera
	init_camera();
	
	// Don't do anything until the wifi chip has connected to the network
	waitForWifiNetworkConnect();
	
	// Write all wifi chip setup commands every time just to be safe
	writeWifiConfigurationCommands();
		
	// Main Loop //////////////////////////////////////////////////////////////////////////////////////////////////		
	while(1){

		// If user has pushed the button to enter web setup, enter this routine
		if(wifi_setup_flag == true){

			// Send the setup web string to the wifi chip
			write_wifi_command("setup web\r\n",3);

			// Clear the flag
			wifi_setup_flag = false;
			waitForWifiNetworkConnect();
		}

		// If user has not requested web setup, try to capture and display an image
		else{

			//Check if connected to a network by polling the network status pin
			if(ioport_get_pin_level(PIN_WIFI_NETWORK_STATUS) == true){

				//if connected, are there any open streams?
				//Write the command to the wifi chip
				write_wifi_command("stream_poll all\r\n",3);

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

			// If all else fails, just reset the wifi chip and wait for it to reconnect to the network
			else{
				resetWifi();
				waitForWifiNetworkConnect();
			}
		}	
	}
}
