/*
 * Common.h
 *
 * File consists of common constructs used throughout the project
 *
 *  Created on: 25.5.2015
 *      Author: Janne
 */

#ifndef COMMON_H_
#define COMMON_H_

typedef union
{
	long L;
	float F;
} LF_t;

/* Defines -----------------------------------------------------------*/

#define _FTOA_TOO_LARGE			0x01
#define _FTOA_TOO_SMALL			0x02
#define _FTOA_STATUS_OK			0x00


extern int ftoa(char *outbuf, float f, int bufsize);
extern float atof_(char str[]);
extern int atoi_(char a[]);

typedef int bool;
#define true 1
#define false 0

#endif /* COMMON_H_ */
