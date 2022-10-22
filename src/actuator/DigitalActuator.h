/*
 * DigitalActuator.h
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#ifndef DIGITALACTUATOR_H_
#define DIGITALACTUATOR_H_

#include "Actuator.h"

class DigitalActuator : public Actuator{
public:
	DigitalActuator(short pin);
	virtual ~DigitalActuator();

	void init();
	void setHigh();
	void setLow();
	bool getState();

private :
	bool state;
};

#endif /* DIGITALACTUATOR_H_ */
