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
	void setFrameToSend(frame); //préparer trame à envoyer



	//Attributs

	virtual ~Frame_controller();

private:
	frame *tabFramesReceived [10] = {0};
	frame *tabFrameToSend[10] = {0};

	uint8_t index_tab_received = 0;
	uint8_t index_tab_toSend = 0;
	void encodeFrame();
	void decodeFrame();
};

#endif /* FRAMECONTROLLER_H_ */
