/*
 * utils.h
 *
 *  Created on: 4 oct. 2022
 *      Author: hotte
 */
#include "Arduino.h"

#ifndef UTILS_H_
#define UTILS_H_

enum type_frame {
	UNDEFINED  = 0,
	TEMPERATURE = 1,
	DOOR_CONTROL = 2,
	RAIN_GAUGE = 3,

};

enum error {
	NONE = 0,
	UNDEFINED = 1,
	NO_RESPONSE = 2,
	HIGH_CURRENT = 3,
	POULTRY_PRESENCE = 4,

};

struct frame{
	uint8_t len;
	type_frame type = UNDEFINED;
	error error = NONE;
	bool value_bool = false;
	int value_int = 0;
	char payload[20] = {0};

};




#endif /* UTILS_H_ */
