/*
 * Timer_interface.c
 *
 *  Created on: Apr 9, 2017
 *      Author: janne
 */



//---------------------------------------------------------------------------
// ConfigCpuTimer:
//---------------------------------------------------------------------------
// This function initializes the selected timer to the period specified
// by the "Freq" and "Period" parameters. The "Freq" is entered as "MHz"
// and the period in "uSeconds". The timer is held in the stopped state
// after configuration.
#include "F2806x_Device.h"     // Headerfile Include File
#include "F2806x_Examples.h"   // Examples Include File
#include "Timer_interface.h"
#include "Cpu_timer_init.h"

void InitControlTimer(float ControlFreq);

void InitControlTimer(float ControlFreq)
{
    // Calculate the microseconds from the input frequency
    float Period = (1/ControlFreq)*1000000;

    // Configure CPU-Timer 0 to interrupt _Period_ time:
    // 90MHz CPU Freq, Period (in uSeconds)
    ConfigCpuTimer(&CpuTimer0, 90, Period);
    CpuTimer0Regs.TCR.all = 0x4001;
}


void ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period)
{
    Uint32  PeriodInClocks;

    // Initialize timer period:
    Timer->CPUFreqInMHz = Freq;
    Timer->PeriodInUSec = Period;
    PeriodInClocks = (long) (Freq * Period);
    Timer->RegsAddr->PRD.all = PeriodInClocks - 1; // Counter decrements PRD+1 times each period

    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    Timer->RegsAddr->TPR.all  = 0;
    Timer->RegsAddr->TPRH.all  = 0;

    // Initialize timer control register:
    Timer->RegsAddr->TCR.bit.TSS = 1;      // 1 = Stop timer, 0 = Start/Restart Timer
    Timer->RegsAddr->TCR.bit.TRB = 1;      // 1 = reload timer
    Timer->RegsAddr->TCR.bit.SOFT = 0;
    Timer->RegsAddr->TCR.bit.FREE = 0;     // Timer Free Run Disabled
    Timer->RegsAddr->TCR.bit.TIE = 1;      // 0 = Disable/ 1 = Enable Timer Interrupt

    // Reset interrupt counter:
    Timer->InterruptCount = 0;

}
