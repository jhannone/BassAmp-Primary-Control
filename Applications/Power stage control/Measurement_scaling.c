/*
 * Control_top.c
 *
 *  Created on: 2.4.2017
 *      Author: Janne Hannonen
 *
 *  Brief: This file contains the scaling functions for AD converted results.
 */

#include "Measurement_scaling.h"
#include "Measurement_calibration_data.h"

Uint16 FitDataLSQ(float *x, float *y, float *a, float *b, Uint16 n);

// Input voltage
float a_uin  = 0;    // For AD -> Voltage
float b_uin  = 0;    // For AD -> Voltage
float uin_norm = 0;    // For Voltage -> Normalized
float uin_range = 0;

// Input current
float a_iin  = 0;      // For AD -> Current
float b_iin  = 0;      // For AD -> Current
float iin_norm = 0;      // For Current -> Normalized
float iin_range = 0;

// DC link voltage
float a_udc  = 0;      // For AD -> Voltage
float b_udc  = 0;      // For AD -> Voltage
float udc_norm = 0;     // For Voltage -> Normalized
float udc_range = 0;

/* Determine the y = bx + a coefficients for each set of calibration data in Measurement_calibration_data.h.
 * When these values are used to calculate the voltages and currents corresponding to the
 * calculate first the voltage or current value corresponding to the AD value. Then scale the result between 0-1 for
 * control using xxx_norm value.*/

void MeasurementInit(void)
{

    float compare;

    a_uin = 0;    // For AD -> Voltage
    b_uin = 0;    // For AD -> Voltage

    // Input current
    a_iin = 0;    // For AD -> Current
    b_iin = 0;    // For AD -> Current

    // DC link voltage
    a_udc = 0;    // For AD -> Voltage
    b_udc = 0;    // For AD -> Voltage

    FitDataLSQ(&uin_ad[0],&uin[0],&a_uin,&b_uin,UIN_VECTOR_SIZE);
    FitDataLSQ(&iin_ad[0],&iin[0],&a_iin,&b_iin,IIN_VECTOR_SIZE);
    FitDataLSQ(&udc_ad[0],&udc[0],&a_udc,&b_udc,UDC_VECTOR_SIZE);

    // Determine the measurement range.
    // As the input voltage and input current are two-sided, the virtual ground should be somewhere around 1700-2300 AD value.
    // seek the minimum of the absolute values. It is known that 0 AD value definitely represents negative input value.

    compare = b_uin*AD_BITS+a_uin;
    uin_range = (a_uin*-1) < compare ? (a_uin*-1) : compare;
    compare = b_iin*AD_BITS+a_iin;
    iin_range = (a_iin*-1) < compare ? (a_iin*-1) : compare;

    // For DC link voltage the range definition is a bit more straight forward, as the maximum range is directly the maximum of (y = bx+a)
    udc_range = b_udc*AD_BITS+a_udc;

    // The normalized values can be calculated with inverse range coefficients:
    uin_norm = 1/uin_range; // For voltage -> scaled
    iin_norm = 1/iin_range; // For current -> scaled
    udc_norm = 1/udc_range; // For voltage -> scaled

}


/*  FitDataLSQ function calculates the best linear fit for function y= bx + a
    for given data vectors x and y. n equals the vector size
    Parts of the code taken from the example shown in
    http://www.codewithc.com/c-program-for-linear-exponential-curve-fitting/
 */

Uint16 FitDataLSQ(float *x, float *y, float *a, float *b, Uint16 n)
{

    float sumx = 0;
    float sumy = 0;
    float sumx2 = 0;
    float sumxy = 0;
    Uint16 i;

    // Calculate needed variables
    for(i=0;i<=n-1;i++)
    {
        sumx  = sumx  + x[i];
        sumx2 = sumx2 + x[i] * x[i];
        sumy  = sumy  + y[i];
        sumxy = sumxy + x[i] * y[i];
    }

    *a = ((sumx2 * sumy - sumx * sumxy) / (n * sumx2 - sumx * sumx));
    *b = ((n * sumxy - sumx * sumy) / (n * sumx2 - sumx * sumx));

    return 0;
}
