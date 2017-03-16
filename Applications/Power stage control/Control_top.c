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
#include "Control_interface_functions.h"
#include "PWM_interface.h"


void InitControl(void);


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

Uint16 once_initialized = 0;




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
	if(once_initialized == 0) // Initialize these parameters only at the startup
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

		once_initialized = 1;

	}

	HB_duty = HB_DUTY;
	PFC_duty = PFC_DUTY;
	AUX_duty = AUX_DUTY;
}
//
//	trips 	= appENABLE;
//	tripped = appFALSE;
//
//	/* Trip level init. Change FAULT_LEVEL_x in control_funcs.h if needed */
//	trip.DC_link_voltage	= FAULT_LEVEL_V_DC_LINK * DC_LINK_VOLTAGE_MEAS_GAIN * NORM_ADC_3V;
//	trip.DC_link_current	= FAULT_LEVEL_I_DC_LINK * DC_LINK_CURRENT_MEAS_GAIN * NORM_ADC_3V;
//	trip.Output_voltage		= FAULT_LEVEL_V_OUT 		* V24_VOLTAGE_MEAS_GAIN 		* NORM_ADC_3V;
//	trip.PFC_current			= FAULT_LEVEL_I_PFC 		* SW_CURRENT_MEAS_GAIN 			* NORM_ADC_3V;
//	trip.ID 							= ID_FAULT_NONE;			// Clear faults at the beginning
//
//	/* Control output saturation levels */
//
//	saturlevs.PFC_V_PI_over 	= (float)PFC_V_PI_MAX;
//	saturlevs.PFC_V_PI_under 	= (float)PFC_V_PI_MIN;
//	saturlevs.PFC_I_PI_over 	= (float)PFC_I_PI_MAX;
//	saturlevs.PFC_I_PI_under 	= (float)PFC_I_PI_MIN;
//	saturlevs.HB_V_PI_over 		= (float)HB_V_PI_MAX;
//	saturlevs.HB_V_PI_under 	= (float)HB_V_PI_MIN;
//	saturlevs.HB_I_SOS_over 	= (float)HB_I_SOS_MAX;
//	saturlevs.HB_I_SOS_under 	= (float)HB_I_SOS_MIN;
//
//	/* Measurement circuit gains. Calculated from measurement circuit hardware. Change values in control_funcs.h if needed */
// 	meas_gain.ADC_resolution	= ADC_RESOLUTION;
//
//	meas_gain.V_Grid			= GRID_VOLTAGE_MEAS_GAIN 		* NORM_ADC_3V;
//	meas_gain.I_PFC_SW		= SW_CURRENT_MEAS_GAIN 			* NORM_ADC_3V;
//	meas_gain.V_DC_link		= DC_LINK_VOLTAGE_MEAS_GAIN * NORM_ADC_3V;
//	meas_gain.I_DC_link		= DC_LINK_CURRENT_MEAS_GAIN * NORM_ADC_3V;
//	meas_gain.V_24V				= V24_VOLTAGE_MEAS_GAIN 		* NORM_ADC_3V;
//	meas_gain.I_24V				= V24_CURRENT_MEAS_GAIN 		* NORM_ADC_3V;
//
//	/* Scale values to make the measurement result normalized to be from 0 to 1*/
//	meas_scale.ADC_3V			= NORM_ADC_3V;
//
//	/* Scale values for PWM signals to be valid for FPGA modulators. Put here new values if switching frequency is changed.*/
//	meas_scale.HB_PWM			= HB_60K_FIXED_POINT_ADC_SCALING;
//	meas_scale.PFC_PWM		= PFC_100K_FIXED_POINT_ADC_SCALING;
//
//	/*	reference values	*/
//	ref_value.V_DC_link			= DC_LINK_VOLTAGE_REFERENCE * DC_LINK_VOLTAGE_MEAS_GAIN * NORM_ADC_3V;
//	ref_value.I_MAX_DC_link	= DC_LINK_MAX_CURRENT 			* DC_LINK_CURRENT_MEAS_GAIN * NORM_ADC_3V;
//	ref_value.I_MAX_PFC_SW	= PFC_SW_MAX_CURRENT 				* SW_CURRENT_MEAS_GAIN  		* NORM_ADC_3V;
//	ref_value.V_24V					= V24_REF_VOLTAGE 					* V24_VOLTAGE_MEAS_GAIN 		* NORM_ADC_3V;
//	ref_value.I_MAX_24V			= V24_CURRENT_LIMIT 				* V24_CURRENT_MEAS_GAIN 		* NORM_ADC_3V;
//
//	ReferenceVoltage = V24_REF_VOLTAGE;
//	//startup voltages are needed if the system is to be started without explicit user command
//// 	ref_value.PFC_DC_link_startup_voltage= PFC_STARTUP_VOLTAGE * DC_LINK_VOLTAGE_MEAS_GAIN * NORM_ADC_2V5;
//// 	ref_value.HB_DC_link_startup_voltage= HB_STARTUP_VOLTAGE * DC_LINK_VOLTAGE_MEAS_GAIN * NORM_ADC_2V5;
//
//
//	THETA_CALC.W_ref				= W_REFERENCE;
//	THETA_CALC.Th_reset			= TH_RESET;
//
//	// Initialize PI-controller values
//	PI_PLL.integrator				= 0;
//	PI_PLL.delay						= 0;
//
//	detect_enable 	= appDISABLE;
//	StartDelay 			= 500;
//
//}
//
//
///********************************************************************************/
///*                				void SoftTrip(void)							               		    */
///* SoftTrip function includes system protection features in software.	Trip 		  */
///* functions use the copied values of the measurements, hence the SoftTrip			*/
///* is not atomic function. When a software trip occurs, the function disables HB*/
///* and PFC and indicates the tripped signal. The function also indicates the    */
///* circular log buffer index in order to ease the effort finding the tripped  	*/
///* signal from the log. This function is executed on each control cycle.				*/
///********************************************************************************/
//
//void SoftTrip(void)
//{
//
///* FIXME: If trip occurs on startup sequence, the PFC is enabled again after
//	startup sequence is finished. This is huge potential hazard. */
//
//	if (VDC_link >= trip.DC_link_voltage)
//	{
//		Jokeri_SysControlStructure.PFC_Enable	=PFC_DISABLE;
//		Jokeri_SysControlStructure.HB_Enable	=HB_DISABLE;
//		Jokeri_SysControl(&Jokeri_SysControlStructure);
//		trip.ID	=ID_FAULT_V_DC_LINK;
//
//		if(!tripped)
//		{
//			SetLED(ST_LED1);
//			tripped = appTRUE;
//			cmd_fault();
//			sprintf(faultIdx,"Fault index: %d\r\n", MeasIndex);
//			print_dbg(faultIdx);
//		}
//	}
//
//	if (DCLinkCurrentPulseRising >= (float)0.70)//trip.DC_link_current)		// FIXME: Fix these.
//	{
//		Jokeri_SysControlStructure.PFC_Enable=PFC_DISABLE;
//		Jokeri_SysControlStructure.HB_Enable=HB_DISABLE;
//		Jokeri_SysControl(&Jokeri_SysControlStructure);
//		trip.ID=ID_FAULT_I_DC_LINK;
//
//		if(!tripped)
//		{
//			SetLED(ST_LED1);
//			tripped = appTRUE;
//			cmd_fault();
//			sprintf(faultIdx,"Fault index: %d\r\n", MeasIndex);
//			print_dbg(faultIdx);
//		}
//	}
//
//	if (OutputVoltage >= trip.Output_voltage)
//	{
//		Jokeri_SysControlStructure.PFC_Enable=PFC_DISABLE;
//		Jokeri_SysControlStructure.HB_Enable=HB_DISABLE;
//		Jokeri_SysControl(&Jokeri_SysControlStructure);
//		trip.ID=ID_FAULT_V_OUT;
//
//		if(!tripped)
//		{
//			SetLED(ST_LED1);
//			tripped = appTRUE;
//			cmd_fault();
//			sprintf(faultIdx,"Fault index: %d\r\n", MeasIndex);
//			print_dbg(faultIdx);
//		}
//	}
//
//	if (PFC_Current >= trip.PFC_current)
//	{
//		Jokeri_SysControlStructure.PFC_Enable=PFC_DISABLE;
//		Jokeri_SysControlStructure.HB_Enable=HB_DISABLE;
//		Jokeri_SysControl(&Jokeri_SysControlStructure);
//		trip.ID=ID_FAULT_I_PFC;
//
//		if(!tripped)
//		{
//			SetLED(ST_LED1);
//			tripped = appTRUE;
//			cmd_fault();
//			sprintf(faultIdx,"Fault index: %d\r\n", MeasIndex);
//			print_dbg(faultIdx);
//		}
//	}
//}
//
//
///******************************************************************************/
///*                				void ControlMeasCopy(void)					                */
///*																																						*/
///* This function copies measurement data from ADC output tables and variables */
///* for the use control. This is done to prevent data corruption, hence the 	  */
///* interrupts are disabled during the measurement copy process. 				      */
///* VDC_link is measured with external AD-converted. In the process false      */
///* values are generated due to defficiency of SPI-bus. 												*/
///* All measurement data are normalized between  															*/
///* 0.0 and 1.0 by meas_gain.ADC_resolution or EXT_ADC_DIV_1024 coefficients.  */
///* This function triggers also Software Trip function SoftTrip() when all  		*/
///* measurement data is copied.  																							*/
///******************************************************************************/
//
//void ControlMeasCopy(void)
//{
//
//	// Measurements need to be normalized with max adc meas voltage!
//
//	__disable_irq();
//
//	// Regular AD conversions. These are handled by direct DMA transfers, see XynergyXS_HW_init.c
//	OutputVoltage 						=	(float)ADC1ConvertedValue[0] 				* meas_gain.ADC_resolution;
//	ShuntCurrent 							= (float)ADC3ConvertedValue[0] 				* meas_gain.ADC_resolution;
//	VoltageAdjust 						= (float)ADC3ConvertedValue[1] 				* meas_gain.ADC_resolution;
//	DCLinkCurrentPulseRising  = (float)ADC2ConvertedValue						* meas_gain.ADC_resolution;
//	VDC_link									= (float)ADC3ConvertedValue[2]				* meas_gain.ADC_resolution;
//	Vgrid											= (float)ADC3ConvertedValue[1]				* meas_gain.ADC_resolution;
//
//	if(trips)
//	{
//		SoftTrip();
//	}
//
//	__enable_irq();
//
//	// Injected AD conversions triggered straight from the FPGA modulators.
//	// Injected conversion have to be read in ADC_IRQHandler, DMA is not available, see stm32f4xx_it.c.
//		PFC_Current						= ((float)CSA_data 	+ (float)CSB_data)* meas_gain.ADC_resolution*(float)0.5; //FIXME: � V��rin, mutta toimiva
//
//		PFCCurrentProper 			= PFC_Current 	  * (float)3.3 	* (float)10.5273		*(float)2;
//		DCCurrentProper  			= DCLinkCurrentPulseRising 		  * (float)3.3 				* (float)10.4818;
//		VDC_linkProper	 			= VDC_link 			  * (float)3.3 	* (float)163.9344;
//		ShuntCurrentProper 		= ShuntCurrent 	  * (float)3.3 	* (float)51.641279458108791;		// calibrated 14.11.2013
//		Reducted_Isec 				= DCCurrentProper * (float)6.609397345104917; 									// Primary DC link current reducted to secondary current
//
//		FilteredOutput 				= median_filter(ADC1ConvertedValue[0]);
//		FilteredOutputVoltage = (float)FilteredOutput * meas_gain.ADC_resolution;
//		OutputVoltageProper 	= FilteredOutputVoltage * (float)3.3 * (float)10.240977403773957;  //(float)10.522604282377742;// (float)10.447901784617729; // calibrated 14.11.2013
//
// 		VgridFilt							= MAFilterVin(Vgrid);
//		VDC_linkFilt					= MAFilterVDC(VDC_link);
//
//		VgridProper			 			= VgridFilt			  * (float)3.3  * (float)126.0081;
//
////  		HBModel();						// Run H-bridge model with new measurements
//
//
//
// }
//
//
///********************************************************************************/
///*                					void ControlPFC(void)							                  */
///*																																						  */
///*	ControlPFC is the upper level control section for Power Factor Correction.  */
///* 	This function includes the reference calculation and calls for startup			*/
///*	sequence and PFC voltage and current controls which are located in 					*/
///*	PFC_Control.c.																							 								*/
///*  																																						*/
///*	In this Jokeri revision, the grid voltage measurement through external AD		*/
///*	converter is not valid for control, the grid synchronization is  						*/
///*	done by using grid voltage zero cross detection. Altought in order to use 	*/
///*  grid measurement for control, a SOGI based phase locked loop reference 			*/
///*	generation can be found in SOGI.c. When zero cross rising edge is detected, */
///*	reference	calculation is reseted. Otherwise, the grid reference is absolute */
///*  value of cosine function. 																									*/
///*																																							*/
///*	At the startup, the PFC duty cycle is sloped up. At the end of the slope up */
///*  System waits for the next zero cross, before starting the PFC control. 			*/
///* 	During this wait time, the function produces constant 10% pulse to the PFC.	*/
///********************************************************************************/
//
//
//void ControlPFC(void)
//{
//
//
//	/* Voltage control loop at 5 kHz */
//
//	if (PLL_index >= 9)
//	{
//		PLL_index = 0;
//		PFCVoltageControlPI();
//	}
//	else
//	{
//		PLL_index++;
//	}
//
//	if (PFCStartSequenceReady == appFALSE)
//	{
//		 StartSequence();
//		 if(PFCStart == appTRUE)
//		 {
//			startduty += PFC_START_DUTY_INCREMENT;
//		 }
//		 else
//		 {
//			 startduty = (float)0.1;
//		 }
//
//		DataToFPGA(ID_GDA, (uint16_t)floor(meas_scale.PFC_PWM*startduty));
//// 			DataToFPGA(ID_GDA, (uint16_t)floor(meas_scale.PFC_PWM*(float)0.6));
//	}
//	else
//	{
//		PFCCurrentControlPI();
//// 		DataToFPGA(ID_GDA, (uint16_t)floor(meas_scale.PFC_PWM*(float)0.1));
//		DataToFPGA(ID_GDA, (uint16_t)floor(meas_scale.PFC_PWM*PFC_I_PI.output));
//
//	}
//
//}
//
///********************************************************************************/
///*                					void ControlHB(void)							                  */
///*																																						  */
///*	ControlHB() is the lower level control function for H-bridge control   		  */
///* 	This function includes the voltage and current control calls and utilizes 	*/
///*	the DataToFPGA function for providing the controlled duty cycle value to 		*/
///*  modulator in the FPGA. On each round when the control is run, the function	*/
///*  calls LogValues() function. The functional control code is located in 			*/
///*  HB_Control.c.																								 								*/
///********************************************************************************/
//
//void ControlHB(void)
//{
//
//
//	if(StartDelay > 1)
//	{
//		DataToFPGA(ID_DUTY_HBRIDGE, (uint16_t)floor(meas_scale.HB_PWM*(float)0.1));
//		LogValues();
//		StartDelay--;
//	}
//	else
//	{
//		HBVoltageControlPI();
//		HBCurrentControlSOS();
//		DataToFPGA(ID_DUTY_HBRIDGE, (uint16_t)floor(meas_scale.HB_PWM*HBPhaseShift));
//		LogValues();
//	}
//}
//
//
///********************************************************************************/
///*                					void StartSequence(void)					                  */
///*																																						  */
///*	StartSequence provides the startup functionality for PFC control. During   	*/
///* 	start sequence the PFC duty is ramped up to limit the DC link charge current*/
///*	and giving time for PFC to synchronize itself on the input grid phase. 			*/
///*	The grid synchronisation time is needed in both of the cases, with and			*/
///* 	without applying SOGI.																											*/
//
///*	Startup sequence is divided in two main functionalities: Startup ramp and 	*/
///*	zerocross wait states. In the first state PFCStartCounter counts to an pre-	*/
///*	defined calue MEAS_LOG_MAX (FIXME:v��r� arvo). After reaching the predefined*/
///*  value, the function waits for the next zero crossing event, which trigs the */
///* 	ControlInitPFC(); function. After the system startup is done, the function 	*/
///*  sets the PFCStartSequenceReady flag.																				*/
///********************************************************************************/
//
//
//void StartSequence(void)
//{
//		if(PFCStart == appTRUE)	// This runs PFCStartCounter rounds minimum pulse and records the peak grid voltage
//		{
//			if(--PFCStartCounter == 0)
//			{
//				PFCStart = appFALSE;
//				DipValueReached = appFALSE;
//				WaitingZeroCross = appTRUE;
//				PFCStartCounter = PFC_START_COUNTER_INITVALUE;
//				PFCIndex = 0;
//				MeasIndex = 0;
//				MeasLog = appTRUE;
//			}
//			else
//			{
//// 				if(PFCStartCounter<=MEAS_LOG_MAX)
//// 				{
//// 					PFCLogValues[PFCIndex] = DCLinkCurrentPulseRising;
//// 					PLLLogValues[PFCIndex] = output_voltage_ff_filter.output; //ZeroCrossAD;
//// 					PFCIndex++;
//// 				}
//			}
//			return;
//		}
//
//		else
//		{
//			if (DipValueReached == appFALSE)
//			{
//
//				if(Vgrid > (float)0.15)
//				{
//					return;
//				}
//
//				else
//				{
//					ControlInitPFC();
//					DipValueReached = appTRUE;
//					ZerocrossStartFlag = appFALSE;
//					return;
//				}
//			}
//			else
//			{
//				PFCStartSequenceReady = appTRUE;
//			}
//		}
//}
//
///********************************************************************************/
///*                					void LogValues(void)							                  */
///*																																							*/
///* LogValues() function records 4000 values of the determined signals into 			*/
///* MeasLogValuesX table. The tables can be used	as debug purposes								*/
///*																																							*/
///********************************************************************************/
//
//void LogValues(void)
//{
//// if (MeasIndex < 4001)
//// {
//			MeasLogValues1[MeasIndex] = OutputVoltage; 				//VgridProper;	//VDC_linkProper;//VgridProper;
//			MeasLogValues2[MeasIndex] = VDC_linkFilt; 			//DCCurrentProper;			//PFCCurrentProper;//PFC_Current;
//			MeasLogValues3[MeasIndex] = PFC_Current;									// OutputVoltage * (float)3.3 * (float)10.447901784617729;	;
//			MeasLogValues4[MeasIndex] = DCLinkCurrentPulseRising;	//VDC_linkProper;			//Reducted_Isec;
//			MeasLogValues5[MeasIndex] = HB_V_PI.output;
//			MeasLogValues6[MeasIndex] = est_state[3];	//untCurrentProper; 	//DCCurrentProper;						//Adaptation_Isec;
//
//			MeasIndex++;
//// }
//			if(MeasIndex == 4000)
//				MeasIndex = 0;
//}
//
//void LogCapestimate(void)
//{
//	if (MeasIndexCap < 100)
//	{
//		MeasLogValues6[MeasIndexCap] = rise_time;
//	}
//		MeasIndexCap++;
//}
//
//
