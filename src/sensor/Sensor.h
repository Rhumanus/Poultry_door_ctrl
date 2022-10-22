/*
 * Sensor.h
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Arduino.h"

class Sensor {
public:
	//Constructeur / Destructeur
	Sensor();
	Sensor(short pin);
	virtual ~Sensor();

	//Méthodes
	short getPin();
	virtual void init();
	//Attributs

protected :
	//Méthodes

	//Attributs
	short pin;

};


#endif /* SENSOR_H_ */
