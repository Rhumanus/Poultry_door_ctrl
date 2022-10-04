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
	//TODO
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
void Frame_controller::encodeFrame(){
	//todo
}


//**************************************
void Frame_controller::decodeFrame(){
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
void Frame_controller::setFrameToSend(frame frame){
	*this->tabFrameToSend[this->index_tab_toSend] = frame;
	this->index_tab_toSend;
}

Frame_controller::~Frame_controller() {
	// TODO Auto-generated destructor stub
}

