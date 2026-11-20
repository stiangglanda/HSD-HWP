#include "StateMachine.h"
#include "Lcd.h"
#include "Tsc.h"
#include <stdbool.h>
#include <stdint.h>

#define CAL_OBJ_SIZE    20U
#define CAL_SAMPLES     16U

typedef struct {
    uint16_t x;
    uint16_t y;
} CalPoint_t;

typedef struct {
    float x_offset;
    float y_offset;
    float x_scale;
    float y_scale;
} CalData_t;

static const RGB565_t COLOR_BLACK = { .R = 0,  .G = 0,  .B = 0  };
static const RGB565_t COLOR_BLUE  = { .R = 0,  .G = 0,  .B = 31 };
static const RGB565_t COLOR_WHITE = { .R = 31, .G = 63, .B = 31 };

static const uint16_t cornerPos[4][2] = {
    { 0,                          0                           },
    { LCD_WIDTH - CAL_OBJ_SIZE,   0                           },
    { 0,                          LCD_HEIGHT - CAL_OBJ_SIZE   },
    { LCD_WIDTH - CAL_OBJ_SIZE,   LCD_HEIGHT - CAL_OBJ_SIZE   }
};

static CalPoint_t rawCorners[4];
static CalData_t calData;
static uint8_t currentCorner = 0;
static bool waitForRelease = false;

static void DrawCorner(uint8_t index, RGB565_t color) {
    Lcd_FillRectangle(cornerPos[index][0], cornerPos[index][1],
                      CAL_OBJ_SIZE, CAL_OBJ_SIZE, color);
}

static void CalculateCalibration(void) {
    calData.x_offset = ((float)rawCorners[0].x + (float)rawCorners[2].x) / 2.0f;

    calData.y_offset = ((float)rawCorners[0].y + (float)rawCorners[1].y) / 2.0f;

    float distTopX    = (float)rawCorners[1].x - (float)rawCorners[0].x;
    float distBottomX = (float)rawCorners[3].x - (float)rawCorners[2].x;
    float avgDistX    = (distTopX + distBottomX) / 2.0f;

    if (avgDistX != 0.0f) {
        calData.x_scale = (float)(LCD_WIDTH - CAL_OBJ_SIZE) / avgDistX;
    }

    float distLeftY  = (float)rawCorners[2].y - (float)rawCorners[0].y;
    float distRightY = (float)rawCorners[3].y - (float)rawCorners[1].y;
    float avgDistY   = (distLeftY + distRightY) / 2.0f;

    if (avgDistY != 0.0f) {
        calData.y_scale = (float)(LCD_HEIGHT - CAL_OBJ_SIZE) / avgDistY;
    }
}

static void Enter(void) {
    currentCorner = 0;
    waitForRelease = false;

    Lcd_FillRectangle(0, 0, LCD_WIDTH, LCD_HEIGHT, COLOR_BLACK);
    DrawCorner(currentCorner, COLOR_BLUE);
}

static State_t const * Process(void) {
    bool touched = false;
    uint16_t x = 0;
    uint16_t y = 0;

    Tsc_Read(&touched, &x, &y, CAL_SAMPLES);

    // Wait for release
    if (waitForRelease) {
        if (!touched) {
            waitForRelease = false;

            if (currentCorner >= 4) {
                CalculateCalibration();
                return &State_A; // Calibration done
            }

            // Mark next corner
            DrawCorner(currentCorner, COLOR_BLUE);
        }
        return &State_Calibration;
    }

    // Store touch and mark corner
    if (touched) {
        rawCorners[currentCorner].x = x;
        rawCorners[currentCorner].y = y;

        DrawCorner(currentCorner, COLOR_WHITE);
        currentCorner++;
        waitForRelease = true;
    }

    return &State_Calibration;
}

static void Exit(void) {
    Lcd_FillRectangle(0, 0, LCD_WIDTH, LCD_HEIGHT, COLOR_BLACK);
}

State_t const State_Calibration = { Enter, Process, Exit };