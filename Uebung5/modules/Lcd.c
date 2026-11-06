#include "Lcd.h"
#include "Gpio.h"
#include <stm32f072xb.h>

#define GPIO_LOW false
#define GPIO_HIGH true
#define LCD_Command true
#define LCD_Data false

#define BYTEMASK 0xFF
#define DATALINE_RESET_OFFSET 16
#define CLEAR_DATALINE_MASK (BYTEMASK << DATALINE_RESET_OFFSET)

#define BITMASK 0x1
#define WR_RESET_OFFSET 26
#define CLEAR_WR_MASK (BITMASK << WR_RESET_OFFSET)

#define WR_SET_OFFSET 10
#define SET_WR_MASK (BITMASK << WR_SET_OFFSET)

// Mask for write enable with cleared dataline and reset of write (disable)
static uint32_t const GPIO_LCD_BSSR_WRITE_ON = (uint32_t)(CLEAR_WR_MASK | CLEAR_DATALINE_MASK); // 0x04FF0000
static uint32_t const GPIO_LCD_BSSR_WRITE_OFF = (uint32_t)(SET_WR_MASK);	// 0x00000400

static inline void Lcd_Write(uint8_t data, bool command){
  Gpio_Set(GPIO_ID_TFT_DC, !command);  						// Data (1) or command (0) byte
  GPIOE->BSRR = (GPIO_LCD_BSSR_WRITE_ON | data); 	// enable writing mode + write data
  GPIOE->BSRR = GPIO_LCD_BSSR_WRITE_OFF;   				// disable writing mode
}

