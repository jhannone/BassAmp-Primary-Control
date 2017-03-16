/*
 * Control_interface_functions.h
 *
 *  Created on: 4.8.2015
 *      Author: Janne
 */

#ifndef CONTROL_INTERFACE_FUNCTIONS_H_
#define CONTROL_INTERFACE_FUNCTIONS_H_

#include "Common.h"
#include "F2806x_Device.h"
#include "F2806x_Examples.h"

/* Function prototypes */

extern void ControlInit(void);
extern void setHBParameters(Uint16 ParamterToSet, float data);
extern void setPFCParameters(Uint16 ParamterToSet, float data);
extern void setAUXParameters(Uint16 ParamterToSet, float data);

extern void* getParameter(Uint16 ParamterID);



#endif /* CONTROL_INTERFACE_FUNCTIONS_H_ */
