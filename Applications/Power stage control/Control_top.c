/*
 * Control_top.c
 *
 *  Created on: 2.8.2015
 *      Author: Janne
 */

#include "Common.h"
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "Command_shell.h"
#include "Control_top.h"
#include "PWM_interface.h"
#include "Timer_interface.h"
#include "DMA_interface.h"
#include "Measurement_scaling.h"

void InitControl(void);
void ControlMain(void);
void PFCVoltageControl(void);
void PFCCurrentControl(void);



float HB_V_P_gain;
float HB_V_I_gain;
float HB_I_P_gain;
float HB_I_I_gain;

float PFCkpV;
float PFCkiV;
float PFCkpI;
float PFCkiI;

float AUX_V_P_gain;
float AUX_V_I_gain;

float Vout_ref;
float DClinkRef;
float AUX_ref;

float HB_duty;
float PFC_duty;
float AUX_duty;

float Uin;
float Iin;
float Udc;

float Ts;

float PFCintegratorV;
float PFCerrorV;
float PFCoutputV;

float PFCrefI;
float PFCintegratorI;
float PFCerrorI;
float PFCoutputI;



bool once_initialized = false;


/*
 * *****************************************************************************
 *              				void InitControl(void)
 *
 * Function consists of all control and controller parameter initializations.
 * The function has a section, where the initializations are done only once
 * after the processor startup. This is tagged as "once_initialized".
 * *****************************************************************************
 */



void InitControl(void)
{
	if(!once_initialized) // Initialize these parameters only at the startup
	{
		HB_V_P_gain = HB_V_P_GAIN;
		HB_V_I_gain = HB_V_I_GAIN;
		HB_I_P_gain = HB_I_P_GAIN;
		HB_I_I_gain = HB_I_I_GAIN;

		PFCkpV = PFC_V_P_GAIN;
		PFCkiV = PFC_V_I_GAIN;
		PFCkpI = PFC_I_P_GAIN;
		PFCkiI = PFC_I_I_GAIN;

		AUX_V_P_gain = AUX_V_P_GAIN;
		AUX_V_I_gain = AUX_V_I_GAIN;

		Vout_ref 	 = HB_VREF;
		DClinkRef	 = PFC_VREF;
		AUX_ref 	 = HB_VREF;

		Ts = 1/CTRL_FREQ;

		SetHB_Fsw((Uint16)HB_FSW);
		SetPFC_Fsw((Uint16)PFC_FSW);
		SetAUX_Fsw((Uint16)AUX_FSW);

		SetHB_DT((Uint16)HB_DEADTIME);
		InitControlTimer(CTRL_FREQ);    // Timer_interface.c

		once_initialized = true;


	}
	PFCoutputV = 0;
    PFCintegratorV = 0;
    PFCerrorV = 0;

	HB_duty = HB_DUTY;
	PFC_duty = PFC_DUTY;
	AUX_duty = AUX_DUTY;
}

void ControlMain(void)
{
    // TODO: Move the functionality to CLA

    // First, copy all the measurements to local variables. Disable all interrupts while doing this.
    DINT;
    Iin = DMABuf1[0]*iin_norm - 0.5; // Input current is normally offset by 0.5 because of the used analog measurement. Compensate the offset here.
    Uin = DMABuf1[2]*uin_norm;
    Udc = DMABuf1[4]*udc_norm;
    EINT;

    // TODO: Check if PFC voltage control could be executed e.g. with 1/10th of frequency
    if (PFCState)
    {
        PFCVoltageControl();
        PFCCurrentControl();
        setPFCDuty(PFCoutputI);
    }
}

void PFCVoltageControl(void)
{

    PFCerrorV  = DClinkRef - Udc;
    PFCoutputV = PFCerrorV * PFCkpV + PFCintegratorV * PFCkiV * Ts;

    if (PFCoutputV >= 0.85)
    {
        PFCoutputV = 0.85;
        PFCintegratorV =  PFCintegratorV - fabs(PFCerrorV)*(0.015);
    }
        else if (PFCoutputV <= 0.00)
    {
        PFCoutputV = 0.00;
        PFCintegratorV = PFCintegratorV + fabs(PFCerrorV)*(0.015);
    }
    else
    {
        PFCintegratorV = PFCerrorV + PFCintegratorV;
    }

}

void PFCCurrentControl(void)
{

    float Imeas;

    if (Iin <= 0)
        Imeas = Iin*-1;
    else
        Imeas = Iin;

    PFCrefI = PFCoutputV*Uin;
    PFCerrorI  = PFCrefI - Imeas;
    PFCoutputI = PFCerrorI * PFCkpI + PFCintegratorI * PFCkiI * Ts + ((1-Uin))*0.4; // 0.4 = approximately the relation between the meas gain of Uin and DC link.

    if (PFCoutputI >= 0.95)
    {
        PFCoutputI = 0.95;
        PFCintegratorI =  PFCintegratorI - fabs(PFCerrorI)*(0.10);
    }
    else if (PFCoutputI <= 0.05)
    {
        PFCoutputI = 0.05;
        PFCintegratorI = PFCintegratorI + fabs(PFCerrorI)*(0.10);
    }
    else
    {
        PFCintegratorI = PFCerrorI + PFCintegratorI;
    }
}

