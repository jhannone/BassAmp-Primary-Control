//###########################################################################
//
// FILE:    Adc_config_primary.c
//
// TITLE:   ADC Initialization for Bass Amp Primary.
//
// Comments:
//			File Created 21.3.2015
//
//###########################################################################
// Janne Hannonen
//###########################################################################

#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "Adc_init.h"

// This function initializes ADC to a known state.
//
// NOTE: ADC INIT IS DIFFERENT ON F2806x DEVICES COMPARED TO OTHER 28X DEVICES
//
//  *IMPORTANT*
//  IF RUNNING FROM FLASH, PLEASE COPY OVER THE SECTION "ramfuncs"  FROM FLASH
//  TO RAM PRIOR TO CALLING InitSysCtrl(). THIS PREVENTS THE MCU FROM THROWING
//  AN EXCEPTION WHEN A CALL TO DELAY_US() IS MADE.
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);

    // *IMPORTANT*
    // The Device_cal function, which copies the ADC calibration values from TI reserved
    // OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
    // Boot ROM. If the boot ROM code is bypassed during the debug process, the
    // following function MUST be called for the ADC to function according
    // to specification. The clocks to the ADC MUST be enabled before calling this
    // function.
    // See the device data manual and/or the ADC Reference
    // Manual for more information.

        EALLOW;
        SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
        (*Device_cal)();
        EDIS;

    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
    // after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
    // CPU_RATE define statement in the F2806x_Examples.h file must
    // contain the correct CPU clock period in nanoseconds.
    EALLOW;
    AdcRegs.ADCCTL1.bit.ADCBGPWD  = 1;      // Power ADC BG
    AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;      // Power reference
    AdcRegs.ADCCTL1.bit.ADCPWDN   = 1;      // Power ADC
    AdcRegs.ADCCTL1.bit.ADCENABLE = 1;      // Enable ADC
    AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;      // Select interal BG
    EDIS;

    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

    EALLOW;
    AdcRegs.ADCCTL2.bit.CLKDIV2EN = 0;		// No prescaling is used
    EDIS;

    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels
}


void ConfigureAdc(void)
{
    // Configure ADC
    EALLOW;

//    	AdcRegs.ADCCTL2.bit.ADCNONOVERLAP 	= 1;	// Enable non-overlap mode
    	AdcRegs.ADCCTL2.bit.ADCNONOVERLAP 	= 0;	// Enable overlap mode
//    	AdcRegs.ADCCTL1.bit.INTPULSEPOS		= 1;	// ADCINT1 trips after AdcResults latch

    	AdcRegs.INTSEL1N2.bit.INT1E     	= 1;	// Enabled ADCINT1
//    	AdcRegs.INTSEL1N2.bit.INT2E     	= 1;	// Enabled ADCINT2

    	AdcRegs.INTSEL1N2.bit.INT1CONT  	= 0;	// Disable ADCINT1 Continuous mode
    	AdcRegs.INTSEL1N2.bit.INT2CONT  	= 0;	// Disable ADCINT2 Continuous mode

    	/* Choose Channels for Start of Conversion triggers, See reference manual page 513 */

    	AdcRegs.ADCSOC0CTL.bit.CHSEL 		= 9;    // set SOC0 to convert ADC channel B1 (I Ac input)
    	AdcRegs.ADCSOC1CTL.bit.CHSEL 		= 8;    // set SOC1 to convert ADC channel B0 (U AC input)
    	AdcRegs.ADCSOC2CTL.bit.CHSEL 		= 2;    // set SOC3 to convert ADC channel B2 (U DClink)

    	/* Define priorities */
 //   	AdcRegs.SOCPRICTL.bit.SOCPRIORITY   = 1;    // SOC 0 is high priority, rest are round robin.

    	/* Select which SOC triggers ADC interrupt */
    	/* Here we control ADC interrupt channel 1 and 2 (of which 2 is not used atm). These define the ADC instance to be monitored in ADC interrupt. */
    	AdcRegs.INTSEL1N2.bit.INT1SEL 		= 2;    // setup EOC2 to trigger ADCINT1 (Measure Iin, Uin and UDclink with one trigger)

    	/* Select the trigger source for Start of conversion process, see reference manual page 512 */

    	AdcRegs.ADCSOC0CTL.bit.TRIGSEL 		= 19;    // set SOC0 start trigger on EPWM8, due to round-robin SOC0 converts first then SOC1 and the SOC 2
    	AdcRegs.ADCSOC1CTL.bit.TRIGSEL 		= 19;    // set SOC0 start trigger on EPWM8, due to round-robin SOC0 converts first then SOC1 and the SOC 2
    	AdcRegs.ADCSOC2CTL.bit.TRIGSEL 		= 19;    // set SOC0 start trigger on EPWM8, due to round-robin SOC0 converts first then SOC1 and the SOC 2



    	/* Select conversion time window for each ad conversion channel. The default is 7 ADC Clock Cycles, (6 ACQPS plus 1) */

	    AdcRegs.ADCSOC0CTL.bit.ACQPS 		= 6;
    	AdcRegs.ADCSOC1CTL.bit.ACQPS 		= 6;
    	AdcRegs.ADCSOC2CTL.bit.ACQPS 		= 6;


  	EDIS;
}
