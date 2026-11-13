#include "Tsc.h"
#include "Gpio.h"

static void Tsc_WriteByte(uint8_t data);
static uint8_t Tsc_ReadByte(void);

static inline void Tsc_Delay(void) {
	__asm volatile ("nop");
	__asm volatile ("nop");
	__asm volatile ("nop");
	__asm volatile ("nop");
	__asm volatile ("nop");
	
	__asm volatile ("nop");
	__asm volatile ("nop");
	__asm volatile ("nop");
	__asm volatile ("nop");
	__asm volatile ("nop");
}


void Tsc_Initialize(void) {
	//We get Busy, PenIRQ and DOUT
	Gpio_Initialize(GPIO_ID_TOUCH_BUSY, GPIO_MODE_INPUT, false);
	Gpio_Initialize(GPIO_ID_TOUCH_PENIRQ, GPIO_MODE_INPUT, false);
	Gpio_Initialize(GPIO_ID_TOUCH_DOUT, GPIO_MODE_INPUT, false);
	
	//We define DIN, nCS and CLK	
	Gpio_Initialize(GPIO_ID_TOUCH_DIN, GPIO_MODE_OUTPUT, false);
	Gpio_Initialize(GPIO_ID_TOUCH_CS, GPIO_MODE_OUTPUT, false);
	Gpio_Initialize(GPIO_ID_TOUCH_DCLK, GPIO_MODE_OUTPUT, false);
}

static void Tsc_WriteByte(uint8_t data){
//Durchlaufen aller Bits und setzten der Leitung
	for (int8_t bit = 7; bit >= 0; bit--) {
		//Setzen der DCLK-Line
		Gpio_Set(GPIO_ID_TOUCH_DCLK, false);
		
		if (data & (uint8_t)(0x1 << bit)) {
			Gpio_Set(GPIO_ID_TOUCH_DIN, true);
		} else {
			Gpio_Set(GPIO_ID_TOUCH_DIN, false);
		}
		Tsc_Delay();
		
		// Setzten der DCLK-Line
		Gpio_Set(GPIO_ID_TOUCH_DCLK, true);
		Tsc_Delay();
	}
	
	Gpio_Set(GPIO_ID_TOUCH_DCLK, false);
	Gpio_Set(GPIO_ID_TOUCH_DIN, false);
}

static uint8_t Tsc_ReadByte(void){
	uint8_t data = 0x0;
	
	Gpio_Set(GPIO_ID_TOUCH_DCLK, false);
	
	for(uint8_t bit = 0; bit <= 7; bit++) {
		Gpio_Set(GPIO_ID_TOUCH_DCLK, true);
		Tsc_Delay();

		//Test for while busy
		bool bitValue = false;
		Gpio_Get(GPIO_ID_TOUCH_DOUT, &bitValue);

		data = ((data << 1) | (uint8_t)(bitvalue));

		Gpio_Set(GPIO_ID_TOUCH_DCLK, false);

		Tsc_Delay();
	}
	return data;
}
