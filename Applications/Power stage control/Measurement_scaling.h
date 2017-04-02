/*
 * Measurement_scaling.h
 *
 *  Created on: Apr 2, 2017
 *      Author: Janne Hannonen
 */

#ifndef APPLICATIONS_POWER_STAGE_CONTROL_MEASUREMENT_SCALING_H_
#define APPLICATIONS_POWER_STAGE_CONTROL_MEASUREMENT_SCALING_H_

#include "F2806x_Device.h"
#include "F2806x_Examples.h"

#define AD_BITS 4096

#define UIN_VECTOR_SIZE 13
#define IIN_VECTOR_SIZE 13
#define UDC_VECTOR_SIZE 9

extern void MeasurementInit(void);


extern float a_uin;    // For AD -> Voltage
extern float b_uin;    // For AD -> Voltage
extern float uin_norm;    // For Voltage -> Normalized
extern float uin_range;

// Input current
extern float a_iin;      // For AD -> Current
extern float b_iin;      // For AD -> Current
extern float iin_norm;      // For Current -> Normalized
extern float iin_range;

// DC link voltage
extern float a_udc;      // For AD -> Voltage
extern float b_udc;      // For AD -> Voltage
extern float udc_norm;     // For Voltage -> Normalized
extern float udc_range;


#endif /* APPLICATIONS_POWER_STAGE_CONTROL_MEASUREMENT_SCALING_H_ */
