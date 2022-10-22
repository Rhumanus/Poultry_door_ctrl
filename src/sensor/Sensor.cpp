/*
 * Sensor.cpp
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#include "Sensor.h"

/**
 * \brief  Constructeur par defaut de la class Sensor
 * \param  void
 * \return void
 *
 * \details
 */
Sensor::Sensor() {
	this->pin = -1;
}

/**
 * \brief  Constructeur a utiliser de la class Sensor
 * \param  short pin
 * \return void
 *
 * \details
 */
Sensor::Sensor(short pin)
{
	this->pin = pin;
}


/**
 * \brief  Destructeur par defaut de la class Sensor
 * \param  void
 * \return void
 *
 * \details
 */
Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}


/**
 * \brief  Accesseur de l'attribut "pin"
 * \param  void
 * \return short
 *
 * \details
 */
void Sensor::init()
{

}


/**
 * \brief  Accesseur de l'attribut "pin"
 * \param  void
 * \return short
 *
 * \details
 */
short Sensor::getPin()
{
	return this->pin;
}


