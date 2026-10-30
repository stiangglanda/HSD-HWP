#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
Configuration
******************************************************************************/


/******************************************************************************
Defines the value to use if the LCD should be used in portrait mode.
******************************************************************************/
#define LCD_MODE_PORTRAIT  1

/******************************************************************************
Defines the value to use if the LCD should be used in landscape mode.
******************************************************************************/
#define LCD_MODE_LANDSCAPE 2

/******************************************************************************
Configures the mode in which the LCD will be used.
******************************************************************************/
#define LCD_MODE LCD_MODE_PORTRAIT


/******************************************************************************
Definitions
******************************************************************************/

typedef struct RGB565_s { uint16_t B:5; uint16_t G:6; uint16_t R:5; } RGB565_t;
typedef struct Image_s { uint16_t Width; uint16_t Height; RGB565_t const * Data; } Image_t;
typedef struct MonochromeImage_s { uint16_t Width; uint16_t Height; uint8_t const * Data; } MonochromeImage_t;
typedef struct Glyph_s { uint8_t const * Data; uint16_t Width; uint64_t:16; } Glyph_t;
typedef struct Font_s { Glyph_t const * (*GetGlyph)(char); uint16_t LineHeight; uint64_t:16; } Font_t;

extern RGB565_t const RGB565_BLACK;
extern RGB565_t const RGB565_GREY;
extern RGB565_t const RGB565_WHITE;
extern RGB565_t const RGB565_RED;
extern RGB565_t const RGB565_GREEN;
extern RGB565_t const RGB565_BLUE;

extern Font_t const Consolas;
extern Font_t const SegoeUI;
extern Image_t const Image;
extern MonochromeImage_t const Image2;


#if LCD_MODE == LCD_MODE_PORTRAIT

/******************************************************************************
Defines the width of the display in pixel.
******************************************************************************/
#define LCD_WIDTH  240

/******************************************************************************
Defines the height of the display in pixel.
******************************************************************************/
#define LCD_HEIGHT 320
	
#endif

#if LCD_MODE == LCD_MODE_LANDSCAPE

/******************************************************************************
Defines the width of the display in pixel.
******************************************************************************/
#define LCD_WIDTH  320
	
/******************************************************************************
Defines the height of the display in pixel.
******************************************************************************/
#define LCD_HEIGHT 240

#endif


/******************************************************************************
Initializes the LCD module and the required GPIOs.

returns: Zero on success, an error code otherwise.
  0: Success
  1: Required GPIOs could not be initialized.
******************************************************************************/
int Lcd_Initialize(void);

/******************************************************************************
Fills the specified rectangular region with the specified color.

x: The X coordinate of the upper left corner of the rectangle in pixels.
y: Thy Y coordiante of the upper left corner of the rectangle in pixels.
width: The width of the rectangle in pixels.
height: The height of the rectangle in pixels.
color: The RGB565 color to use.

returns: Zero on success, an error code otherwise.
0: Success
1: All pixels are outside the available display area.
2: No pixels to draw.
3: One or more pixels are outside the available display area.

Pixels outside the display are are ignored. Other pixels are still set.
******************************************************************************/
int Lcd_Fill(
 uint_fast16_t x,
 uint_fast16_t y,
 uint_fast16_t width,
 uint_fast16_t height,
 RGB565_t      color);

/******************************************************************************
Draws the specified RGB565 image at the specified location.

x: The X coordinate of the upper left corner of the image in pixels.
y: Thy Y coordiante of the upper left corner of the image in pixels.
width: The width of the image in pixels.
height: The height of the image in pixels.
data: A pointer to the image data (RGB565 color array).

returns: Zero on success, an error code otherwise.
0: Success
1: All pixels are outside the available display area.
2: No pixels to draw.
3: One or more pixels are outside the available display area.

Pixels outside the display are are ignored. Other pixels are still set.
******************************************************************************/
int Lcd_Draw(
 uint_fast16_t    x,
 uint_fast16_t    y,
 uint_fast16_t    width,
 uint_fast16_t    height,
 RGB565_t const * data);

/******************************************************************************
Draws the specified monochrome image at the specified location.

x: The X coordinate of the upper left corner of the image in pixels.
y: Thy Y coordiante of the upper left corner of the image in pixels.
width: The width of the image in pixels.
height: The height of the image in pixels.
data: A pointer to the image data (monochrome/bit array).
foreground: The foreground color to use.
background: The background color to use.

returns: Zero on success, an error code otherwise.
0: Success
1: All pixels are outside the available display area.
2: No pixels to draw.
3: One or more pixels are outside the available display area.

Pixels outside the display are are ignored. Other pixels are still set.
******************************************************************************/
int Lcd_DrawMonochrome(
 uint_fast16_t   x,
 uint_fast16_t   y,
 uint_fast16_t   width,
 uint_fast16_t   height,
 uint8_t const * data,
 RGB565_t        foreground,
 RGB565_t        background);

/******************************************************************************
Prints the specified character at the specified location and advances the
position by the width of the character.

x: The X coordinate of the upper left corner of the character in pixels.
y: Thy Y coordiante of the upper left corner of the character in pixels.
character: The character to draw.
foreground: The foreground color to use.
background: The background color to use.

returns: Zero on success, an error code otherwise.
0: Success
1: All pixels are outside the available display area.
2: No pixels to draw.
3: One or more pixels are outside the available display area.
******************************************************************************/
int Lcd_PrintCharacter(
 uint_fast16_t * x,
 uint_fast16_t * y,
 char            character,
 RGB565_t        foreground,
 RGB565_t        background,
 Font_t const  * font);

/******************************************************************************
Prints the specified string at the specified location.

x: The X coordinate of the upper left corner of the character in pixels.
y: Thy Y coordiante of the upper left corner of the character in pixels.
string: A zero terminated character string.
foreground: The foreground color to use.
background: The background color to use.

returns: Zero on success, an error code otherwise.
0: Success
1: All pixels are outside the available display area.
2: No pixels to draw.
3: One or more pixels are outside the available display area.
******************************************************************************/
int Lcd_Print(
 uint_fast16_t   x,
 uint_fast16_t   y,
 char const    * string,
 RGB565_t        foreground,
 RGB565_t        background,
 Font_t const  * font);

#endif // LCD_H
