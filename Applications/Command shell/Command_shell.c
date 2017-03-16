/*
 * Command_shell.c
 *
 *  Created on: 7.6.2015
 *      Author: Janne
 */

#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "Command_shell.h"
#include "SCI_interface.h"
#include "PWM_interface.h"
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void CommandInit(void);
void CMDParse(void);
void BufferChar(Uint16 ch);
void DecodeCommand(Uint16 nArgs);
void FlushBuffers(void);

//void DataToXmit16(Uint8 address, Uint16 data);
//void DataToXmit32(Uint8 address, Uint32 data);
//void DataToXmitFloat(Uint8 address, void *data)

/* Command execution functions */
void send_info(void);
void set_pfc_duty(float duty);
void StartStopPFC(Uint16 nArgs);
void log_ctrl(void);

char arguments[MAX_ARGUMENTS][MAX_CMD_LENGTH+2]; // NOTE: DO NOT USE "argv" as a variable name. Everything will explode. Maybe it is reserved for some other use.
char *msg_ptr;

char incoming_cmd[MAX_CMD_LENGTH+2];
char arg[MAX_CMD_LENGTH+2];

bool debug_on = false;

char cmd_buffer[MAX_CMD_LENGTH+2];		// Input characters go here
Uint16 cmd_i;							// Input character index

/* Data transmit package variables */

Uint16 start;
Uint16 data_arr[2];	// Max 32 bit data packages to be sent
Uint8 send_pckg_index;


// Delete everything in buffers
void FlushBuffers()
{
	Uint16 i,j;
	for (i = 0; i < MAX_ARGUMENTS; i++)
	{
		for(j = 0; j<MAX_CMD_LENGTH+2; j++)
		{
			arguments[i][j] = '\0';
			incoming_cmd[j] = '\0';
			cmd_buffer[j] = '\0';
			arg[j] = '\0';
		}
	}
}


void CommandInit(void)
{
	FlushBuffers();
	msg_ptr = &cmd_buffer[0];
	debug_on = true;		// TODO: Move this hell out of here
}


/* BufferChar inserts character into command buffer (cmd_buffer). When null string or CR is found, the command is parsed.
 * Command parsing is done in ParseCommand() function. */

void BufferChar(Uint16 ch)
{
	switch((char)ch)
	{
	case CR:						// Add NULL char.
		cmd_buffer[cmd_i] = '\0';
		CMDParse();
		cmd_i = 0;
		break;

	case LF:						//if LF received, read it from buffer
		break;

	case NULL:						// Parse command.
		CMDParse();
		cmd_i = 0;
		break;

	default:
		cmd_buffer[cmd_i++] = (char)ch;	// Else add character on the buffer
		break;
	}
	return;
}


void CMDParse(void)
{
	Uint16 i = 0;
	Uint16 j = 0;

	for (msg_ptr = &cmd_buffer[0]; *msg_ptr != '\0'; msg_ptr++)
	{
		if (*msg_ptr == ' ')	// Separates the arguments from the command buffer according to space (' ')
		{
			i++;
			j = 0;
		}
		else
		{
			if (j >= MAX_CMD_LENGTH) // Parses the command and the arguments
			{
				SendMsg(MSG_ERROR_TOO_LONG_ARGUMENT);
				break;
			}
			if (i == 0)
			{
				incoming_cmd[j] = *msg_ptr;
			}
			else
			{
				arguments[i-1][j] = *msg_ptr;
			}
			j++;
		}
	}
	DecodeCommand(i);	// Give number of arguments (one parameter less than i, as the first is command)
}

void DecodeCommand(Uint16 nArgs)
{
	Uint16 i;
	float arg1;
	if (!strcmp(incoming_cmd,CMD_HELP))
		send_info();

	else if ((!strcmp(incoming_cmd,CMD_SET_PFC_DUTY) && (nArgs == 1)))  // TODO: make invalid parameter error
	{
		if (debug_on)
		{
			for (i = 0 ;i < MAX_CMD_LENGTH; i++)
			{
				arg[i] = arguments[0][i];
			}
			arg1 = atof_(arg);
			set_pfc_duty(arg1);
		}
		else
		{
			SendMsg(MSG_ERROR_DEBUG_NOT_ALLOWED);
		}
	}

	else if (!strcmp(incoming_cmd,CMD_RUN_PFC))
	{
		StartStopPFC(nArgs);
	}

	else
	{
		SendMsg(MSG_ERROR_COMMAND_NOT_FOUND);
	}
	FlushBuffers();
}

void send_info(void)
{
	SendMsg("Taalla ei ole mitaan nahtavaa!");
	SendMsg("\r\n");
}

void set_pfc_duty(float duty)
{
	if (duty > 1)
		SendMsg("Duty must be between 0-1\r\n");
	else if (duty < 0)
		SendMsg("Duty must be between 0-1\r\n");
	else
	{
		setPFCDuty(duty);
		SendMsg(MSG_OK);
	}
}

void StartStopPFC(Uint16 nArgs)
{
	Uint16 i;

	if (nArgs == 0)
		if (PFCState == true)
			SendMsg(MSG_PFC_ON);
		else
			SendMsg(MSG_PFC_OFF);

	else if (nArgs == 1)
	{
		for (i = 0 ;i < MAX_CMD_LENGTH; i++)
		{
			arg[i] = arguments[0][i];
		}

		if (!strcmp(arg,PAR_ON))
		{
			PFCRun(true);
			SendMsg(MSG_OK);
			SendMsg(MSG_PFC_ON);
		}

		else if (!strcmp(arg,PAR_OFF))
		{
			PFCRun(false);
			SendMsg(MSG_OK);
			SendMsg(MSG_PFC_OFF);
		}

		else
			SendMsg(MSG_ERROR_INVALID_ARGUMENT);
	}

	else
		SendMsg(MSG_ERROR_NUMBER_ARGUMENT);



}


//void DataToXmit16(Uint8 address, Uint16 data)
//{
//	start =0xA0FF & address;		// The lowest 8 bits are masked with address
//	SendDataSCI(data);
//	SendDataSCI(start);
//}
//
//void DataToXmit32(Uint8 address, Uint32 data)
//{
//	start =((Uint16)0xA2 << 8) | address;			// The lowest 8 bits are masked with address
//	data_arr[0] = 0x0000FFFF & data;	// Lowest 8 bits of long
//	data_arr[1] = 0xFFFF0000 & data;		// Highest 8 bits of long
//
//	SendDataSCI(data_arr[0]);
//	SendDataSCI(data_arr[1]);
//	SendDataSCI(start);
//}
//
//void DataToXmitFloat(Uint8 address, void *data)	// void *data gets the pointer to the memory slot of the number to be sent. This is converted into 32 bit (IEEE format) binary later on
//{
//	start =((Uint16)0xBC << 8) | address;			// The lowest 8 bits are masked with address
//	data_arr[0] = (Uint16)(0x0000FFFF & *(Uint32*)data);	// Lowest 8 bits of float
//	data_arr[1] = (Uint16)((0xFFFF0000 & *(Uint32*)data) >> 16);	// Highest 8 bits of float
//	SendDataSCI(data_arr[1]);
//	SendDataSCI(data_arr[0]);
//	SendDataSCI(start);
//	//SendDataSCI((char)('\n'));
//}







