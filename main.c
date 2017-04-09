/*
 * main.c
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Adc_init.h"
#include "GPIO_config.h"
#include "SCI_init.h"
#include "SCI_interface.h"
#include "Command_shell.h"
#include "Control_top.h"
#include "EPWM_init.h"
#include "PWM_interface.h"
#include "DMA_init.h"
#include "Measurement_scaling.h"
#include "Cpu_timer_init.h"
#include "Timer_interface.h"


__interrupt void adc_isr(void);
__interrupt void cpu_timer0_isr(void);

Uint16 i=0;

//#pragma CODE_SECTION(, "ramfuncs");

int main(void)
{
	
	// If using Flash memory, Copy first some functions from flash to ram
	// memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

	   InitSysCtrl();
	   DINT; 			// Disable CPU interrupts

	   InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
	   IER = 0x0000;
	   IFR = 0x0000;

	   InitPieVectTable();	// Configure default ISR:s. Will halt the processor if something goes wrong

	 // Interrupts are rewrapped to known names.
	      EALLOW;  // This is needed to write to EALLOW protected register
	      	  PieVectTable.ADCINT1 = &adc_isr;
	      	  PieVectTable.TINT0 = &cpu_timer0_isr;
	      EDIS;    // This is needed to disable write to EALLOW protected registers

	  //  Initialize Device Peripherals:
	      InitAdc();  		// Common initialization
	      InitAdcAio();		// Define trip mux
	      ConfigureAdc();	// Configure ADC channels

	      InitSCI();		// Initialize Serial communication
	      InitGPIO();	    // Initialize GPIO pins
	      InitPFCPWM();		// Initialize PFC EPWM
	      InitDMA();		// Initialize DMA
	      InitCpuTimers();  // Initialize CPU timers


	      /* Application initializations */
	      CommandInit();
	      MeasurementInit();
	      InitControl();


		  // Step 5. Enable interrupts:
		  // Enable ADCINT1 in PIE
		  PieCtrlRegs.PIEIER1.bit.INTx1 = 1;		// Enable INT 1.1 in the PIE

		  // Enable TINT0 in the PIE: Group 1 interrupt 7
		  PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

		  IER |= M_INT1; 							// Enable CPU Interrupt 1

		  StartDMACH1();

		  EINT;          						// Enable Global interrupt INTM
		  ERTM;          						// Enable Global realtime interrupt DBGM

		  while(1)
		  {
			  // SCI
			  if (SCIRXBufferWordsAvailable() >= 1)		// Some word(s) is/are waiting at SCI buffer
			  {
					BufferChar(SCIRXBufferGetData());	// Data received
			  }
		  }
}


__interrupt void adc_isr(void)
{
	/* WHEN DMA IS IN USE, _DO NOT_ read anything from the ADC result buffer, the results will get corrupted */

  AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;		//Clear ADCINT1 flag reinitialize for next SOC
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

  return;
}

__interrupt void cpu_timer0_isr(void)
{

    ControlMain();
    if (i == 30000)
    {
        GpioDataRegs.GPATOGGLE.LedG = 1;
        i = 0;
    }
    else
    {
        i++;
    }

    // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


