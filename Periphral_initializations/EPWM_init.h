/*
 * EPWM_init.h
 *
 *  Created on: 30.4.2016
 *      Author: Janne
 */

#ifndef PERIPHRAL_INITIALIZATIONS_EPWM_INIT_H_
#define PERIPHRAL_INITIALIZATIONS_EPWM_INIT_H_

#define PFC_PERIOD 1126 /*(90 MHz / 80 kHz)+1  Note that this is only default value, which is set to variable at startup. Change the variable at PWM_interface.c when switching frequency is changed from outside*/

extern void InitPFCPWM(void);

#endif /* PERIPHRAL_INITIALIZATIONS_EPWM_INIT_H_ */