int Lcd_Initialize(void) {
	Gpio_Initialize(GPIO_ID_TFT_CS, GPIO_MODE_OUTPUT, GPIO_LOW);
	Gpio_Initialize(GPIO_ID_TFT_DC, GPIO_MODE_OUTPUT, GPIO_LOW);
	Gpio_Initialize(GPIO_ID_TFT_RD, GPIO_MODE_OUTPUT, GPIO_HIGH);
	Gpio_Initialize(GPIO_ID_TFT_RES, GPIO_MODE_OUTPUT, GPIO_HIGH);
	Gpio_Initialize(GPIO_ID_TFT_WR, GPIO_MODE_OUTPUT, GPIO_HIGH);
	
	Gpio_Initialize(GPIO_ID_TFT_D0, GPIO_MODE_OUTPUT, GPIO_LOW);
	Gpio_Initialize(GPIO_ID_TFT_D1, GPIO_MODE_OUTPUT, GPIO_LOW);
	Gpio_Initialize(GPIO_ID_TFT_D2, GPIO_MODE_OUTPUT, GPIO_LOW);
	Gpio_Initialize(GPIO_ID_TFT_D3, GPIO_MODE_OUTPUT, GPIO_LOW);
	Gpio_Initialize(GPIO_ID_TFT_D4, GPIO_MODE_OUTPUT, GPIO_LOW);
	Gpio_Initialize(GPIO_ID_TFT_D5, GPIO_MODE_OUTPUT, GPIO_LOW);
	Gpio_Initialize(GPIO_ID_TFT_D6, GPIO_MODE_OUTPUT, GPIO_LOW);
	Gpio_Initialize(GPIO_ID_TFT_D7, GPIO_MODE_OUTPUT, GPIO_LOW);		

	Lcd_Write(0x11, LCD_Command); //exit SLEEP mode
	Lcd_Write(0x36, LCD_Command);
	Lcd_Write(0x00, LCD_Data); // MADCTL: memory data access control (portrait/landscape)
	Lcd_Write(0x3A, LCD_Command);
	Lcd_Write(0x65, LCD_Data); // COLMOD: Interface Pixel format
	Lcd_Write(0xB2, LCD_Command);
	Lcd_Write(0x0C, LCD_Data);
	Lcd_Write(0x0C, LCD_Data);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x33, LCD_Data);
	Lcd_Write(0x33, LCD_Data); // PORCTRK: Porch setting
	Lcd_Write(0xB7, LCD_Command);
	Lcd_Write(0x35, LCD_Data); // GCTRL: Gate Control
	Lcd_Write(0xBB, LCD_Command);
	Lcd_Write(0x2B, LCD_Data); // VCOMS: VCOM setting
	Lcd_Write(0xC0, LCD_Command);
	Lcd_Write(0x2C, LCD_Data); // LCMCTRL: LCM Control
	Lcd_Write(0xC2, LCD_Command);
	Lcd_Write(0x01, LCD_Data);
	Lcd_Write(0xFF, LCD_Data); // VDVVRHEN: VDV and VRH Command Enable
	Lcd_Write(0xC3, LCD_Command);
	Lcd_Write(0x11, LCD_Data); // VRHS: VRH Set
	Lcd_Write(0xC4, LCD_Command);
	Lcd_Write(0x20, LCD_Data); // VDVS: VDV Set
	Lcd_Write(0xC6, LCD_Command);
	Lcd_Write(0x0F, LCD_Data); // FRCTRL2: Frame Rate control in normal mode
	Lcd_Write(0xD0, LCD_Command);
	Lcd_Write(0xA4, LCD_Data);
	Lcd_Write(0xA1, LCD_Data); // PWCTRL1: Power Control 1
	Lcd_Write(0xE0, LCD_Command);
	Lcd_Write(0xD0, LCD_Data);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x05, LCD_Data);
	Lcd_Write(0x0E, LCD_Data);
	Lcd_Write(0x15, LCD_Data);
	Lcd_Write(0x0D, LCD_Data);
	Lcd_Write(0x37, LCD_Data);
	Lcd_Write(0x43, LCD_Data);
	Lcd_Write(0x47, LCD_Data);
	Lcd_Write(0x09, LCD_Data);
	Lcd_Write(0x15, LCD_Data);
	Lcd_Write(0x12, LCD_Data);
	Lcd_Write(0x16, LCD_Data);
	Lcd_Write(0x19, LCD_Data); // PVGAMCTRL: Positive Voltage Gamma control	
	Lcd_Write(0xE1, LCD_Command);
	Lcd_Write(0xD0, LCD_Data);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x05, LCD_Data);
	Lcd_Write(0x0D, LCD_Data);
	Lcd_Write(0x0C, LCD_Data);
	Lcd_Write(0x06, LCD_Data);
	Lcd_Write(0x2D, LCD_Data);
	Lcd_Write(0x44, LCD_Data);
	Lcd_Write(0x40, LCD_Data);
	Lcd_Write(0x0E, LCD_Data);
	Lcd_Write(0x1C, LCD_Data);
	Lcd_Write(0x18, LCD_Data);
	Lcd_Write(0x16, LCD_Data);
	Lcd_Write(0x19, LCD_Data); // NVGAMCTRL: Negative Voltage Gamma control
	Lcd_Write(0x29, LCD_Command); // Display: On
	
	for (int i = 0; i < 2; i++) {
		SetToBlack();
		SetToWhite();
	}	
		
	return 0;	
}

void SetToWhite(void) {
	// WRITE CASET with fixed start and stop
	Lcd_Write(0x2A, LCD_Command);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0xEF, LCD_Data);
	
	// WRITE RASET with fixed start and stop
	Lcd_Write(0x2B, LCD_Command);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x01, LCD_Data);
	Lcd_Write(0x3F, LCD_Data);
	
	// Memory Write
	Lcd_Write(0x2C, LCD_Command);
	
	for (uint32_t index_y = 0; index_y < LCD_HEIGHT; index_y++) {
		for (uint32_t index_x = 0; index_x < LCD_WIDTH; index_x++) {
			Lcd_Write(0xFF, LCD_Data);
			Lcd_Write(0xFF, LCD_Data);
		}
	}
}

void SetToBlack(void) {
	// WRITE CASET with fixed start and stop
	Lcd_Write(0x2A, LCD_Command);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0xEF, LCD_Data);
	
	// WRITE RASET with fixed start and stop
	Lcd_Write(0x2B, LCD_Command);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x00, LCD_Data);
	Lcd_Write(0x01, LCD_Data);
	Lcd_Write(0x3F, LCD_Data);
	
	// Memory Write
	Lcd_Write(0x2C, LCD_Command);
	
	for (uint32_t index_y = 0; index_y < LCD_HEIGHT; index_y++) {
		for (uint32_t index_x = 0; index_x < LCD_WIDTH; index_x++) {
			Lcd_Write(0x00, LCD_Data);
			Lcd_Write(0x00, LCD_Data);
		}
	}
}

