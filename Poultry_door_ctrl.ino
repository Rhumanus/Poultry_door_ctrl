#include "Arduino.h"
#include "src/Framecontroller.h"
#include "src/HC12Controller.h"
Frame_controller *FC = new Frame_controller();
HC12Controller *HC12 = new HC12Controller();
frame frame;

void setup()
{
	Serial.begin(9600);

	HC12->frameCtrl = FC;

	frame.payload[0] = 'A';
	frame.error = UNDEFINED_ERROR;
	frame.id = UNDEFINED_ID;
	HC12->frameCtrl->init();

	HC12->frameCtrl->setFrameToSend(true, ANSWER, DOOR_CONTROL_OPEN, NONE);

}


void loop()
{
	for(int i =0; i<7; i++){
		Serial.print(HC12->frameCtrl->tabFrameToSend[0]->payload[i], HEX);
		Serial.print(" ");
	}
	Serial.println();
	delay(1000);

}
