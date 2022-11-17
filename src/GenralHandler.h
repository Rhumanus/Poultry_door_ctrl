/*
 * GenralHandler.h
 *
 *  Created on: 22 oct. 2022
 *      Author: hotte
 */

#ifndef GENRALHANDLER_H_
#define GENRALHANDLER_H_

#define TIME_DELAY_SEND_TEMP_MS 900000 //15 x 60 x 1000 = 900 000

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DoorController.h"
#include "OneWire.h"
#include "DallasTemperature.h"



class GenralHandler {
public:
	GenralHandler(SoftwareSerial *softSerial);
	SoftwareSerial *HC12_uart;
	DoorController doorController;
	OneWire *oneWire;
	DallasTemperature *ds;

	void init();
	void run();


	virtual ~GenralHandler();

private :

	void requestTraitement();
	void answerTraitement();
	bool checkTimerTemp();
	void getAndSendTemp();

	String bufferUart;
	bool doorCrtlInProgress;

	unsigned long last_time_rq_temp;


};

#endif /* GENRALHANDLER_H_ */
