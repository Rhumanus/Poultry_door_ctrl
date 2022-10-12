/*
 * Framecontroller.h
 *
 *  Created on: 4 oct. 2022
 *      Author: hotte
 */

#ifndef FRAMECONTROLLER_H_
#define FRAMECONTROLLER_H_

#include "utils.h"


class Frame_controller {
public:
	Frame_controller();

	// méthodes
	void init();

	bool availableFrameReceived(); //savoir si une trame est en attente
	bool availableFrameToSend();
	frame getFrameReceived();  //récupérer trame en attente
	void setFrameToSend(bool value_bool, type_frame type_frame, id_frame id_frame, error_frame error);//préparer trame à envoyer
	void setFrameToSend(int value_int, type_frame type_frame, id_frame id_frame, error_frame error);


	frame *tabFramesReceived [10] = {0};
	frame *tabFrameToSend[10] = {0};

	//Attributs

	virtual ~Frame_controller();

private:


	uint8_t index_tab_received = 0;
	uint8_t index_tab_toSend = 0;
	int encodePayload(frame *frame);
	void decodePayload();
};

#endif /* FRAMECONTROLLER_H_ */
