//###########################################################################
//
// FILE:    GPIO_config_primary.c
//
// TITLE:   F28069 GPIO configuration for Bass Amp Primary
//
// Comments:
//			File Created 21.3.2015
//
//###########################################################################
// Janne Hannonen
//###########################################################################

#include "GPIO_config.h"


void InitGPIO(void)
{

	EALLOW;

	// Disable pull-up resistor on

    GpioCtrlRegs.GPAPUD.PFC_G2 = 1;    // (EPWM1A)
	GpioCtrlRegs.GPAPUD.PFC_G1 = 1;    // (EPWM1B)
    GpioCtrlRegs.GPAPUD.PFC_G4 = 1;    // (EPWM2A)
	GpioCtrlRegs.GPAPUD.PFC_G3 = 1;    // (EPWM2B)

    GpioCtrlRegs.GPAPUD.Bridge_G1 = 1;    // (EPWM3A)
	GpioCtrlRegs.GPAPUD.Bridge_G2 = 1;    // (EPWM3B)
    GpioCtrlRegs.GPAPUD.Bridge_G3 = 1;    // (EPWM4A)
	GpioCtrlRegs.GPAPUD.Bridge_G4 = 1;    // (EPWM4B)

    GpioCtrlRegs.GPAPUD.G_aux_power = 1;	// (EPWM5A)
	GpioCtrlRegs.GPAPUD.G_Fan_buck  = 1;	// (EPWM5B)

    GpioCtrlRegs.GPAPUD.Sync_G1 = 1;    //  (EPWM6A)
	GpioCtrlRegs.GPAPUD.Sync_G2 = 1;    //  (EPWM6B)
	GpioCtrlRegs.GPBPUD.Sync_G3 = 1;    //  (EPWM7A)	Note GPIO B
	GpioCtrlRegs.GPBPUD.Sync_G4 = 1;    //  (EPWM7B)	Note GPIO B

	GpioCtrlRegs.GPBPUD.HRPWM_8A =1;	// (EPWM8A)

	GpioCtrlRegs.GPAPUD.SCI_TX = 1;    //  (SCI A)
	GpioCtrlRegs.GPAPUD.SCI_RX = 1;    //  (SCI A)


	// Command pull-up
	GpioCtrlRegs.GPAPUD.LedG = 0;
    GpioCtrlRegs.GPAPUD.LedR = 0;





//	GpioCtrlRegs.GPBPUD.HRPWM_8A = 1;    //  (EPWM8A)	// used for measurement synchronization
//	GpioCtrlRegs.GPBPUD.PWM_8B	 = 1;    //  (EPWM8B) // used for measurement synchronization


	/* Configure EPWM pins using GPIOx as ePWM regs*/

    GpioCtrlRegs.GPAMUX1.PFC_G2 = 1;    // (EPWM1A)
	GpioCtrlRegs.GPAMUX1.PFC_G1 = 1;    // (EPWM1B)
    GpioCtrlRegs.GPAMUX1.PFC_G4 = 1;    // (EPWM2A)
	GpioCtrlRegs.GPAMUX1.PFC_G3 = 1;    // (EPWM2B)

    GpioCtrlRegs.GPAMUX1.Bridge_G1 = 1;    // (EPWM3A)
	GpioCtrlRegs.GPAMUX1.Bridge_G2 = 1;    // (EPWM3B)
    GpioCtrlRegs.GPAMUX1.Bridge_G3 = 1;    // (EPWM4A)
	GpioCtrlRegs.GPAMUX1.Bridge_G4 = 1;    // (EPWM4B)

    GpioCtrlRegs.GPAMUX1.G_aux_power = 1;	// (EPWM5A)
	GpioCtrlRegs.GPAMUX1.G_Fan_buck  = 1;	// (EPWM5B)

    GpioCtrlRegs.GPAMUX1.Sync_G1 = 1;    //  (EPWM6A)
	GpioCtrlRegs.GPAMUX1.Sync_G2 = 1;    //  (EPWM6B)
	GpioCtrlRegs.GPBMUX1.Sync_G3 = 1;    //  (EPWM7A)	Note GPIO B
	GpioCtrlRegs.GPBMUX1.Sync_G4 = 1;    //  (EPWM7B)	Note GPIO B

	GpioCtrlRegs.GPBMUX1.HRPWM_8A = 1;	 //	 (EPWM8A)

	GpioCtrlRegs.GPAMUX2.SCI_RX = 1;   // (SCI A)
	GpioCtrlRegs.GPAMUX2.SCI_TX = 1;   // (SCI A)

	// Configure LED as normal GPIO
    GpioCtrlRegs.GPAMUX2.LedG = 0;
    GpioCtrlRegs.GPAMUX2.LedR = 0;


	// SCI Inputs are synchronized to SYSCLKOUT by default.

	GpioCtrlRegs.GPAQSEL2.SCI_RX = 3;  // Asynch input GPIO28 (SCIRXDA)


	// Command as GPIO outputs
    GpioCtrlRegs.GPADIR.LedG = 1;
    GpioCtrlRegs.GPADIR.LedR = 1;


    // Init state for normal GPIO
    GpioDataRegs.GPASET.LedG = 1;
    GpioDataRegs.GPASET.LedR = 1;

	EDIS;
}

void InitAdcAio()
{

   EALLOW;

/* Configure ADC pins using AIO regs*/
// This specifies which of the possible AIO pins will be Analog input pins.
// NOTE: AIO 1,3,5,7-9,11,13,15 are analog inputs in all AIOMUX1 configurations.
// Comment out other unwanted lines.



	GpioCtrlRegs.AIOMUX1.bit.AIO2 = 2;    // Configure AIO2 for A2 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO4 = 2;    // Configure AIO4 for A4 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO6 = 2;    // Configure AIO6 for A6 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO10 = 2;   // Configure AIO10 for B2 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO12 = 2;   // Configure AIO12 for B4 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO14 = 2;   // Configure AIO14 for B6 (analog input) operation

	EDIS;
}





