/*
 * GPIO_config.h
 *
 *  Created on: 21.3.2015
 *      Author: jhannone
 */

#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_

#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File

// GPIO A

#define PFC_G2		bit.GPIO0
#define PFC_G1		bit.GPIO1
#define PFC_G4		bit.GPIO2
#define PFC_G3		bit.GPIO3

#define Bridge_G1	bit.GPIO4
#define Bridge_G2	bit.GPIO5
#define Bridge_G3	bit.GPIO6
#define Bridge_G4	bit.GPIO7

#define G_aux_power bit.GPIO8

#define G_Fan_buck  bit.GPIO9

#define Sync_G1		bit.GPIO10
#define Sync_G2		bit.GPIO11

#define SPIB_MOSI	bit.GPIO12
#define SPIB_MISO	bit.GPIO13
#define SPIB_CLK	bit.GPIO14
#define SPIB_NSS	bit.GPIO15

#define SPIA_MOSI	bit.GPIO16
#define SPIA_MISO	bit.GPIO17

#define Sync_clk_out	bit.GPIO18
#define Xclk_in			bit.GPIO19

#define Comp1Out		bit.GPIO20
#define Comp2Out		bit.GPIO21

#define LedR			bit.GPIO22
#define LedG			bit.GPIO23

#define Qenc2_InA		bit.GPIO24
#define Qenc2_InB		bit.GPIO25
#define Qenc2_Index		bit.GPIO26
#define QencA_Strobe	bit.GPIO27

#define SCI_RX			bit.GPIO28
#define SCI_TX			bit.GPIO29

#define CanA_RX			bit.GPIO30
#define CanA_TX			bit.GPIO31



//GPIO B

#define AD_conv_start_A	bit.GPIO32
#define AD_conv_start_B	bit.GPIO33

#define Comp3Out	bit.GPIO34
#define SyncBit		bit.GPIO39

#define Sync_G3		bit.GPIO40
#define Sync_G4		bit.GPIO41

#define HRPWM_8A	bit.GPIO42
#define PWM_8B		bit.GPIO43

#define Gpio44		bit.GPIO44

#define Trip_in_1	bit.GPIO50
#define Trip_in_2	bit.GPIO51
#define Trip_in_3	bit.GPIO52

#define Gpio53		bit.GPIO53

#define In_capt_1	bit.GPIO54
#define In_capt_2	bit.GPIO55

#define SPIA_CLK	bit.GPIO56
#define SPIA_NSS	bit.GPIO57

#define EN_relay	bit.GPIO58

extern void Gpio_select(void);


#endif /* GPIO_CONFIG_H_ */


