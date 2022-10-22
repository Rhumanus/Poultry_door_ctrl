/*
 * DoorController.h
 *
 *  Created on: 22 oct. 2022
 *      Author: hotte
 */


#ifndef DOORCONTROLLER_H_
#define DOORCONTROLLER_H_

#define PIN_K1P 2
#define PIN_K2N 3
#define PIN_FC_HIGH 4
#define PIN_FC_LOW 5
#define PIN_POULTRY_BARRIER 6
#define PIN_CURRENT_MCC A0




#include "sensor/DigitalSensor.h"
#include "sensor/AnalogSensor.h"
#include "actuator/DigitalActuator.h"


class DoorController {
public:

	DigitalSensor *FC_high; //fin course haut
	DigitalSensor *FC_low;  //fin course bas
	DigitalSensor *poultry_barrier; //IR présence poule
	AnalogSensor *current_mcc; // capteur courant ACS714
	DigitalActuator *relay_K1p; // relais ou le + est branchee
	DigitalActuator *relay_K2n; // relais ou le + est branchee

	bool flagDoorIsClose;
	bool flagDoorIsOpen;

	void init();
	void run();

	void openDoorWithCtrl(bool check_current, bool check_sensor);
	void closeDoorWithCtrl(bool check_current, bool check_sensor);

	void stopDoor();
	void downDoor();
	void upDoor();



	DoorController();
	virtual ~DoorController();

private :

	bool stopDoorPoultryPresence;
	bool doorDescendingCheck;
	bool doorGoingUpCheck;
	bool currentCheck;

	unsigned long int time_current;
	unsigned long int time_last_check_current;


};

#endif /* DOORCONTROLLER_H_ */
