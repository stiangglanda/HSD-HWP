#include "Lcd.h"
#include "Gpio.h"

RGB565_t const RGB565_BLACK = { .R = 0x00, .G = 0x00, .B = 0x00 };
RGB565_t const RGB565_GREY  = { .R = 0x0F, .G = 0x1F, .B = 0x0F };
RGB565_t const RGB565_WHITE = { .R = 0x1F, .G = 0x3F, .B = 0x1F };
RGB565_t const RGB565_RED   = { .R = 0x1F, .G = 0x00, .B = 0x00 };
RGB565_t const RGB565_GREEN = { .R = 0x00, .G = 0x3F, .B = 0x00 };
RGB565_t const RGB565_BLUE  = { .R = 0x00, .G = 0x00, .B = 0x1F };

// ToDo: Set Defines for commands
#define CASET 
#define RASET 

static inline void Lcd_Write(uint8_t data, bool command) {
	// We start a transmission by setting WRX to low
	
	// Decide, whether command or data byte and control DCX
	if (command) {
		// Control DCX
		
	} else {
		// Control DCX
		
	}
	// We write data to our pins via BSRR
	
	// We end a transmission by setting WRX to high
	
}

void Lcd_Initialize(void) {
	// ToDo: use GPIO_Initialize with relevant pins for CS, Data / Command, WR, RD, RES, DB0 - DB7
	
	
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
}



