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

	if(bufferUart == "O_11"){
		this->HC12_uart->print("O_11_ACK");
		this->doorController.openDoorWithCtrl(true, true);
		this->doorCrtlInProgress = true;
	}
	else if(bufferUart == "O_01"){
		this->HC12_uart->print("O_01_ACK");
		this->doorController.openDoorWithCtrl(false, true);
		this->doorCrtlInProgress = true;
	}
	else if(bufferUart == "C_11") {
		this->HC12_uart->print("C_11_ACK");
		this->doorController.closeDoorWithCtrl(true, true);
		this->doorCrtlInProgress = true;
	}
	else if(bufferUart == "C_01") {
		this->HC12_uart->print("C_01_ACK");
		this->doorController.closeDoorWithCtrl(false, true);
		this->doorCrtlInProgress = true;

	}
	else if(bufferUart == "O_00") {
		this->HC12_uart->print("O_00_ACK");
		this->doorController.upDoor();
	}
	else if(bufferUart == "C_00") {
		this->HC12_uart->print("C_00_ACK");
		this->doorController.downDoor();
	}
	else if(bufferUart == "STOP") {
		this->HC12_uart->print("STOP_ACK");
		this->doorController.stopDoor();
	}
	else if(bufferUart == "FC_L") {
		this->HC12_uart->print("FC_L_ACK");
		//this->doorController.stopDoor(); // todo
	}
	else if(bufferUart == "FC_H") {
		this->HC12_uart->print("FC_H_ACK");
		//this->doorController.stopDoor(); // todo
	}
	else if(bufferUart == "POUL_P") {
		this->HC12_uart->print("POUL_P_ACK");
		//this->doorController.stopDoor(); // todo
	}
	else if(bufferUart == "TEMP") {
		this->HC12_uart->print("TEMP_ACK");
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
		this->HC12_uart->print("C_OK");
	}
	else if(this->doorController.flagStopDoorHighCurrent)
	{
		this->doorCrtlInProgress = false;
		this->doorController.flagStopDoorHighCurrent = false;
		this->HC12_uart->print("C_KO");
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

