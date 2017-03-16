/*
 * EPWM_init.c
 *
 *  Created on: 30.4.2016
 *      Author: Janne
 */

#include "DSP28x_Project.h"     // Device Headerfile
#include "EPWM_init.h"


void InitPFCPWM(void);


/* In this case, only the lower switches of PFC brdge are initialized, since pridgeless PFC is used.
 * The lower switches, G2 & G4 are connected to EPWM1 and EPWM2 respectively.
 * EPWM8 is used to trigger the ADC in synchronous with the gate commands. */

void InitPFCPWM(void)
{

	   // Setup TBCLK
	   EPwm1Regs.TBPRD 					= PFC_PERIOD;    	// Set timer period
	   EPwm1Regs.TBCTL.bit.CTRMODE 		= TB_COUNT_UP; 		// Count up
	   EPwm1Regs.TBCTL.bit.PHSEN 		= TB_DISABLE;    	// Disable phase loading
	   EPwm1Regs.TBPHS.half.TBPHS 		= 0x0000;       	// Phase is 0
	   EPwm1Regs.TBCTR 					= 0x0000;           // Clear counter
	   EPwm1Regs.TBCTL.bit.HSPCLKDIV 	= TB_DIV1;   		// Clock ratio to SYSCLKOUT
	   EPwm1Regs.TBCTL.bit.CLKDIV 		= TB_DIV1;
	   EPwm1Regs.TBCTL.bit.SYNCOSEL 	= TB_CTR_ZERO;   	// Sync down-stream module, in this case EPwm2


	   // Setup shadow register load on ZERO
	   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	   // Set Compare values
	   EPwm1Regs.CMPA.half.CMPA = 0;    	// Set compare A value
	   EPwm1Regs.CMPB = 0;					// Set Compare B value

	   // Set actions
	   EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
	   EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A, up count

	   // Trip zone control
	   EALLOW;
	   EPwm1Regs.TZSEL.bit.OSHT1 	= 1;
	   EPwm1Regs.TZCTL.bit.TZA 		= 2;					// Force A output low, when trip occurs
	   EPwm1Regs.TZCTL.bit.TZB 		= 2;					// Force B output low, when trip occurs
	   EPwm1Regs.TZFRC.bit.OST 		= 1;					// Force trip on at startup => The start must be done manually
	   EDIS;

	   //EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;            // Set PWM1B on Zero
	   //EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;          // Clear PWM1B on event B, up count




//	   // Interrupt where we will change the Compare Values
//	   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
//	   EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
//	   EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event


	   // Setup TBCLK
	   EPwm2Regs.TBPRD 					= PFC_PERIOD;    	// Set timer period
	   EPwm2Regs.TBCTL.bit.CTRMODE 		= TB_COUNT_UP; 		// Count up
	   EPwm2Regs.TBCTL.bit.PHSEN 		= TB_ENABLE;	    // Slave module
	   EPwm2Regs.TBCTL.bit.SYNCOSEL 	= TB_SYNC_IN;		// Synchronisation pulse flowthrough
	   EPwm2Regs.TBPHS.half.TBPHS 		= 0x0000;       	// Phase is 0
	   EPwm2Regs.TBCTR 					= 0x0000;           // Clear counter
	   EPwm2Regs.TBCTL.bit.HSPCLKDIV 	= TB_DIV1;   		// Clock ratio to SYSCLKOUT
	   EPwm2Regs.TBCTL.bit.CLKDIV 		= TB_DIV1;

	   // Setup shadow register load on ZERO
	   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	   // Set Compare values
	   EPwm2Regs.CMPA.half.CMPA = 0;//PFC_PERIOD/2;    // Set compare A value
	   EPwm2Regs.CMPB = 0;  //= PFC_PERIOD;              // Set Compare B value

	   // Set actions
	   EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
	   EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A, up count

	   // Trip zone control
	   EALLOW;
	   EPwm2Regs.TZSEL.bit.OSHT1 	= 1;
	   EPwm2Regs.TZCTL.bit.TZA = 2;					// Force A output low, when trip occurs
	   EPwm2Regs.TZCTL.bit.TZB = 2;					// Force B output low, when trip occurs
	   EPwm2Regs.TZFRC.bit.OST = 1;					// Force trip on at startup => The start must be done manually
	   EDIS;

	   //EPwm2Regs.AQCTLB.bit.ZRO = AQ_SET;            // Set PWM1B on Zero
	   //EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;          // Clear PWM1B on event B, up count


	   // EPWM8 is used for measurement trig. At this phase of development, the signal is routed to EPWM8 to see when the measurement is triggered

	   EPwm8Regs.TBPRD 					= PFC_PERIOD;    	// Set timer period
	   EPwm8Regs.TBCTL.bit.CTRMODE 		= TB_COUNT_UP; 		// Count up
	   EPwm8Regs.TBCTL.bit.PHSEN 		= TB_ENABLE;	    // Slave module
	   EPwm8Regs.TBCTL.bit.SYNCOSEL 	= TB_SYNC_IN;		// Synchronisation pulse flowthrough
	   EPwm8Regs.TBPHS.half.TBPHS 		= (PFC_PERIOD/2)+8; // This should be duty + 8. Why it needs to be +8 and not -8 to make delay, I don't have a slightest idea. Maybe the phase is calculated "backwards"
	   EPwm8Regs.TBCTR 					= 0x0000;           // Clear counter
	   EPwm8Regs.TBCTL.bit.HSPCLKDIV 	= TB_DIV1;   		// Clock ratio to SYSCLKOUT
	   EPwm8Regs.TBCTL.bit.CLKDIV 		= TB_DIV1;

	   // Setup shadow register load on ZERO
	   EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	   EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	   EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	   EPwm8Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;



	   // Set Compare values
	   EPwm8Regs.CMPA.half.CMPA = 2;    			// Set compare A value (this is duty later on)
	   //EPwm8Regs.CMPB = PFC_PERIOD;              // Set Compare B value

	   /*SOC triggering*/

	   EPwm8Regs.ETSEL.bit.SOCAEN	= 1;		// Enable SOC on A group
	   EPwm8Regs.ETSEL.bit.SOCASEL	= 4;		// Select SOC from CMPA on upcount
	   EPwm8Regs.ETPS.bit.SOCAPRD 	= 1;		// Generate pulse on 1st event

	   // Set actions
	   EPwm8Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
	   EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A, up count

	   //EPwm8Regs.AQCTLB.bit.ZRO = AQ_SET;            // Set PWM1B on Zero
	   //EPwm8Regs.AQCTLB.bit.CBU = AQ_CLEAR;          // Clear PWM1B on event B, up count

//	   // Interrupt where we will change the Compare Values
//	   EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
//	   EPwm2Regs.ETSEL.bit.INTEN = 1;                // Enable INT
//	   EPwm2Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event


}

