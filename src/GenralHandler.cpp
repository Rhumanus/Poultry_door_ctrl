/*
 * GenralHandler.cpp
 *
 *  Created on: 22 oct. 2022
 *      Author: hotte
 */

#include "GenralHandler.h"

GenralHandler::GenralHandler(SoftwareSerial *softSerial) {
	this->HC12_uart = softSerial;
	this->bufferUart = "";
	this->doorCrtlInProgress= false;
	this->oneWire = new  OneWire(4);
	this->ds = new DallasTemperature(this->oneWire);
	this->last_time_rq_temp = 0;
	this->RTC = NULL;
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::init(){
	this->HC12_uart->begin(2400);
	this->doorController.init();
	this->ds->begin();

	if(RTC != NULL){

	}
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::run(){
	doorController.run();

	this->checkRTCTime();


	if(this->doorCrtlInProgress) this->answerTraitement();
	if(this->HC12_uart->available()) this->requestTraitement();
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::requestTraitement(){
	this->bufferUart = HC12_uart->readString();

	if(bufferUart == "O_11"){
		this->HC12_uart->print("O_11_ACK/");
		this->doorController.openDoorWithCtrl(true, true);
		this->doorCrtlInProgress = true;
	}
	else if(bufferUart == "O_01"){
		this->HC12_uart->print("O_01_ACK/");
		this->doorController.openDoorWithCtrl(false, true);
		this->doorCrtlInProgress = true;
	}
	else if(bufferUart == "C_11") {
		this->HC12_uart->print("C_11_ACK/");
		this->doorController.closeDoorWithCtrl(true, true);
		this->doorCrtlInProgress = true;
	}
	else if(bufferUart == "C_01") {
		this->HC12_uart->print("C_01_ACK/");
		this->doorController.closeDoorWithCtrl(false, true);
		this->doorCrtlInProgress = true;

	}
	else if(bufferUart == "O_00") {
		this->HC12_uart->print("O_00_ACK/");
		this->doorController.upDoor();
	}
	else if(bufferUart == "C_00") {
		this->HC12_uart->print("C_00_ACK/");
		this->doorController.downDoor();
	}
	else if(bufferUart == "STOP") {
		this->HC12_uart->print("STOP_ACK/");
		this->doorController.stopDoor();
	}

	else if(bufferUart == "FC_L") {
		this->HC12_uart->print("FC_L_ACK/");
		if(this->doorController.FC_low->getState()) this->HC12_uart->print("FC_L_1/");
		else this->HC12_uart->print("FC_L_0/");
	}

	else if(bufferUart == "FC_H") {
		this->HC12_uart->print("FC_H_ACK/");
		if(this->doorController.FC_high->getState()) this->HC12_uart->print("FC_H_1/");
		else this->HC12_uart->print("FC_H_0/");
	}
	else if(bufferUart == "POUL_P") {
		this->HC12_uart->print("POUL_P_ACK/");
		if(this->doorController.poultry_barrier->getState()) this->HC12_uart->print("POUL_P_1/");
		else this->HC12_uart->print("POUL_P_0/");
	}

	else if(bufferUart == "STATE_D") {
		this->HC12_uart->print("STATE_D_ACK/");
		String tmp = "S" + String(this->doorController.FC_low->getState()) + "_" +
				String(this->doorController.FC_high->getState()) + "_" +
				String(this->doorController.poultry_barrier->getState()) + "/";

		this->HC12_uart->print(tmp);
	}

	else if(bufferUart == "TEMP") {
		this->HC12_uart->print("TEMP_ACK/");
		this->getAndSendTemp();
	}



}


/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::answerTraitement(){
	if(this->doorController.flagDoorIsClose){
		this->doorCrtlInProgress = false;
		this->doorController.flagDoorIsClose = false;
		this->HC12_uart->print("C_OK/");
	}
	else if(this->doorController.flagStopDoorHighCurrent)
	{
		this->doorCrtlInProgress = false;
		this->doorController.flagStopDoorHighCurrent = false;
		this->HC12_uart->print("C_KO/");
	}
	if(this->doorController.flagDoorIsOpen){
		this->doorCrtlInProgress = false;
		this->doorController.flagDoorIsOpen = false;
		this->HC12_uart->print("O_OK/");
	}
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
bool GenralHandler::checkTimerTemp(){
	unsigned long tmp = millis() - this->last_time_rq_temp;


	if(tmp == 0) tmp = 4294967295 - this->last_time_rq_temp + millis();

	if(tmp > TIME_DELAY_SEND_TEMP_MS) {
		this->last_time_rq_temp = millis();
		return true;
	}
	else return false;
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::getAndSendTemp(){
	this->ds->requestTemperatures();
	float tmp_temp = this->ds->getTempCByIndex(0);
	int temperature = int(tmp_temp *10);
	Serial.println(tmp_temp);
	String payload = "T" + String(temperature) + "/";
	this->HC12_uart->print(payload);

	Serial.println(payload);


}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::checkRTCTime(){
	DateTime dt = this->RTC->now();
	uint8_t tmp_month_now = dt.month()-1; // -1 car tableau de 0-11 et class RTC 1-12



	//if()

	/*
	Serial.print(dt.year());
	Serial.print(" / ");
	Serial.print(dt.month());
	Serial.print(" / ");
	Serial.print(dt.day());
	Serial.print(" ");
	Serial.print(dt.hour());
	Serial.print(":");
	Serial.print(dt.minute());
	Serial.print(":");
	Serial.println(dt.second());
	 */
	//if(dt.hour() == 13) && dt.minute


}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::initTabCtrlDoor(){

}
/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::checkMajDefaultTimeControlDoor(){
	DateTime dt = this->RTC->now();
	uint8_t tmp_month_now = dt.month()-1;
	if(dt.hour() == 0 && dt.minute() == 1 && !this->sunrise_time_day.maj_default && !this->sunset_time_day.maj_default){
		//MAJ sunrise time default en début de journee 00:01
		this->sunrise_time_day.hour_default = this->sunrise_default_tab[tmp_month_now].hour;
		this->sunrise_time_day.minute_default = this->sunrise_default_tab[tmp_month_now].minute;
		this->sunrise_time_day.maj_default = true;
		this->sunrise_time_day.maj_remote_master = false;

		//MAJ sunset time default en début de journee 00:01
		this->sunset_time_day.hour_default = this->sunset_default_tab[tmp_month_now].hour;
		this->sunset_time_day.minute_default = this->sunset_default_tab[tmp_month_now].minute;
		this->sunset_time_day.maj_default = true;
		this->sunset_time_day.maj_remote_master = false;
	}
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
int GenralHandler::checkSunriseTime(){
	DateTime dt = this->RTC->now();

	if(this->sunrise_time_day.maj_remote_master && !this->sunrise_time_day.done){
		if((this->sunrise_time_day.hour_remote_master == dt.hour()) && (this->sunrise_time_day.minute_remote_master == dt.minute())){
			this->doorController.openDoorWithCtrl(false, true);
			this->doorCrtlInProgress = true;
			this->sunrise_time_day.done = true; //fixme verifier si a mettre ici ou lorsque la descente est finie.
			this->sunrise_time_day.maj_default = false;
			this->sunrise_time_day.maj_remote_master = false;
		}
	}

	else if (this->sunrise_time_day.maj_default && !this->sunrise_time_day.done){
		if((this->sunrise_time_day.hour_default == dt.hour()) && (this->sunrise_time_day.minute_default == dt.minute())){
			this->doorController.openDoorWithCtrl(false, true);
			this->doorCrtlInProgress = true;
			this->sunrise_time_day.done = true; //fixme verifier si a mettre ici ou lorsque la descente est finie.
			this->sunrise_time_day.maj_default = false;
			this->sunrise_time_day.maj_remote_master = false;
		}
	}
	//else return -1; //erreur

	return 0;
}


/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
int GenralHandler::checkSunsetTime(){
	DateTime dt = this->RTC->now();

	if(this->sunset_time_day.maj_remote_master && !this->sunset_time_day.done){
		if((this->sunset_time_day.hour_remote_master == dt.hour()) && (this->sunset_time_day.minute_remote_master == dt.minute())){
			this->doorController.closeDoorWithCtrl(false, true);
			this->doorCrtlInProgress = true;
			this->sunset_time_day.done = true; //fixme verifier si a mettre ici ou lorsque la descente est finie.
			this->sunset_time_day.maj_default = false;
			this->sunset_time_day.maj_remote_master = false;
		}
	}

	else if (this->sunset_time_day.maj_default && !this->sunset_time_day.done){
		if((this->sunset_time_day.hour_default == dt.hour()) && (this->sunset_time_day.minute_default == dt.minute())){
			this->doorController.closeDoorWithCtrl(false, true);
			this->doorCrtlInProgress = true;
			this->sunset_time_day.done = true; //fixme verifier si a mettre ici ou lorsque la descente est finie.
			this->sunset_time_day.maj_default = false;
			this->sunset_time_day.maj_remote_master = false;
		}
	}
	//else return -1; //erreur

	return 0;
}
/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::init_sunrise_tab(){
	//Janvier
	this->sunrise_default_tab[0].month = 0;
	this->sunrise_default_tab[0].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_JAN);
	this->sunrise_default_tab[0].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_JAN);
	//Fevrier
	this->sunrise_default_tab[1].month = 1;
	this->sunrise_default_tab[1].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_FEB);
	this->sunrise_default_tab[1].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_FEB);
	//Mars
	this->sunrise_default_tab[2].month = 2;
	this->sunrise_default_tab[2].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_MAR);
	this->sunrise_default_tab[2].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_MAR);
	//Avril
	this->sunrise_default_tab[3].month = 3;
	this->sunrise_default_tab[3].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_APR);
	this->sunrise_default_tab[3].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_APR);
	//Mai
	this->sunrise_default_tab[4].month = 4;
	this->sunrise_default_tab[4].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_MAY);
	this->sunrise_default_tab[4].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_MAY);
	//Juin
	this->sunrise_default_tab[5].month = 5;
	this->sunrise_default_tab[5].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_JUN);
	this->sunrise_default_tab[5].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_JUN);
	//Juillet
	this->sunrise_default_tab[6].month = 6;
	this->sunrise_default_tab[6].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_JUL);
	this->sunrise_default_tab[6].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_JUL);
	//Aout
	this->sunrise_default_tab[7].month = 7;
	this->sunrise_default_tab[7].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_AUG);
	this->sunrise_default_tab[7].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_AUG);
	//Septembre
	this->sunrise_default_tab[8].month = 8;
	this->sunrise_default_tab[8].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_SEP);
	this->sunrise_default_tab[8].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_SEP);
	//Octobre
	this->sunrise_default_tab[9].month = 9;
	this->sunrise_default_tab[9].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_OCT);
	this->sunrise_default_tab[9].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_OCT);
	//Novembre
	this->sunrise_default_tab[10].month = 10;
	this->sunrise_default_tab[10].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_NOV);
	this->sunrise_default_tab[10].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_NOV);
	//Décembre
	this->sunrise_default_tab[11].month = 11;
	this->sunrise_default_tab[11].hour = EEPROM.read(ADDR_EEPROM_SUNRISE_HOUR_DEC);
	this->sunrise_default_tab[11].minute = EEPROM.read(ADDR_EEPROM_SUNRISE_MIN_DEC);
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::init_sunset_tab(){
	//Janvier
	this->sunrise_default_tab[0].month = 0;
	this->sunrise_default_tab[0].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_JAN);
	this->sunrise_default_tab[0].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_JAN);
	//Fevrier
	this->sunrise_default_tab[1].month = 1;
	this->sunrise_default_tab[1].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_FEB);
	this->sunrise_default_tab[1].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_FEB);
	//Mars
	this->sunrise_default_tab[2].month = 2;
	this->sunrise_default_tab[2].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_MAR);
	this->sunrise_default_tab[2].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_MAR);
	//Avril
	this->sunrise_default_tab[3].month = 3;
	this->sunrise_default_tab[3].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_APR);
	this->sunrise_default_tab[3].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_APR);
	//Mai
	this->sunrise_default_tab[4].month = 4;
	this->sunrise_default_tab[4].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_MAY);
	this->sunrise_default_tab[4].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_MAY);
	//Juin
	this->sunrise_default_tab[5].month = 5;
	this->sunrise_default_tab[5].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_JUN);
	this->sunrise_default_tab[5].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_JUN);
	//Juillet
	this->sunrise_default_tab[6].month = 6;
	this->sunrise_default_tab[6].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_JUL);
	this->sunrise_default_tab[6].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_JUL);
	//Aout
	this->sunrise_default_tab[7].month = 7;
	this->sunrise_default_tab[7].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_AUG);
	this->sunrise_default_tab[7].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_AUG);
	//Septembre
	this->sunrise_default_tab[8].month = 8;
	this->sunrise_default_tab[8].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_SEP);
	this->sunrise_default_tab[8].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_SEP);
	//Octobre
	this->sunrise_default_tab[9].month = 9;
	this->sunrise_default_tab[9].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_OCT);
	this->sunrise_default_tab[9].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_OCT);
	//Novembre
	this->sunrise_default_tab[10].month = 10;
	this->sunrise_default_tab[10].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_NOV);
	this->sunrise_default_tab[10].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_NOV);
	//Décembre
	this->sunrise_default_tab[11].month = 11;
	this->sunrise_default_tab[11].hour = EEPROM.read(ADDR_EEPROM_SUNSET_HOUR_DEC);
	this->sunrise_default_tab[11].minute = EEPROM.read(ADDR_EEPROM_SUNSET_MIN_DEC);

}


GenralHandler::~GenralHandler() {
	// TODO Auto-generated destructor stub
}

