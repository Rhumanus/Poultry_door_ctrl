#include "Arduino.h"
#include "src/Framecontroller.h"
#include "src/HC12Controller.h"
#include "SoftwareSerial.h"
#include "src/DoorController.h"

SoftwareSerial *HC12_uart (10, 11); // @suppress("Abstract class cannot be instantiated")

DoorController doorController;
/*Frame_controller *FC = new Frame_controller();
HC12Controller *HC12 = new HC12Controller();
frame frame;
*/


String RX_serial;
String TX_serial;

void setup()
{
	Serial.begin(9600);


	doorController.init();

}


void loop()
{
	doorController.run();

	/*
	 * if(mySerial.available()){

		RX_serial = mySerial.readString();

		Serial.println(RX_serial); //Debug

		if(RX_serial == "O_C_FC"){
			mySerial.println("O_OK");

		}
		else if (RX_serial == "close"){
			mySerial.println("close_ec");

		}
		else if (RX_serial == "Temp"){

		}
		else if (RX_serial == "Rain"){

		}
	}
*/
}
