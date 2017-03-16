/*
 * Control_interface_functions.c
 *
 *  Created on: 4.8.2015
 *      Author: Janne
 */

#include "commands.h"
#include "Control_top.h"
#include "Control_interface_functions.h"
#include "PWM_interface.h"


void ControlInit(void);
void setHBParameters(Uint16 ParamterToSet, float data);
void setPFCParameters(Uint16 ParamterToSet, float data);
void setAUXParameters(Uint16 ParamterToSet, float data);

void* getParameter(Uint16 ParameterID);






void ControlInit(void)	// This is stupid, but the point is that the functions in Control_top are not visible outside of the Power stage control block
{
	InitControl();
}

void setHBParameters(Uint16 ParamterToSet, float data)
{
	switch(ParamterToSet)
	{
		case(SET_HBVIGAIN):		HB_V_I_gain = data; break;
		case(SET_HBVPGAIN): 	HB_V_P_gain = data; break;
		case(SET_HBIIGAIN): 	HB_I_I_gain = data; break;
		case(SET_HBIPGAIN): 	HB_I_P_gain = data; break;


		case(SET_HBFSW):		SetHB_Fsw((Uint16) data); break;
		case(SET_HBVREF): 		Vout_ref = data; break;
		case(SET_HBDUTY): 		HB_duty  = data; break;
		case(SET_HBDEADTIME): 	SetHB_DT((Uint16) data); break;
	}
}


void setPFCParameters(Uint16 ParamterToSet, float data)
{

	switch(ParamterToSet)
	{
		case(SET_PFCVIGAIN): 	PFC_V_I_gain = data; break;
		case(SET_PFCVPGAIN): 	PFC_V_P_gain = data; break;
		case(SET_PFCIIGAIN): 	PFC_I_I_gain = data; break;
		case(SET_PFCIPGAIN): 	PFC_I_P_gain = data; break;

		case(SET_PFCVREF): 		DC_link_ref  = data; break;

		case(SET_PFCFSW):		SetPFC_Fsw((Uint16) data); break;
		case(SET_PFCDUTY): 		PFC_duty = data; break;
	}

}


void setAUXParameters(Uint16 ParamterToSet, float data)
{
	switch(ParamterToSet)
	{
		case(SET_AUXVIGAIN):	AUX_V_I_gain = data; break;
		case(SET_AUXVPGAIN):	AUX_V_P_gain = data; break;

		case(SET_AUXVREF): 		AUX_ref  = data; break;
		case(SET_AUXDUTY): 		AUX_duty = data; break;

		case(SET_AUXFSW):		SetAUX_Fsw((Uint16) data); break;

	}
}


void* getParameter(Uint16 ParamterID)
{
	switch(ParamterID)
	{
		case(SET_HBVIGAIN):		return (void*)&HB_V_I_gain;
		case(SET_HBVPGAIN): 	return (void*)&HB_V_P_gain;
		case(SET_HBIIGAIN): 	return (void*)&HB_I_I_gain;
		case(SET_HBIPGAIN): 	return (void*)&HB_I_P_gain;

		case(SET_HBVREF): 		return (void*)&Vout_ref;
		case(SET_HBDUTY): 		return (void*)&HB_duty;

		case(SET_PFCVIGAIN): 	return (void*)&PFC_V_I_gain;
		case(SET_PFCVPGAIN): 	return (void*)&PFC_V_P_gain;
		case(SET_PFCIIGAIN): 	return (void*)&PFC_I_I_gain;
		case(SET_PFCIPGAIN): 	return (void*)&PFC_I_P_gain;

		case(SET_PFCVREF): 		return (void*)&DC_link_ref;
		case(SET_PFCDUTY): 		return (void*)&PFC_duty;

		case(SET_AUXVIGAIN):	return (void*)&AUX_V_I_gain;
		case(SET_AUXVPGAIN):	return (void*)&AUX_V_P_gain;

		case(SET_AUXVREF): 		return (void*)&AUX_ref;
		case(SET_AUXDUTY): 		return (void*)&AUX_duty;

		default: return 0;
	}
}








