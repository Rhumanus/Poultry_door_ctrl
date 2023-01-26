#include "Arduino.h"
#include "src/Framecontroller.h"
#include "src/HC12Controller.h"
#include "SoftwareSerial.h"
#include "src/DoorController.h"
#include "src/GenralHandler.h"
#include "RTClib.h"
#include "Wire.h"

SoftwareSerial HC12_uart (10, 11); // @suppress("Abstract class cannot be instantiated")
RTC_DS1307 RTC;
GenralHandler handler(&HC12_uart);

//DoorController doorController;
/*Frame_controller *FC = new Frame_controller();
HC12Controller *HC12 = new HC12Controller();
frame frame;
 */


int val =0;

String RX_serial;
String TX_serial;

void setup()
{
	delay(1000);

	Serial.begin(9600);
	Wire.begin();
	RTC.begin();

	if (! RTC.begin())
	{
		Serial.println("RTC KO !");
		while (1); // Attente RESET
	}
	else
	{
		Serial.println("Le module RTC est OK");
		RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); // Date du PC
	}

	handler.RTC = &RTC;
	handler.init();

	HC12_uart.print("Poultry_door_ctrl_V0.1 29_12_22/");


	//doorController.init();

}


void loop()
{
	handler.run();
	/*val = analogRead(A0);

	Serial.println(val);
	delay(1000);*/
}
