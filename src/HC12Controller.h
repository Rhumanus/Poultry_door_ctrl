/*
 * HC12Controller.h
 *
 *  Created on: 4 oct. 2022
 *      Author: hotte
 */


#ifndef HC12CONTROLLER_H_
#define HC12CONTROLLER_H_

#include "utils.h"
#include "Framecontroller.h"

class HC12Controller {
public:
	HC12Controller();
	virtual ~HC12Controller();
/*
	//Methodes
	void init();
	void run();

	void sleep();
	void sendFrame();
*/
	Frame_controller *frameCtrl;



	//Attributs


private :
};

#endif /* HC12CONTROLLER_H_ */
