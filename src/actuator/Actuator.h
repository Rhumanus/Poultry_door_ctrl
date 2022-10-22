/*
 * Actuator.h
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include "Arduino.h"

class Actuator {
public:
	Actuator();
	Actuator(short pin);
	virtual void init();

	short getPin();

	virtual ~Actuator();

protected:
	short pin;
};

#endif /* ACTUATOR_H_ */
