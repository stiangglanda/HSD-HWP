#include "StateMachine.h"
#include "Lcd.h"
#include "Tsc.h"
#include <stdbool.h>
#include <stdint.h>

#define PAINT_BRUSH_SIZE    4U
#define PAINT_SAMPLES       8U

static const RGB565_t COLOR_BLACK = { .R = 0,  .G = 0, .B = 0 };
static const RGB565_t COLOR_RED   = { .R = 31, .G = 0, .B = 0 };

static void Enter(void) {
    Lcd_FillRectangle(0, 0, LCD_WIDTH, LCD_HEIGHT, COLOR_BLACK);
}

static State_t const * Process(void) {
    bool touched = false;
    uint16_t xTsc = 0;
    uint16_t yTsc = 0;

    if (Tsc_Read(&touched, &xTsc, &yTsc, PAINT_SAMPLES) == 0 && touched) {
        uint16_t xLcd = 0;
        uint16_t yLcd = 0;

        Tsc_ConvertToLcd(xTsc, yTsc, &xLcd, &yLcd);

        // Sicherstellen, dass das Quadrat komplett innerhalb des Displays bleibt
        if (xLcd > (LCD_WIDTH - PAINT_BRUSH_SIZE)) {
            xLcd = LCD_WIDTH - PAINT_BRUSH_SIZE;
        }
        if (yLcd > (LCD_HEIGHT - PAINT_BRUSH_SIZE)) {
            yLcd = LCD_HEIGHT - PAINT_BRUSH_SIZE;
        }

        Lcd_FillRectangle(xLcd, yLcd, PAINT_BRUSH_SIZE, PAINT_BRUSH_SIZE, COLOR_RED);
    }

    return &State_Paint;
}

static void Exit(void) {
    Lcd_FillRectangle(0, 0, LCD_WIDTH, LCD_HEIGHT, COLOR_BLACK);
}

State_t const State_Paint = { Enter, Process, Exit };