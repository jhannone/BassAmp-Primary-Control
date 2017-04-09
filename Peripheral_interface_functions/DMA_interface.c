/*
 * DMA_interface.c
 *
 *  Created on: Apr 9, 2017
 *      Author: janne
 */


#include "DSP28x_Project.h"     // Device Headerfile
#include "DMA_init.h"
#include "Adc_init.h"

#include "F2806x_Device.h"     // Headerfile Include File
#include "F2806x_Examples.h"   // Examples Include File
#include "DMA_interface.h"


#pragma DATA_SECTION(DMABuf1,"DMARAM");
volatile Uint16 DMABuf1[DMA_1_BUF_SIZE]; //DMABuf[0] = input current, DMABuf[2] = input voltage, DMABuf[4] = DC link voltage

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;
