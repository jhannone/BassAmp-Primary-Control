/*
 * DMA_interface.h
 *
 *  Created on: Apr 9, 2017
 *      Author: janne
 */

#ifndef PERIPHERAL_INTERFACE_FUNCTIONS_DMA_INTERFACE_H_
#define PERIPHERAL_INTERFACE_FUNCTIONS_DMA_INTERFACE_H_

#define DMA_1_BUF_SIZE 40

extern volatile Uint16 DMABuf1[DMA_1_BUF_SIZE];

extern volatile Uint16 *DMADest;
extern volatile Uint16 *DMASource;

#endif /* PERIPHERAL_INTERFACE_FUNCTIONS_DMA_INTERFACE_H_ */
