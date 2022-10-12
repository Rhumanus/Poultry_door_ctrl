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
	UNDEFINED_TYPE  = 0,
	REQUEST = 1,
	ANSWER = 2,
	PARAM = 3,

};

enum id_frame {
	UNDEFINED_ID  = 0,
	TEMPERATURE = 1,
	DOOR_CONTROL_OPEN =2,
	RAIN_GAUGE = 3
};

enum error_frame {
	NONE = 0,
	UNDEFINED_ERROR = 1,
	NO_RESPONSE = 2,
	HIGH_CURRENT = 3,
	POULTRY_PRESENCE = 4,

};

struct frame{
	uint8_t len_payload;
	type_frame type = UNDEFINED_TYPE;
	id_frame id = UNDEFINED_ID;
	error_frame error = NONE;
	bool value_bool = false;
	int value_int = 69;
	char payload[20] = {0};

};




#endif /* UTILS_H_ */
