/*
 * GenralHandler.h
 *
 *  Created on: 22 oct. 2022
 *      Author: hotte
 */

#ifndef GENRALHANDLER_H_
#define GENRALHANDLER_H_

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "src/DoorController.h"

class GenralHandler {
public:
	GenralHandler(SoftwareSerial *softSerial);
	SoftwareSerial *HC12_uart;
	DoorController doorController;
	void init();
	void run();


	virtual ~GenralHandler();

private :
	void requestTraitement();
	void answerTraitement();

	String bufferUart;
	bool doorCrtlInProgress;


};

#endif /* GENRALHANDLER_H_ */
