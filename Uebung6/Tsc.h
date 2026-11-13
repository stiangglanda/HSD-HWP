#ifndef TSC_H
#define TSC_H

#include "stdint.h"
#include "stdbool.h"

void Tsc_Initialize(void) {

}

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

#endif