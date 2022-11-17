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


}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::init(){
	this->HC12_uart->begin(9600);
	this->doorController.init();
	this->ds->begin();
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



	if(this->checkTimerTemp()){
		this->getAndSendTemp();
	}

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

	if(bufferUart == "O_C_FC"){
		this->doorController.openDoorWithCtrl(true, true);
		this->doorCrtlInProgress = true;
	}
	else if(bufferUart == "O_FC"){
		this->doorController.openDoorWithCtrl(false, true);
		this->doorCrtlInProgress = true;
	}
	else if(bufferUart == "C_C_FC") {
		this->doorController.closeDoorWithCtrl(true, true);
		this->doorCrtlInProgress = true;
	}
	else if(bufferUart == "C_FC") {
		this->doorController.closeDoorWithCtrl(false, true);
		this->doorCrtlInProgress = true;

	}
	else if(bufferUart == "O_NC") this->doorController.upDoor();
	else if(bufferUart == "C_NC") this->doorController.downDoor();
	else if(bufferUart == "STOP") this->doorController.stopDoor();

}


/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void GenralHandler::answerTraitement(){
	Serial.println("Dans answer traitement");

	if(this->doorController.flagDoorIsClose){
		this->doorCrtlInProgress = false;
		this->doorController.flagDoorIsClose = false;
		Serial.println("C-OK");
		this->HC12_uart->print("C_OK");
	}
	if(this->doorController.flagDoorIsOpen){
		this->doorCrtlInProgress = false;
		this->doorController.flagDoorIsOpen = false;
		this->HC12_uart->print("O_OK");
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

	String payload = "T" + String(temperature);
	this->HC12_uart->print(payload);

	Serial.println(payload);


}



GenralHandler::~GenralHandler() {
	// TODO Auto-generated destructor stub
}

