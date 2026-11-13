#include "Lcd.h"
#include "Gpio.h"
#include <stddef.h>
#include <stm32f072xb.h>

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
static uint32_t const GPIO_LCD_BSSR_WRITE_OFF = (uint32_t)(SET_WR_MASK);								// 0x00000400

static inline void Lcd_Write(uint8_t data, bool command)
{
	Gpio_Set(GPIO_ID_TFT_DC, command);				  // Data (1) or command (0) byte
	GPIOE->BSRR = (GPIO_LCD_BSSR_WRITE_ON | data); // enable writing mode + write data
	GPIOE->BSRR = GPIO_LCD_BSSR_WRITE_OFF;			  // disable writing mode
}

void Lcd_Initialize(void)
{
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

	Lcd_Write(0x11, LCD_Command); // exit SLEEP mode
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
	Lcd_Write(0x19, LCD_Data);		// NVGAMCTRL: Negative Voltage Gamma control
	Lcd_Write(0x29, LCD_Command); // Display: On

	for (int i = 0; i < 2; i++)
	{
		SetToBlack();
		SetToWhite();
	}
}

void SetToWhite(void)
{
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

	for (uint32_t index_y = 0; index_y < LCD_HEIGHT; index_y++)
	{
		for (uint32_t index_x = 0; index_x < LCD_WIDTH; index_x++)
		{
			Lcd_Write(0xFF, LCD_Data);
			Lcd_Write(0xFF, LCD_Data);
		}
	}
}

void SetToBlack(void)
{
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

	for (uint32_t index_y = 0; index_y < LCD_HEIGHT; index_y++)
	{
		for (uint32_t index_x = 0; index_x < LCD_WIDTH; index_x++)
		{
			Lcd_Write(0x00, LCD_Data);
			Lcd_Write(0x00, LCD_Data);
		}
	}
}

static void Lcd_SetArea(
	 uint_fast16_t xStart,
	 uint_fast16_t xEnd,
	 uint_fast16_t yStart,
	 uint_fast16_t yEnd)
{
	Lcd_Write(0x2A, LCD_Command); // CASET
	Lcd_Write((uint8_t)(xStart >> 8), LCD_Data);
	Lcd_Write((uint8_t)(xStart & 0xFF), LCD_Data);
	Lcd_Write((uint8_t)(xEnd >> 8), LCD_Data);
	Lcd_Write((uint8_t)(xEnd & 0xFF), LCD_Data);

	Lcd_Write(0x2B, LCD_Command); // RASET
	Lcd_Write((uint8_t)(yStart >> 8), LCD_Data);
	Lcd_Write((uint8_t)(yStart & 0xFF), LCD_Data);
	Lcd_Write((uint8_t)(yEnd >> 8), LCD_Data);
	Lcd_Write((uint8_t)(yEnd & 0xFF), LCD_Data);
}

void Lcd_BeginWrite(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	Lcd_SetArea(x, x + width - 1, y, y + height - 1);
	Lcd_Write(0x2C, LCD_Command); // RAMWR
}

void Lcd_WritePixel(RGB565_t color)
{
	uint16_t value = (uint16_t)((color.R << 11) | (color.G << 5) | color.B);
	Lcd_Write((uint8_t)(value >> 8), LCD_Data);
	Lcd_Write((uint8_t)(value & 0xFF), LCD_Data);
}

int Lcd_FillRectangle(
	 uint_fast16_t x,
	 uint_fast16_t y,
	 uint_fast16_t width,
	 uint_fast16_t height,
	 RGB565_t color)
{
	if (width == 0 || height == 0 || x + width > LCD_WIDTH || y + height > LCD_HEIGHT)
	{
		return -1;
	}

	Lcd_BeginWrite(x, y, width, height);

	for (uint32_t i = 0; i < width * height; i++)
	{
		Lcd_WritePixel(color);
	}
	return 0;
}

int Lcd_Draw(
	 uint_fast16_t x,
	 uint_fast16_t y,
	 uint_fast16_t width,
	 uint_fast16_t height,
	 RGB565_t const *data)
{
	if (width == 0 || height == 0 || x + width > LCD_WIDTH || y + height > LCD_HEIGHT)
	{
		return -1;
	}

	Lcd_BeginWrite(x, y, width, height);

	for (uint32_t i = 0; i < width * height; i++)
	{
		Lcd_WritePixel(data[i]);
	}
	return 0;
}

int Lcd_DrawMonochrome(
	 uint_fast16_t x,
	 uint_fast16_t y,
	 uint_fast16_t width,
	 uint_fast16_t height,
	 uint8_t const *data,
	 RGB565_t foreground,
	 RGB565_t background)
{
	if (width == 0 || height == 0)
	{
		return -1;
	}

	// Image is completely outside the display
	if (x >= LCD_WIDTH || y >= LCD_HEIGHT)
	{
		return 0;
	}

	// Only draw the visible part
	uint_fast16_t visibleWidth = (x + width > LCD_WIDTH) ? (LCD_WIDTH - x) : width;
	uint_fast16_t visibleHeight = (y + height > LCD_HEIGHT) ? (LCD_HEIGHT - y) : height;

	Lcd_BeginWrite(x, y, visibleWidth, visibleHeight);

	for (uint_fast16_t row = 0; row < visibleHeight; row++)
	{
		for (uint_fast16_t col = 0; col < visibleWidth; col++)
		{
			uint_fast16_t bitIndex = row * width + col;
			// Read pixel bit: pick the byte, shift the bit to the right end, keep only that bit
			uint8_t bit = (data[bitIndex / 8] >> (bitIndex % 8)) & 1;

			Lcd_WritePixel(bit ? foreground : background);
		}
	}

	return 0;
}

int Lcd_PrintCharacter(
	 uint_fast16_t *px,
	 uint_fast16_t *py,
	 char character,
	 RGB565_t foreground,
	 RGB565_t background,
	 Font_t const *font)
{
	if (px == NULL || py == NULL || font == NULL)
	{
		return -1;
	}

	if (character == '\n')
	{
		*py += font->LineHeight;
		return 0;
	}

	if (character == '\t')
	{
		// Tab = 4 spaces
		for (int i = 0; i < 4; i++)
		{
			int result = Lcd_PrintCharacter(px, py, ' ', foreground, background, font);
			if (result != 0)
			{
				return result;
			}
		}
		return 0;
	}

	Glyph_t const *glyph = font->GetGlyph(character);
	if (glyph == NULL)
	{
		return -1;
	}

	int result = Lcd_DrawMonochrome(*px, *py, glyph->Width, font->LineHeight, glyph->Data, foreground, background);
	*px += glyph->Width;
	return result;
}

int Lcd_Print(
	 uint_fast16_t x,
	 uint_fast16_t y,
	 char const *string,
	 RGB565_t foreground,
	 RGB565_t background,
	 Font_t const *font)
{
	if (string == NULL)
	{
		return -1;
	}

	uint_fast16_t startX = x;

	for (char const *c = string; *c != '\0'; c++)
	{
		int result = Lcd_PrintCharacter(&x, &y, *c, foreground, background, font);
		if (result != 0)
		{
			return result;
		}

		if (*c == '\n')
		{
			x = startX; // new line starts at the left again
		}
	}
	return 0;
}