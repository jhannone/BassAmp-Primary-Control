/*
 * Measurement_calibration_data.h
 *
 *  Created on: Apr 2, 2017
 *      Author: janne
 */

#ifndef MEASUREMENT_CALIBRATION_DATA_H_
#define MEASUREMENT_CALIBRATION_DATA_H_

#include "Measurement_scaling.h"

// Input voltage
float uin[UIN_VECTOR_SIZE] = {-12, -9, -7, -5, -3, -1, 0, 1, 3, 5, 7, 9, 12};
float uin_ad[UIN_VECTOR_SIZE] = {246, 644, 911, 1178, 1443, 1708, 1840, 1975, 2238, 2503, 2767, 3033, 3430};

// Input current
float iin[IIN_VECTOR_SIZE] = {-1, -0.8, -0.7, -0.5, -0.3, -0.1, 0, 0.1, 0.3, 0.5, 0.7, 0.8, 1};
float iin_ad[IIN_VECTOR_SIZE] = {1225, 1345, 1409, 1530, 1650, 1775, 1834, 1897, 2017, 2141, 2265, 2324, 2455};

// DC link voltage
float udc[UDC_VECTOR_SIZE] = {1, 2, 4, 6, 8, 10, 14, 18, 20};
float udc_ad[UDC_VECTOR_SIZE] = {97, 211, 450, 679, 908, 1135, 1595, 2058, 2289};

#endif /* MEASUREMENT_CALIBRATION_DATA_H_ */
