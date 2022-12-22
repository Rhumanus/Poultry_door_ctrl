/*
 * DoorController.h
 *
 *  Created on: 22 oct. 2022
 *      Author: hotte
 */


#ifndef DOORCONTROLLER_H_
#define DOORCONTROLLER_H_

#define PIN_K1P A2
#define PIN_K2N A3
#define PIN_FC_HIGH 5
#define PIN_FC_LOW 6
#define PIN_POULTRY_BARRIER 7
#define PIN_CURRENT_MCC A0

#define LIMIT_HIGH_CURRENT_MA 1000 //mA
#define FILTER_DELAY_MEASURE_CURRENT_MS 50

#define SENSIBILITY_ACHS7121_V_p_A 0.185 //0,185 V / A
#define REF_0_ADC_ACHS 490 //valeur ADC (0 - 1024)
#define VREF_ADC_MV 5000 // 5V x 1000

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
	bool flagStopDoorHighCurrent; //TODO

	void init();
	void run();

	void openDoorWithCtrl(bool check_current, bool check_sensor);
	void closeDoorWithCtrl(bool check_current, bool check_sensor);

	int measure_current_intstant_mA(); //TODO
	int measure_current_average_mA(); //TODO

	void stopDoor();
	void downDoor();
	void upDoor();




	DoorController();
	virtual ~DoorController();

private :

	int tab_current_mA[10] = {0};
	int ref_0_adc_achs = 0;
	void superviseAverageCurrent();
	int iteratorAverageCurrentTab = 0; //TODO reset tab + iterator dans une fonction

	bool stopDoorPoultryPresence;
	bool doorDescendingCheck;
	bool doorGoingUpCheck;
	bool currentCheck;

	unsigned long int time_current;
	unsigned long int time_last_check_current;


};

#endif /* DOORCONTROLLER_H_ */
