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

void InitControl(void);
void ControlMain(void);
void PFCVoltageControl(void);
void PFCCurrentControl(void);



float HB_V_P_gain;
float HB_V_I_gain;
float HB_I_P_gain;
float HB_I_I_gain;

float PFC_V_P_gain;
float PFC_V_I_gain;
float PFC_I_P_gain;
float PFC_I_I_gain;

float AUX_V_P_gain;
float AUX_V_I_gain;

float Vout_ref;
float DC_link_ref;
float AUX_ref;

float HB_duty;
float PFC_duty;
float AUX_duty;

float Uin;
float Iin;
float Udc;

bool once_initialized = false;




//#include "control_funcs.h"
//#include "command_shell.h"
//#include "extADC.h"
//#include "PFC_control.h"
//#include "HB_control.h"
//#include "xynergyxs.h"
//#include "misc_funcs.h"
//#include "models.h"
//#include "cap_estimator.h"
//#include <math.h>
//#include <stdio.h>
//
//
//void ControlHB(void);
//void ControlMeasCopy(void);
//void ControlPFC(void);
//void LogValues(void);
//void SoftTrip(void);
//void StartSequence(void);
//void ZeroCrossDetection(void);
//void EstimateCap(void);
//
//void LogCapestimate(void);
//
///* Init values, references and measurement scalings */
//SCALE_VALUES			meas_scale;
//LOW_PASS_FILTER 	VDCLINK_filter;
//REFERENCE_VALUES	ref_value;
//MEASUREMENT_GAINS meas_gain;
//
///* Control output saturation and trip levels */
//TRIP_LEVELS				trip;
//SATURATION_LEVS 	saturlevs;
//
///* Phase locked loop */
//PI_Controller			PI_PLL;
//FPG								THETA_CALC;
//
///* DC capacitor estimator */
//
///* Output capacitor estimator */
//
//bool 			detect_enable 	= appDISABLE;
//bool 			meas_enable			= appFALSE;
//
///* PFC startup & control sequence variables */
//bool 			PFCStart 							= appFALSE;
//bool			PFCStartSequenceReady = appFALSE;
//bool 			DipValueReached 			= appFALSE;
//bool			PhaseFlag							= appFALSE;
//bool			ZeroCrossStartup			= appFALSE;
//bool			ZeroCrossDetected			= appFALSE;
//bool			WaitingZeroCross			= appFALSE;
//bool			ZerocrossStartFlag		= appFALSE;
//bool			disable_ctrl 					= appFALSE;
//
//float 		deb_phase =-0.015; // Verified. DO NOT CHANGE THIS VALUE!
//
//uint32_t 	PFCStartCounter 	= PFC_START_COUNTER_INITVALUE;
//uint16_t	PLL_index 				= 9;
//
///* Log data variables */
//bool 			MeasLog 					= appFALSE;
//uint16_t 	MeasIndex 				= 0;
//uint16_t  MeasIndexCap			= 0;
//uint16_t 	PFCIndex 					= 0;
//float 		MeasLogValues1[MEAS_LOG_MAX];
//float 		MeasLogValues2[MEAS_LOG_MAX];
//float 		MeasLogValues3[MEAS_LOG_MAX];
//float 		MeasLogValues4[MEAS_LOG_MAX];
//float 		MeasLogValues5[MEAS_LOG_MAX];
//float 		MeasLogValues6[MEAS_LOG_MAX];
//
//
//// float 		PFCLogValues[MEAS_LOG_MAX];
//
///* Software trip control values */
//bool 			trips;
//bool 			tripped;
//
///* Measurement data variables*/
//float			OutputVoltage; 							//=	ADC1ConvertedValue[1];
//float 		ShuntCurrent; 							//= ADC3ConvertedValue[0];
//float 		VoltageAdjust; 							//= ADC3ConvertedValue[1];
//float 		DCLinkCurrentPulseRising;  	//= CT_data_rising;
//float 		DCLinkCurrentPulseFalling; 	//= CT_data_falling;
//float 		PFC_Current;							 	//= PFC current, combination of sw1 and sw2 currents
//float 		Vgrid;											//= Rectified grid voltage measurement
//float 		VDC_link;										//= DC_link voltage
//
//float			PFCCurrentProper;
//float			DCCurrentProper;
//float			VDC_linkProper;
//
//float			OutputVoltageProper;
//float			ShuntCurrentProper;
//float			VgridProper;
//float 		Reducted_Isec;
//
//float     VgridFilt;
//float			VDC_linkFilt;
//// float			EstCapValue;
//float			ReferenceVoltage;
//
//uint16_t 		StartDelay;
//
//float			PFCA;
//float			PFCB;
//
//uint16_t FilteredOutput;
//float		 FilteredOutputVoltage;
//
//char 			faultIdx[25];
//
//

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

		PFC_V_P_gain = PFC_V_P_GAIN;
		PFC_V_I_gain = PFC_V_I_GAIN;
		PFC_I_P_gain = PFC_I_P_GAIN;
		PFC_I_I_gain = PFC_I_I_GAIN;

		AUX_V_P_gain = AUX_V_P_GAIN;
		AUX_V_I_gain = AUX_V_I_GAIN;

		Vout_ref 	 = HB_VREF;
		DC_link_ref	 = PFC_VREF;
		AUX_ref 	 = HB_VREF;

		SetHB_Fsw((Uint16)HB_FSW);
		SetPFC_Fsw((Uint16)PFC_FSW);
		SetAUX_Fsw((Uint16)AUX_FSW);

		SetHB_DT((Uint16)HB_DEADTIME);
		InitControlTimer(CTRL_FREQ);    // Timer_interface.c

		once_initialized = true;
	}

	HB_duty = HB_DUTY;
	PFC_duty = PFC_DUTY;
	AUX_duty = AUX_DUTY;
}

void ControlMain(void)
{
    // Refactor this so, that the functionality is run in CLA

    // First, copy all the measurements to local variables. Disable all interrupts while doing this.
    DINT;
    Iin = DMABuf1[0];
    Uin = DMABuf1[2];
    Udc = DMABuf1[4];
    EINT;

}

void PFCVoltageControl(void)
{

}


