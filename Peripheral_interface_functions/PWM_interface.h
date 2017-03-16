/*
 * PWM_interface.h
 *
 *  Created on: 4.8.2015
 *      Author: Janne
 */

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

#include "Common.h"
#include "F2806x_Device.h"
#include "F2806x_Examples.h"


extern void SetHB_Fsw(Uint16 HB_Fsw);
extern void SetPFC_Fsw(Uint16 PFC_Fsw);
extern void SetAUX_Fsw(Uint16 AUX_Fsw);
extern void SetHB_DT(Uint16 HB_Deadtime);
extern void setPFCDuty(float duty);

extern void PFCRun(bool state);

extern bool PFCState;



#endif /* PWM_INTERFACE_H_ */
