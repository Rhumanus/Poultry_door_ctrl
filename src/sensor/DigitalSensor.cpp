/*
 * DigitalSensor.cpp
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#include "DigitalSensor.h"

/**
 * \brief  Constructeur par defaut de la class DigitalSensor
 * \param  void
 * \return void
 *
 * \details
 */
DigitalSensor::DigitalSensor()
{
	this->state = false;
}

/**
 * \brief  Constructeur a utiliser de la class DigitalSensor
 * \param  short pin
 * \return void
 *
 * \details
 */
DigitalSensor::DigitalSensor(short pin) : Sensor(pin)
{
	this->state = false;
}

/**
 * \brief  Destructeur par defaut de la class DigitalSensor
 * \param  void
 * \return void
 *
 * \details
 */
DigitalSensor::~DigitalSensor() {
	// TODO Auto-generated destructor stub
}


/**
 * \brief  Methode d'initialisation de la class DigitalSensor
 * \param  void
 * \return void
 *
 * \details
 */
void DigitalSensor::init()
{
	pinMode(pin, INPUT);
	this->state = digitalRead(this->pin);
}

/**
 * \brief  Methode qui lit et renvoie l'etat de l'entree
 * \param  void
 * \return void
 *
 * \details
 */
bool DigitalSensor::getState()
{
	this->state = digitalRead(this->pin);
	return this->state;
}


