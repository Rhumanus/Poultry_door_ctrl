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
#include "DoorController.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "RTClib.h"
#include "utils.h"
#include "EEPROM.h"


class GenralHandler {
public:
	GenralHandler(SoftwareSerial *softSerial);
	SoftwareSerial *HC12_uart;
	DoorController doorController;
	OneWire *oneWire;
	DallasTemperature *ds;
	RTC_DS1307 *RTC;
	void init();
	void run();


	virtual ~GenralHandler();

private :

	void checkRTCTime();
	int checkSunriseTime();
	int checkSunsetTime();
	void checkMajDefaultTimeControlDoor();
	void initTabCtrlDoor();
	void requestTraitement();
	void answerTraitement();
	bool checkTimerTemp();
	void getAndSendTemp();
	void init_sunrise_tab();
	void init_sunset_tab();

	String bufferUart;
	bool doorCrtlInProgress;

	unsigned long last_time_rq_temp;

	DateTime_struct sunrise_default_tab[12] = {};
	DateTime_struct sunset_default_tab[12] = {};

	timePlanDay_struct sunrise_time_day;
	timePlanDay_struct sunset_time_day;



};

#endif /* GENRALHANDLER_H_ */
