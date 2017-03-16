/*
 * Common.c
 *
 *  Created on: 21.6.2015
 *      Author: Janne
 */


#include "Common.h"
#include <stdio.h>



  float atof_(char str[]);
  int atoi_(char a[]);
  int ftoa(char *outbuf, float f, int bufsize);

  /* Float to binary */
	int integral;
	int binaryInt;
	float binaryFract;
	float k;
	float fractional;
	float temp1;
	float binaryTotal;


int ftoa(char *outbuf, float f, int bufsize)
{
	long mantissa, int_part, frac_part;
	short exp2;
	LF_t x;					// This is a union, the 32-bit float to be converted can be treated either as a float or a long (integer). Used in the conversion process.
	char *p;
	int status;

	status = _FTOA_STATUS_OK;

	if (f == (float)0.0)
	{
		outbuf[0] = '0';
		outbuf[1] = '.';
		outbuf[2] = '0';
		outbuf[3] = 0;
		return status;
	}

	x.F = f;

	exp2 = (unsigned char)(x.L >> 23) - 127;
	mantissa = (x.L & 0xFFFFFF) | 0x800000;
	frac_part = 0;
	int_part = 0;

	if (exp2 >= 31)
	{
		status = _FTOA_TOO_LARGE;
		return status;
	}
	else if (exp2 < -23)
	{
		status = _FTOA_TOO_SMALL;
		return status;
	}
	else if (exp2 >= 23)
		int_part = mantissa << (exp2 - 23);
	else if (exp2 >= 0)
	{
		int_part = mantissa >> (23 - exp2);
		frac_part = (mantissa << (exp2 + 1)) & 0xFFFFFF;
	}
	else /* if (exp2 < 0) */
		frac_part = (mantissa & 0xFFFFFF) >> -(exp2 + 1);

	p = outbuf;

	if (x.L < 0)
		*p++ = '-';

	if (int_part == 0)
		*p++ = '0';
	else
	{
		sprintf(p, "%d", int_part);
		while (*p)
		p++;
	}

	*p++ = '.';

	if (frac_part == 0)
		*p++ = '0';
	else
	{
		char m, max;

		max = bufsize - (p - outbuf) - 1;
		if (max > 7)
		max = 7;
		/* print BCD */
		for (m = 0; m < max; m++)
		{
			/* frac_part *= 10; */
			frac_part = (frac_part << 3) + (frac_part << 1);

			*p++ = (frac_part >> 24) + '0';
			frac_part &= 0xFFFFFF;
		}
	/* delete ending zeroes */
	for (--p; p[0] == '0' && p[-1] != '.'; --p)	;
	++p;
	}
	*p = 0;

	return status;
}


int atoi_(char a[])
{

	/* atoi function variables */
	  int c;
	  int sign;
	  int offset;
	  int n;

	  if (a[0] == '-') // Handle negative integers
	  {
		sign = -1;
	  }

	  if (sign == -1) // Set starting position to convert
	  {
		offset = 1;
	  }

	  else
	  {
		offset = 0;
	  }

	  n = 0;

	  for (c = offset; a[c] != '\0'; c++)
	  {
		n = n * 10 + a[c] - '0';
	  }

	  if (sign == -1)
	  {
		n = -n;
	  }

	  return n;
}

float atof_(char str[])
{

	int len=0, n=0,i=0;
	float f=1.0,val=0.0;

	//counting length of String
	while(str[len])len++;
	//cheking for valid string
	if(!len)return 0;

	//Extracting Integer  part
	while(i<len && str[i]!='.')
		n=10*n +(str[i++]-'0');

	//checking if only Integer
	if(i==len) return n;
	i++;
	while(i<len)
	{
		f*=0.1;
		val+=f*(str[i++]-'0');
	}
	return(val+n);
}

//Uint32 ftobin(float f)
//{
//	int	i = 1;
//
//	binaryInt = 0;
//	k =0.1f;
//	binaryFract = 0;
//
//	//Separating the integral value from the floating point variable
//	integral = (int)f;
//
//	//Separating the fractional value from the variable
//	fractional = f - (int)f;
//
//	//Loop for converting decimal to binary
//	while(integral>0)
//	{
//	    binaryInt = binaryInt + integral % 2 * i;
//	    i = i * 10;
//	    integral = integral / 2;
//	}
//
//	//Loop for converting Fractional value to binary
//	while(k>0.00000001)
//	{
//	    temp1 = fractional *2;
//	    binaryFract = binaryFract+((int)temp1)*k;
//	    fractional = temp1 - (int)temp1;
//	    k = k / 10;
//	}
//
//	//Combining both the integral and fractional binary value.
//	binaryTotal = binaryInt +binaryFract;
//
//
//
//
//}
