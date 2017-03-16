/*
//###########################################################################
//
// FILE:    SCI_interface.h
//
// TITLE:   SCI (UART) interface headers.
//
// Comments:
//			File Created 28.5.2015
//
//###########################################################################
// Janne Hannonen
//###########################################################################
 *
 */


#ifndef SCI_INTERFACE_H_
#define SCI_INTERFACE_H_

#include "Common.h"
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "SCI_init.h"

extern void SendDataSCI(Uint16 a);
extern void SCIXmitCharacter(int a);
extern void SendMsg(char * msg);


extern void SendDataSCI(Uint16 a);


inline Uint16 SCIATXReady(void)
{
	return SciaRegs.SCICTL2.bit.TXRDY;
}

inline Uint16 SCIARXReady(void)
{
	return SciaRegs.SCIRXST.bit.RXRDY;
}

inline Uint16 SCIRXBufferOVF(void)
{
	return SciaRegs.SCIFFRX.bit.RXFFOVF;
}

inline Uint16 SCIRXBufferWordsAvailable(void)
{
	return SciaRegs.SCIFFRX.bit.RXFFST;
}


inline Uint16 SCIRXBufferParityError(void)
{
	return SciaRegs.SCIRXBUF.bit.SCIFFPE;
}

inline Uint16 SCIRXBufferFramingError(void)
{
	return SciaRegs.SCIRXBUF.bit.SCIFFFE;
}

inline Uint16 SCIRXBufferGetData(void)
{
	return SciaRegs.SCIRXBUF.all;
}



#endif /* SCI_INTERFACE_H_ */
