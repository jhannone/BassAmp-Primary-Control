/*
 * PWM_interface.c
 *
 *  Created on: 4.8.2015
 *      Author: Janne
 */

#include "Common.h"
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "Control_top.h"
#include "EPWM_init.h"
#include "PWM_interface.h"


/* Functions */
void SetHB_Fsw(Uint16 HB_Fsw);
void SetPFC_Fsw(Uint16 PFC_Fsw);
void SetAUX_Fsw(Uint16 AUX_Fsw);
void SetHB_DT(Uint16 HB_Deadtime);
void setPFCDuty(float duty);

void PFCRun(bool state);

bool PFCState = false;


/* Variables */
float PFC_period = PFC_PERIOD; // This needs to be variable to avoid fuckups, when switching frequency is changed (when this is obviousy recalculated).

/* Give duty as float between 0-1 */
/* Trigger the ADC conversions 200 ns before lowering edge of the switching command. Thus I_in is synchronously measured as from the "peak" of the PFC current.
 * AD conversion takes in total 444ns, thus the switching transient has ended before sampling the following Uin and Udc.
 */

void setPFCDuty(float duty)
{
	if (duty > MAXPFCDUTY)
	{
		EPwm1Regs.CMPA.half.CMPA = (Uint16)(MAXPFCDUTY*PFC_period);
		EPwm2Regs.CMPA.half.CMPA = (Uint16)(MAXPFCDUTY*PFC_period);
		EPwm8Regs.TBPHS.half.TBPHS = (Uint16)(PFC_period - (MAXPFCDUTY*PFC_period)+ 22); // Magical number of 22 is the delay to trigger the AD conversions 200ns before lowering edge of the switch command
	}
	else if (duty < MINPFCDUTY)
	{
		EPwm1Regs.CMPA.half.CMPA = (Uint16)(MINPFCDUTY*PFC_period);
		EPwm2Regs.CMPA.half.CMPA = (Uint16)(MINPFCDUTY*PFC_period);
		EPwm8Regs.TBPHS.half.TBPHS = 0;													//When minímum pulse is applied, start measurement immediately when the pulse rises up
	}
	else
	{
		EPwm1Regs.CMPA.half.CMPA = (Uint16)(duty*PFC_period);
		EPwm2Regs.CMPA.half.CMPA = (Uint16)(duty*PFC_period);
		EPwm8Regs.TBPHS.half.TBPHS = (Uint16)(PFC_period - (duty*PFC_period)+22);
	}
}

void PFCRun(bool state)
{
	if (state == false)
	{
		// Use Trip zone to disable PFC PWM
		EALLOW;
		EPwm1Regs.TZFRC.bit.OST = 1;
		EPwm2Regs.TZFRC.bit.OST = 1;
		//EPwm8Regs.TZFRC.bit.OST = 1;
		EDIS;
	}

	if (state == true)
	{
		// Use clear trip zone to enable PFC PWM
		EALLOW;
		EPwm1Regs.TZCLR.bit.OST = 1;
		EPwm2Regs.TZCLR.bit.OST = 1;
		//EPwm8Regs.TZCLR.bit.OST = 1;
		EDIS;
	}

	PFCState = state;
}


void SetHB_Fsw(Uint16 HB_Fsw)
{

}

void SetPFC_Fsw(Uint16 PFC_Fsw)
{

}

void SetAUX_Fsw(Uint16 AUX_Fsw)
{

}

void SetHB_DT(Uint16 HB_Deadtime)
{

}


