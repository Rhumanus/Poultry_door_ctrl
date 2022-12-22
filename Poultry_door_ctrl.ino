#include "Arduino.h"
#include "src/Framecontroller.h"
#include "src/HC12Controller.h"
#include "SoftwareSerial.h"
#include "src/DoorController.h"
#include "src/GenralHandler.h"

SoftwareSerial HC12_uart (10, 11); // @suppress("Abstract class cannot be instantiated")
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

	handler.init();

	HC12_uart.print("XcoucouP");


	//doorController.init();

}


void loop()
{
	handler.run();
	/*val = analogRead(A0);

	Serial.println(val);
	delay(1000);*/
}
