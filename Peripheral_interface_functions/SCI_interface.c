/*
//###########################################################################
//
// FILE:    SCI_interface.c
//
// TITLE:   SCI (UART) interface functions.
//
// Comments:
//			File Created 28.5.2015
//
//###########################################################################
// Janne Hannonen
//###########################################################################
 *
 */


#include "Common.h"
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "SCI_init.h"
#include "SCI_interface.h"

Uint8	Dataset;

void SendDataSCI(Uint16 a)
{
	Dataset = (Uint8)((0xFF00 & a)>>8);
	while(!SciaRegs.SCICTL2.bit.TXRDY);
	SciaRegs.SCITXBUF=Dataset;
	Dataset = (Uint8)0x00FF & a;
	while(!SciaRegs.SCICTL2.bit.TXRDY);
	SciaRegs.SCITXBUF=Dataset;

}

void SCIXmitCharacter(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    SciaRegs.SCITXBUF=a;
}

void SendMsg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
    	SCIXmitCharacter(msg[i]);
        i++;
    }
}
