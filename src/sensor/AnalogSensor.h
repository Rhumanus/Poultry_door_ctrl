/*
 * AnalogSensor.h
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#ifndef ANALOGSENSOR_H_
#define ANALOGSENSOR_H_

#define VREF 5 //V


#include "Sensor.h"

class AnalogSensor : public Sensor{
public:
	AnalogSensor();
	AnalogSensor(short pin);

	virtual ~AnalogSensor();
	void init();
	uint16_t getValue();
	uint16_t getTension();


private:
	uint16_t value; //0 - 1024
	uint16_t tension; // tension en volts x 100



};

#endif /* ANALOGSENSOR_H_ */
