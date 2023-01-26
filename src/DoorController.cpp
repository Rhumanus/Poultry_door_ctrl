/*
 * DoorController.cpp
 *
 *  Created on: 22 oct. 2022
 *      Author: hotte
 *eee
 */

#include "DoorController.h"

DoorController::DoorController() {
	this->FC_high = new DigitalSensor(PIN_FC_HIGH);
	this->FC_low = new DigitalSensor(PIN_FC_LOW);
	this->current_mcc = new AnalogSensor(PIN_CURRENT_MCC);
	this->poultry_barrier = new DigitalSensor(PIN_POULTRY_BARRIER);
	this->relay_K1p = new DigitalActuator(PIN_K1P);
	this->relay_K2n = new DigitalActuator(PIN_K2N);

	this->doorDescendingCheck = false;
	this->doorGoingUpCheck = false;
	this->currentCheck = false ;
	this->stopDoorPoultryPresence = false;
	this->flagDoorIsClose = false;
	this->flagDoorIsOpen = false;
	this->flagStopDoorHighCurrent = false;

	this->time_current = 0;
	this->time_last_check_current = 0;


}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DoorController::init(){
	this->FC_high->init();
	this->FC_low->init();
	this->current_mcc->init();
	this->poultry_barrier->init();
	this->relay_K1p->init();
	this->relay_K2n->init();

	this->stopDoor();
	this->ref_0_adc_achs = this->current_mcc->getValue();
	Serial.print(this->ref_0_adc_achs);
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DoorController::run(){
	// si porte en train de descendre controller l'état des FC

	//Serial.println("door ctrl run");

	if(this->currentCheck){
		this->superviseAverageCurrent();
		if(this->measure_current_average_mA() > LIMIT_HIGH_CURRENT_MA){
			this->stopDoor(); //arrêter moteur
			this->doorDescendingCheck = false; // porte descendue et en position
			this->stopDoorPoultryPresence = false;
			this->currentCheck = false;
			this->flagStopDoorHighCurrent = true;
		}
	}

	if(doorDescendingCheck){
		//Serial.println("dans if descending check");

		if(this->FC_low->getState()){
			//Serial.println("dans if FC LOW");
			this->stopDoor(); //arrêter moteur
			this->doorDescendingCheck = false; // porte descendue et en position
			this->stopDoorPoultryPresence = false;
			this->currentCheck = false;
			this->flagDoorIsClose = true;

		}
		else{
			//Serial.println("dans else ");
			//Vérif si capteur poule activé et si porte deja stoppée ou non
			if(!this->poultry_barrier->getState() && !this->stopDoorPoultryPresence){ //fixme vérif etat capteurs
				//Serial.println("if 1");
				this->stopDoor(); //arrêter moteur présence poule
				this->stopDoorPoultryPresence = true;
			}
			else if(this->poultry_barrier->getState() && this->stopDoorPoultryPresence){
				//Serial.println("if 2");
				this->downDoor();
				this->stopDoorPoultryPresence = false;
			}

			if(this->currentCheck){ //TODO

			}
		}
	}
	if(doorGoingUpCheck){

		//Serial.println("dans if doorGoingUpCheck");
		if(this->FC_high->getState()){
			this->stopDoor(); //arrêter moteur
			this->doorGoingUpCheck = false; // porte montée et en position
			this->stopDoorPoultryPresence = false;
			this->currentCheck = false;
			this->flagDoorIsOpen = true;
		}
	}
}
/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void  DoorController::openDoorWithCtrl(bool check_current, bool check_sensor){
	this->flagDoorIsOpen = false;
	this->flagDoorIsClose = false;
	this->doorDescendingCheck = false;

	if(check_current) this->currentCheck = true;
	else this->currentCheck = false;

	if(check_sensor) this->doorGoingUpCheck = true;

	if(!this->FC_high->getState()) this->upDoor();

}


/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DoorController::closeDoorWithCtrl(bool check_current, bool check_sensor){
	this->flagDoorIsOpen = false;
	this->flagDoorIsClose = false;
	this->doorGoingUpCheck = false;

	if(check_current) this->currentCheck = true;
	else this->currentCheck = false;

	if(check_sensor) this->doorDescendingCheck = true;

	if(!this->FC_low->getState() && this->poultry_barrier->getState()) this->downDoor();

}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DoorController::stopDoor(){
	Serial.println("stop");

	this->relay_K1p->setLow(); //NF sur "-" et logic inverse
	this->relay_K2n->setLow(); //NF sur "-" et logic inverse

	this->doorDescendingCheck = false; // porte descendue et en position
	this->stopDoorPoultryPresence = false;
	//this->flagDoorIsClose = false;
	this->doorGoingUpCheck = false; // porte montée et en position
	this->currentCheck = false;
	//this->flagDoorIsOpen = false;
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DoorController::downDoor(){
	Serial.println("down");
	this->relay_K1p->setLow();
	this->relay_K2n->setHigh();
}


/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DoorController::upDoor(){
	Serial.println("up");
	this->relay_K1p->setHigh();
	this->relay_K2n->setLow();
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
int DoorController::measure_current_intstant_mA(){
	int tmp_adc = (int)this->current_mcc->getValue();
	int delta_adc = 0;

	if(tmp_adc < ref_0_adc_achs) delta_adc = ref_0_adc_achs - tmp_adc;
	else delta_adc = tmp_adc - ref_0_adc_achs;

	int tmp_tension_mV = (delta_adc * VREF_ADC_MV) / 1024;

	int current_mA = int((float)tmp_tension_mV / SENSIBILITY_ACHS7121_V_p_A);

	Serial.print(current_mA);
	Serial.println("mA");
	return current_mA;

}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
void DoorController::superviseAverageCurrent(){
	if((millis() - this->time_last_check_current) > FILTER_DELAY_MEASURE_CURRENT_MS){

		this->tab_current_mA[this->iteratorAverageCurrentTab] = measure_current_intstant_mA();
		this->time_last_check_current = millis();

		this->iteratorAverageCurrentTab ++;
		if(this->iteratorAverageCurrentTab > 9) this->iteratorAverageCurrentTab = 0;
	}
}

/*
 * \brief
 * \param  void
 * \return void
 *
 * \details
 */
int DoorController::measure_current_average_mA(){
	uint16_t tmp_current = 0;
	int return_current = 0;
	for(int i = 0; i < 10 ; i++){
		tmp_current += this->tab_current_mA[i];
	}
	return_current = tmp_current / 10;

	//Serial.print(return_current);
	//Serial.println("mA");


	return return_current;
}

DoorController::~DoorController() {
	// TODO Auto-generated destructor stub
}

