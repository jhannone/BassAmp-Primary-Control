/*
 * Command_shell.h
 *
 *  Created on: 7.6.2015
 *      Author: Janne
 */

#ifndef COMMAND_SHELL_H_
#define COMMAND_SHELL_H_

#define CR                    '\r'
#define LF                    '\n'
#define CRLF                  "\r\n"
#define NULL				  '\0'

#define MAX_CMD_LENGTH		15
#define MAX_ARGUMENTS		5

#define CMD_HELP 			"help"
#define CMD_SET_PFC_DUTY 	"set_dutyPFC"
#define CMD_RUN_PFC			"pfc"

#define PAR_ON				"on"
#define PAR_OFF				"off"

/* Default messages */
#define MSG_ERROR_COMMAND_NOT_FOUND "Command not found\r\n"
#define MSG_ERROR_DEBUG_NOT_ALLOWED "Debug functionality is not allowed\r\n"
#define MSG_ERROR_TOO_LONG_ARGUMENT "Command or argument is overlength\r\n"
#define MSG_ERROR_INVALID_ARGUMENT  "Invalid argument\r\n"
#define MSG_ERROR_NUMBER_ARGUMENT 	"Incorrect number of arguments\r\n"

#define MSG_PFC_ON					"PFC on\r\n"
#define MSG_PFC_OFF					"PFC off\r\n"

#define MSG_OK 						"OK\r\n"



extern void CommandInit(void);
extern void BufferChar(Uint16 ch);

extern void DataToXmit16(Uint8 address, Uint16 data);
extern void DataToXmit32(Uint8 address, Uint32 data);
extern void DataToXmitFloat(Uint8 address, void *data);

#endif /* COMMAND_SHELL_H_ */
