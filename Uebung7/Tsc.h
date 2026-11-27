#ifndef TSC_H
#define TSC_H

#include "stdint.h"
#include "stdbool.h"

typedef struct {
    float x_offset;
    float y_offset;
    float x_scale;
    float y_scale;
} Tsc_Calibration_t;

void Tsc_Initialize(void);

/****************************************************************************** 
Retrieves raw data from the TSC. 
touched: 
A boolean value indicating whether a touch is currently detected or not. 
x: The X coordinate. 
y: The Y coordinate. 
returns: Zero on success, an error code otherwise. 
If no touch is detected, x and y are set to 0xFFFF. 
If the touch is released while the samples are taken, touched is set to false 
and the function returns immediately. 
******************************************************************************/ 
static int Tsc_ReadRaw(bool * touched, uint16_t * x, uint16_t * y);

/****************************************************************************** 
Retrieves the specified number of samples from the TSC and returns the average 
value for each coordinate. 
touched: A boolean value indicating whether a touch is currently detected or not. 
x: The X coordinate. 
y: The Y coordinate. 
returns: Zero on success, an error code otherwise. 
If no touch is detected, x and y are set to 0xFFFF. 
If the touch is released while the samples are taken, touched is set to false 
and the function returns immediately. 
******************************************************************************/ 
int Tsc_Read(bool *touched, uint16_t * x, uint16_t * y, uint8_t samples);

void Tsc_SetCalibration(Tsc_Calibration_t const * cal);
void Tsc_ConvertToLcd(uint16_t xTsc, uint16_t yTsc, uint16_t * xLcd, uint16_t * yLcd);

#endif