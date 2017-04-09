/*
 * Control_top.h
 *
 *  Created on: 4.8.2015
 *      Author: Janne
 */

#ifndef CONTROL_TOP_H_
#define CONTROL_TOP_H_

#define HB_V_P_GAIN 	47.8
#define HB_V_I_GAIN 	47.0
#define HB_I_P_GAIN 	47.0
#define HB_I_I_GAIN 	47.0

#define PFC_V_P_GAIN 	0.0002
#define PFC_V_I_GAIN 	1000
#define PFC_I_P_GAIN 	0.75
#define PFC_I_I_GAIN 	150

#define AUX_V_P_GAIN 	47.0
#define AUX_V_I_GAIN 	47.0

#define HB_FSW			60.0		/*kHz */
#define HB_VREF			48.0		/* V */
#define HB_DUTY			0.0
#define HB_DEADTIME		20.0		/*ns*/

#define PFC_FSW			120.0		/* kHz*/
#define PFC_VREF		30.0		/* V */
#define PFC_DUTY		0.0

#define CTRL_FREQ       60000       /*Hz*/

#define AUX_FSW			100.0		/* kHz*/
#define AUX_VREF		20.0		/* V */
#define AUX_DUTY		0.0

#define MAXPFCDUTY		0.98
#define MINPFCDUTY		0.02

extern float HB_V_P_gain;
extern float HB_V_I_gain;
extern float HB_I_P_gain;
extern float HB_I_I_gain;

extern float PFC_V_P_gain;
extern float PFC_V_I_gain;
extern float PFC_I_P_gain;
extern float PFC_I_I_gain;

extern float AUX_V_P_gain;
extern float AUX_V_I_gain;

extern float Vout_ref;
extern float DC_link_ref;
extern float AUX_ref;

extern float HB_duty;
extern float PFC_duty;
extern float AUX_duty;

extern void InitControl(void);
extern void ControlMain(void);



#endif /* CONTROL_TOP_H_ */
