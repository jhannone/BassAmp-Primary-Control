//###########################################################################
//
// FILE:    SCI_init.c
//
// TITLE:   SCI (UART) initialization for Bass Amp Primary.
//
// Comments:
//			File Created 19.5.2015
//
//###########################################################################
// Janne Hannonen
//###########################################################################



#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "SCI_init.h"
#include <math.h>

void scia_loopback_init(void);
void scia_fifo_init(void);
void InitSCI(void);
void SCI_setbaud(float baud);

int reg_h;
int reg_l;
float BRR;


void InitSCI(void)
{
	scia_loopback_init();
}

void scia_loopback_init()
{
    // Note: Clocks were turned on to the SCIA peripheral in F2806x_SysCtrl.c

//	/* Communication Control Register*/

	SciaRegs.SCICCR.bit.SCICHAR 		= 7;	// Character bits (0-7)
	SciaRegs.SCICCR.bit.ADDRIDLE_MODE 	= 0;	// SCI multiprocessor mode
//	SciaRegs.SCICCR.bit.LOOPBKENA 		= 0;	// Loopback test mode, 1 connects TX -> RX
	SciaRegs.SCICCR.bit.STOPBITS 		= 0;	// 0 = 1 stop bit
	SciaRegs.SCICCR.bit.PARITYENA 		= 0;	// 0 = no parity
	SciaRegs.SCICCR.bit.PARITY 			= 0;	// Parity bits

//	/* SCI Control Register 1 */
//
	SciaRegs.SCICTL1.bit.RXENA			= 1;	// Enable recieve
	SciaRegs.SCICTL1.bit.TXENA			= 1;	// Enable transmit
	SciaRegs.SCICTL1.bit.RXERRINTENA	= 0;	// Enable recieve error interrupt (RX ERROR bit (SCIRXST, bit 7) triggers the interrupt)
	SciaRegs.SCICTL1.bit.SLEEP			= 0;
	SciaRegs.SCICTL1.bit.TXWAKE			= 0;
	SciaRegs.SCICTL1.bit.SWRESET		= 0;	// Trigger software reset

	/* SCI Control Register 2 */

//	SciaRegs.SCICTL2.bit.TXRDY
	SciaRegs.SCICTL2.bit.TXINTENA 		= 1;		// Transmit ready interrupt enable
	SciaRegs.SCICTL2.bit.RXBKINTENA 	= 1;		// Recieve break interrupt enable

	SCI_setbaud(115200);

	scia_fifo_init();

	SciaRegs.SCICCR.bit.LOOPBKENA 		= 0; 	// Enable loop back
	SciaRegs.SCICTL1.bit.SWRESET		= 1;	//Relinquish SCI from Reset




}

// Initalize the SCI FIFO
void scia_fifo_init()
{

//    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFCT.all=0x0;

	/* SCI Transmit FIFO */
	//    SciaRegs.SCIFFTX.all=0xE040;
	SciaRegs.SCIFFTX.bit.TXFIFOXRESET	= 0;	// Reset FIFO operation
	SciaRegs.SCIFFTX.bit.SCIRST 		= 1;	// Enable SCI continue operation
	SciaRegs.SCIFFTX.bit.SCIFFENA 		= 1;	// Enables SCI FIFO-mode
	SciaRegs.SCIFFTX.bit.TXFFIENA 		= 1;
	SciaRegs.SCIFFTX.bit.TXFFIL 		= 0;	// Transmit FIFO will generate interrupt when the FIFO status bits (TXFFST4−0) and FIFO level bits (TXFFIL4−0 ) match
//	SciaRegs.SCIFFTX.bit.TXFFINT 		= 0; 	// TXFIFO interrupt has occurred? read-only bit
	SciaRegs.SCIFFTX.bit.TXFFINTCLR		= 1;	// Clear TXFIFO interrupt
	SciaRegs.SCIFFTX.bit.TXFFST			= 0;	// Transmit FIFO is empty.
//
//
	SciaRegs.SCIFFTX.bit.TXFIFOXRESET	= 1;	// Release TX FIFO operation from reset
//	SciaRegs.SCIFFRX.bit.RXFIFORESET	= 1;	// Release RX FIFO operation from reset

}

void SCI_setbaud(float baud)
{

	float SCIclk;
	int maxbaud;

	SCIclk = 22500000;		// define the correct low speed clock frequency by LSPCLK divider from sysctrlregs

	maxbaud = SCIclk/16;
	BRR = 22500000/(baud * 8) -1;



	if (baud < maxbaud)
	{
		reg_l = (int)BRR & 0xFF;
		reg_h = ((int)BRR & 0xFF00) >> 8;
	}
	else // TODO: This is does nothing else than the code above.
	{
		reg_l = (int)BRR & 0xFF;			// lowest bits
		reg_h = ((int)BRR & 0xFF00) >> 8;	// lowest bits
	}

	SciaRegs.SCIHBAUD = (Uint16)reg_h;
	SciaRegs.SCILBAUD = (Uint16)reg_l;


}
