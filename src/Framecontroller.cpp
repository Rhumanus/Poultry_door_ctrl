/*
 * Framecontroller.cpp
 *
 *  Created on: 4 oct. 2022
 *      Author: hotte
 */

#include "Framecontroller.h"

Frame_controller::Frame_controller() {
	// TODO Auto-generated constructor stub

}

void Frame_controller::init(){
	for(int i=0; i<10; i++){
		this->tabFrameToSend[i] = new frame;
	}
}
//*********************************************
bool Frame_controller::availableFrameReceived(){
	if(this->index_tab_received > 0) return true;
	else return false;
}

//******************************************
bool Frame_controller::availableFrameToSend(){
	if(this->index_tab_toSend > 0) return true;
	else return false;
}

//**************************************
int Frame_controller::encodePayload(frame *frame){
	frame->payload[0] = 0x02;

	switch (frame->error) {
	case NONE:
		frame->payload[4] = '0';
		break;

	case UNDEFINED_ERROR:
		frame->payload[4] = '1';
		break;

	case NO_RESPONSE:
		frame->payload[4] = '2';
		break;

	case HIGH_CURRENT:
		frame->payload[4] = '3';
		break;

	case POULTRY_PRESENCE:
		frame->payload[4] = '4';
		break;

	default:
		break;
	}
	// *****************************check id frame
	switch (frame->id) {
	case UNDEFINED_ID:
		frame->payload[3] = '0';
		break;

	case TEMPERATURE:
		frame->payload[3] = '1';
		break;

	case DOOR_CONTROL_OPEN:
		frame->payload[3] = '2';
		if(frame->value_bool == true) frame->payload[5] = '1';
		else frame->payload[5] = '0';

		frame->payload[6] = 0x03;
		break;

	case RAIN_GAUGE:
		frame->payload[3] = '3';
		break;

	default:
		break;
	}

	// *****************************check error frame
	switch (frame->error) {
	case UNDEFINED_ID:
		frame->payload[2] = '0';
		break;

	case TEMPERATURE:
		frame->payload[2] = '1';
		break;

	case DOOR_CONTROL_OPEN:
		frame->payload[2] = '2';
		break;

	case RAIN_GAUGE:
		frame->payload[2] = '3';
		break;

	default:
		break;
	}


	return 0;
}


//**************************************
void Frame_controller::decodePayload(){
	//todo

}

//*****************************************
frame Frame_controller::getFrameReceived(){
	frame tmp_frame;
	if(this->index_tab_received > 0){
		tmp_frame = *this->tabFramesReceived[this->index_tab_received];
		this->tabFramesReceived[this->index_tab_received] = 0; //réinit le pointeur
		if(this->tabFramesReceived[this->index_tab_received + 1] == 0) {
			this->index_tab_received = 0;
			//verif si donnes suivante dans tableau si non alors retour index position depart
		}
		else this->index_tab_received ++;
	}
	//fixme traité cas ou pas e données dispos
	return tmp_frame;
}

//*****************************************
void Frame_controller::setFrameToSend(bool bool_value, type_frame type_frame, id_frame id_frame, error_frame error){
	this->tabFrameToSend[index_tab_toSend]->error = error;
	this->tabFrameToSend[index_tab_toSend]->type = type_frame;
	this->tabFrameToSend[index_tab_toSend]->id = id_frame;

	this->encodePayload(this->tabFrameToSend[index_tab_toSend]);


	this->index_tab_toSend++;
}

Frame_controller::~Frame_controller() {
	// TODO Auto-generated destructor stub
}

