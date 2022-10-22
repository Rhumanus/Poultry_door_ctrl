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
	if(this->doorController.flagDoorIsClose){
		this->doorController.flagDoorIsClose = false;
		this->HC12_uart->print("C_OK");
	}
	if(this->doorController.flagDoorIsOpen){
		this->doorController.flagDoorIsOpen = false;
		this->HC12_uart->print("O_OK");
	}
}

GenralHandler::~GenralHandler() {
	// TODO Auto-generated destructor stub
}

