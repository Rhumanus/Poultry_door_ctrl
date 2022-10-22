/*
 * Actuator.cpp
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#include "Actuator.h"

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
Actuator::Actuator() {
	this->pin = 0;

}


Actuator::Actuator(short pin)
{
	this->pin = pin;
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
Actuator::~Actuator()
{

}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void Actuator::init()
{
	pinMode(this->pin, OUTPUT);
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
short Actuator::getPin()
{
	return this->pin;
}


