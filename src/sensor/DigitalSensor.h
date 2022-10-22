/*
 * DigitalSensor.h
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#ifndef DIGITALSENSOR_H_
#define DIGITALSENSOR_H_

#include "Sensor.h"

class DigitalSensor : public Sensor{
public:

	//Constructeur / Destructeurs
	DigitalSensor();
	DigitalSensor(short pin);
	virtual ~DigitalSensor();

	//Attributs

	//Méthodes
	void init();
	bool getState();

private:
	bool state;
};
#endif /* DIGITALSENSOR_H_ */
