/*
 * AnalogSensor.cpp
 *
 *  Created on: 21 oct. 2022
 *      Author: hotte
 */

#include "AnalogSensor.h"


AnalogSensor::AnalogSensor() {
	this->tension = 0;
	this->value = 0;

}

/**
 * \brief
 * \param  short pin
 * \return void
 *
 * \details
 */
AnalogSensor::AnalogSensor(short pin) : Sensor(pin)
{
	this->tension = 0;
	this->value = 0;
}

/**
 * \brief
 * \param  short pin
 * \return void
 *
 * \details
 */
void AnalogSensor::init()
{
	pinMode(pin, INPUT);
}

/**
 * \brief  Methode qui lit et renvoie l'etat de l'entree
 * \param  void
 * \return void
 *
 * \details
 */
uint16_t AnalogSensor::getValue()
{
	this->value = analogRead(this->pin);
	return this->value;
}

/**
 * \brief  Methode qui lit et renvoie l'etat de l'entree
 * \param  void
 * \return void
 *
 * \details
 */
uint16_t AnalogSensor::getTension()
{
	float tmp = 0.0;
	this->value = analogRead(this->pin);
	tmp = ((VREF *100.0) * this->value) / 1023.0;
	this->tension = (uint16_t)tmp;
	//this->tension = ((VREF * 100) * this->value) / 1023; //tension x100

	return this->tension;
}
AnalogSensor::~AnalogSensor() {
	// TODO Auto-generated destructor stub
}



