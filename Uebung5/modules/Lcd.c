#include "Lcd.h"
#include "Gpio.h"
#include <stm32f072xb.h>

RGB565_t const RGB565_BLACK = { .R = 0x00, .G = 0x00, .B = 0x00 };
RGB565_t const RGB565_GREY  = { .R = 0x0F, .G = 0x1F, .B = 0x0F };
RGB565_t const RGB565_WHITE = { .R = 0x1F, .G = 0x3F, .B = 0x1F };
RGB565_t const RGB565_RED   = { .R = 0x1F, .G = 0x00, .B = 0x00 };
RGB565_t const RGB565_GREEN = { .R = 0x00, .G = 0x3F, .B = 0x00 };
RGB565_t const RGB565_BLUE  = { .R = 0x00, .G = 0x00, .B = 0x1F };

// ToDo: Set Defines for commands
#define CASET 
#define RASET 

static uint32_t GPIO_LCD_ON  = 0x04FF0000; // 4 = write, FF = data
static uint32_t GPIO_LCD_OFF = 0x00000400; // 4 = write

static inline void Lcd_Write(uint8_t data, bool command) {
	// We start a transmission by setting WRX to low
	Gpio_Set(GPIO_ID_TFT_WR, false);
	
	// Decide, whether command or data byte and control DCX
	if (command) {
		// Control DCX as command
		Gpio_Set(GPIO_ID_TFT_DC, false);
	} else {
		// Control DCX as data
		Gpio_Set(GPIO_ID_TFT_DC, true);
	}
	// We write data to our pins via BSRR
	GPIOE->BSRR = (int32_t)(data | GPIO_LCD_ON);
	GPIOE->BSRR = (int32_t)(GPIO_LCD_OFF);
	
	// We end a transmission by setting WRX to high
	Gpio_Set(GPIO_ID_TFT_WR, true);
}

int Lcd_FillBlack() {
	// set CASET as 0x2A
	Lcd_Write(0x2A, true);
	Lcd_Write(0x00, false);
	Lcd_Write(0x00, false);

	Lcd_Write(0x00, false);
	Lcd_Write(0xEF, false);

	// set RASET as 0x2B
	Lcd_Write(0x2B, true);
	Lcd_Write(0x00, false);
	Lcd_Write(0x00, false);

	Lcd_Write(0x01, false);
	Lcd_Write(0x3F, false);

	// write to Mem as 0x2C
	Lcd_Write(0x2C, true);

	for (uint32_t position_y = 0; position_y < LCD_HEIGHT; position_y++) {
		for (uint32_t position_x = 0; position_x < LCD_WIDTH; position_x++) {
			Lcd_Write(0x00, false);
			Lcd_Write(0x00, false);
		}
	}


}

void Lcd_Initialize(void) {
	// ToDo: use GPIO_Initialize with relevant pins for CS, Data / Command, WR, RD, RES, DB0 - DB7
	// TODO check return of initialization
	Gpio_Initialize(GPIO_ID_TFT_CS, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_WR, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_RD, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_RES, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_DC, GPIO_MODE_OUTPUT, true);

	Gpio_Initialize(GPIO_ID_TFT_DB0, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_DB1, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_DB2, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_DB3, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_DB4, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_DB5, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_DB6, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_TFT_DB7, GPIO_MODE_OUTPUT, true);

	// Initialization Code from exercise
	Lcd_Write(0x11, true); //exit SLEEP mode
	Lcd_Write(0x36, true);
	Lcd_Write(0x00, false); // MADCTL: memory data access control (portrait/landscape)
	Lcd_Write(0x3A, true);
	Lcd_Write(0x65, false); // COLMOD: Interface Pixel format
	Lcd_Write(0xB2, true);
	Lcd_Write(0x0C, false);
	Lcd_Write(0x0C, false);
	Lcd_Write(0x00, false);
	Lcd_Write(0x33, false);
	Lcd_Write(0x33, false); // PORCTRK: Porch setting
	Lcd_Write(0xB7, true);
	Lcd_Write(0x35, false); // GCTRL: Gate Control
	Lcd_Write(0xBB, true);
	Lcd_Write(0x2B, false); // VCOMS: VCOM setting
	Lcd_Write(0xC0, true);
	Lcd_Write(0x2C, false); // LCMCTRL: LCM Control
	Lcd_Write(0xC2, true);
	Lcd_Write(0x01, false);
	Lcd_Write(0xFF, false); // VDVVRHEN: VDV and VRH Command Enable
	Lcd_Write(0xC3, true);
	Lcd_Write(0x11, false); // VRHS: VRH Set
	Lcd_Write(0xC4, true);
	Lcd_Write(0x20, false); // VDVS: VDV Set
	Lcd_Write(0xC6, true);
	Lcd_Write(0x0F, false); // FRCTRL2: Frame Rate control in normal mode
	Lcd_Write(0xD0, true);
	Lcd_Write(0xA4, false);
	Lcd_Write(0xA1, false); // PWCTRL1: Power Control 1
	Lcd_Write(0xE0, true);
	Lcd_Write(0xD0, false);
	Lcd_Write(0x00, false);
	Lcd_Write(0x05, false);
	Lcd_Write(0x0E, false);
	Lcd_Write(0x15, false);
	Lcd_Write(0x0D, false);
	Lcd_Write(0x37, false);
	Lcd_Write(0x43, false);
	Lcd_Write(0x47, false);
	Lcd_Write(0x09, false);
	Lcd_Write(0x15, false);
	Lcd_Write(0x12, false);
	Lcd_Write(0x16, false);
	Lcd_Write(0x19, false); // PVGAMCTRL: Positive Voltage Gamma control
	Lcd_Write(0xE1, true);
	Lcd_Write(0xD0, false);
	Lcd_Write(0x00, false);
	Lcd_Write(0x05, false);
	Lcd_Write(0x0D, false);
	Lcd_Write(0x0C, false);
	Lcd_Write(0x06, false);
	Lcd_Write(0x2D, false);
	Lcd_Write(0x44, false);
	Lcd_Write(0x40, false);
	Lcd_Write(0x0E, false);
	Lcd_Write(0x1C, false);
	Lcd_Write(0x18, false);
	Lcd_Write(0x16, false);
	Lcd_Write(0x19, false); // NVGAMCTRL: Negative Voltage Gamma control
	Lcd_Write(0x29, true); // Display: On

	FillBlack();
}



