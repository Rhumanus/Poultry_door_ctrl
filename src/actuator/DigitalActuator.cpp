/*
 * DigitalActuator.cpp
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#include "DigitalActuator.h"


/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
DigitalActuator::DigitalActuator(short pin) : Actuator(pin) {
	this->pin = pin;
	this->state = false;
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
DigitalActuator::~DigitalActuator() {
	// TODO Auto-generated destructor stub
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DigitalActuator::init()
{
	pinMode(this->pin, OUTPUT);
	digitalWrite(this->pin, LOW);
	this->state = false;
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DigitalActuator::setHigh()
{
	digitalWrite(this->pin, HIGH);
	this->state = true;
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DigitalActuator::setLow()
{
	digitalWrite(this->pin, LOW);
	this->state = false;
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
bool DigitalActuator::getState()
{
	return this->state;
}


