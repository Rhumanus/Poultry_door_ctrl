/*
 * utils.h
 *
 *  Created on: 4 oct. 2022
 *      Author: hotte
 */
#include "Arduino.h"

#ifndef UTILS_H_
#define UTILS_H_

#define TIME_DELAY_SEND_TEMP_MS 900000 //15 x 60 x 1000 = 900 000

#define ADDR_EEPROM_SUNRISE_HOUR_JAN 0
#define ADDR_EEPROM_SUNRISE_MIN_JAN 1
#define ADDR_EEPROM_SUNRISE_HOUR_FEB 2
#define ADDR_EEPROM_SUNRISE_MIN_FEB 3
#define ADDR_EEPROM_SUNRISE_HOUR_MAR 4
#define ADDR_EEPROM_SUNRISE_MIN_MAR 5
#define ADDR_EEPROM_SUNRISE_HOUR_APR 6
#define ADDR_EEPROM_SUNRISE_MIN_APR 7
#define ADDR_EEPROM_SUNRISE_HOUR_MAY 8
#define ADDR_EEPROM_SUNRISE_MIN_MAY 9
#define ADDR_EEPROM_SUNRISE_HOUR_JUN 10
#define ADDR_EEPROM_SUNRISE_MIN_JUN 11
#define ADDR_EEPROM_SUNRISE_HOUR_JUL 12
#define ADDR_EEPROM_SUNRISE_MIN_JUL 13
#define ADDR_EEPROM_SUNRISE_HOUR_AUG 14
#define ADDR_EEPROM_SUNRISE_MIN_AUG 15
#define ADDR_EEPROM_SUNRISE_HOUR_SEP 16
#define ADDR_EEPROM_SUNRISE_MIN_SEP 17
#define ADDR_EEPROM_SUNRISE_HOUR_OCT 18
#define ADDR_EEPROM_SUNRISE_MIN_OCT 19
#define ADDR_EEPROM_SUNRISE_HOUR_NOV 20
#define ADDR_EEPROM_SUNRISE_MIN_NOV 21
#define ADDR_EEPROM_SUNRISE_HOUR_DEC 22
#define ADDR_EEPROM_SUNRISE_MIN_DEC 23


#define ADDR_EEPROM_SUNSET_HOUR_JAN 24
#define ADDR_EEPROM_SUNSET_MIN_JAN 25
#define ADDR_EEPROM_SUNSET_HOUR_FEB 26
#define ADDR_EEPROM_SUNSET_MIN_FEB 27
#define ADDR_EEPROM_SUNSET_HOUR_MAR 28
#define ADDR_EEPROM_SUNSET_MIN_MAR 29
#define ADDR_EEPROM_SUNSET_HOUR_APR 30
#define ADDR_EEPROM_SUNSET_MIN_APR 31
#define ADDR_EEPROM_SUNSET_HOUR_MAY 32
#define ADDR_EEPROM_SUNSET_MIN_MAY 33
#define ADDR_EEPROM_SUNSET_HOUR_JUN 34
#define ADDR_EEPROM_SUNSET_MIN_JUN 35
#define ADDR_EEPROM_SUNSET_HOUR_JUL 36
#define ADDR_EEPROM_SUNSET_MIN_JUL 37
#define ADDR_EEPROM_SUNSET_HOUR_AUG 38
#define ADDR_EEPROM_SUNSET_MIN_AUG 39
#define ADDR_EEPROM_SUNSET_HOUR_SEP 40
#define ADDR_EEPROM_SUNSET_MIN_SEP 41
#define ADDR_EEPROM_SUNSET_HOUR_OCT 42
#define ADDR_EEPROM_SUNSET_MIN_OCT 43
#define ADDR_EEPROM_SUNSET_HOUR_NOV 44
#define ADDR_EEPROM_SUNSET_MIN_NOV 45
#define ADDR_EEPROM_SUNSET_HOUR_DEC 46
#define ADDR_EEPROM_SUNSET_MIN_DEC 47

#define ADDR_EEPROM_WIN_SUM_HOUR 50

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
	DOOR_CONTROL_CLOSE = 3,
	RAIN_GAUGE = 4
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

struct DateTime_struct
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
};

struct timePlanDay_struct // structure pour stocker valeur lever et coucher soleil du jour
{
	int hour_remote_master = -1;
	int minute_remote_master = -1;
	int hour_default = -1;
	int minute_default = -1;
	bool maj_remote_master = false;
	bool maj_default = false;
	bool done = false;

};

// enum pour désigner heure hiver ou heure été
enum WinterSummerHour {
	UNKNOWN = 40,
	SUMMER = 41,
	WINTER = 42,
};

#endif /* UTILS_H_ */