void Lcd_BeginWrite(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
	// WRITE CASET with fixed start and stop
	Lcd_Write(0x2A, LCD_Command);

	// TODO: Calculate Start High Byte / Low Byte for XStart
	//Lcd_Write(0x00, LCD_Data);
	//Lcd_Write(0x00, LCD_Data);

	//TODO: Calculate Stop High Byte / Low Byte for XEnd
	//Lcd_Write(0x00, LCD_Data);
	//Lcd_Write(0xEF, LCD_Data);
	
	// WRITE RASET with fixed start and stop
	Lcd_Write(0x2B, LCD_Command);
	// TODO: Calculate Start High Byte / Low Byte for YStart
	//Lcd_Write(0x00, LCD_Data);
	//Lcd_Write(0x00, LCD_Data);

	//TODO: Calculate Stop High Byte / Low Byte for YEnd
	//Lcd_Write(0x01, LCD_Data);
	//Lcd_Write(0x3F, LCD_Data);

	// Memory Write
	Lcd_Write(0x2C, LCD_Command);	
}

void Lcd_WritePixel(RGB565_t color) {
	//TODO: Convert RGB565_t to uint8_t Bytes
	//Lcd_Write(0x00, LCD_Data); //Red and Green Bits
	//Lcd_Write(0x00, LCD_Data); // Green and Blue Bits
}

int Lcd_Fill(uint_fast16_t x, uint_fast16_t y, uint_fast16_t width, uint_fast16_t height, RGB565_t color) {
	Lcd_BeginWrite(x, y, width, height);
	
	for (uint32_t index_y = 0; index_y < height; index_y++) {
		for (uint32_t index_x = 0; index_x < width; index_x++) {
			Lcd_WritePixel(color);
		}
	}
	
	return 0;
}

int Lcd_Draw(uint_fast16_t x, uint_fast16_t y, uint_fast16_t width, uint_fast16_t height, RGB565_t const * data) {
	Lcd_BeginWrite(x, y, width, height);
	
	for (uint32_t index_y = 0; index_y < height; index_y++) {
		for (uint32_t index_x = 0; index_x < width; index_x++) {
			Lcd_WritePixel(data[index_y * width + index_x]);
		}
	}
	
	return 0;
}

int Lcd_DrawMonochrome(uint_fast16_t x, uint_fast16_t y, uint_fast16_t width, uint_fast16_t height, uint8_t const * data, RGB565_t foreground, RGB565_t background) {
	Lcd_BeginWrite(x, y, width, height);
	
	for (uint32_t index_y = 0; index_y < height; index_y++) {
		for (uint32_t index_x = 0; index_x < width; index_x++) {
			uint8_t byte = data[(index_y * width + index_x) / 8];
			uint8_t bit = (byte >> (7 - (index_x % 8))) & 0x01;
			if (bit) {
				Lcd_WritePixel(foreground);
			} else {
				Lcd_WritePixel(background);
			}
		}
	}
	
	return 0;
}

int Lcd_PrintCharacter(uint_fast16_t* x, uint_fast16_t* y, char character, RGB565_t foreground, RGB565_t background, Font_t const * font) {
	// TODO: Implement character printing
	(void)x;
	(void)y;
	(void)character;
	(void)foreground;
	(void)background;
	(void)font;

	//Access font height and width / font->glyph width
	//Lcd_beginWrite(x, y, font->width, font->height);

	//iterate over with and height
		// is pixel the ninth bit?
			// Change / increment pointer
		//Derefrence pointer for uint8_t value
		//is bit high =1
			//lcd_writePixel(foreground)
		//is bit low =0
			//lcd_writePixel(background)

	// increment x if possible by glyph width
		//check wether y increment is possible
			// increment y
		//return error
	return 0; 
}

int Lcd_Print(uint_fast16_t x, uint_fast16_t y, char const * string, RGB565_t foreground, RGB565_t background, Font_t const * font) {
	while (*string != '\0') {
		uint_fast16_t character_x = x;
		uint_fast16_t character_y = y;
		Lcd_PrintCharacter(&character_x, &character_y, *string, foreground, background, font);
		x += font->GetGlyph(*string)->Width;
		string++;
	}
	return 0;
}