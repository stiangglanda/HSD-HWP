#include "Lcd.h"
#include <stm32f072xb.h>

void Systemconfig_Clock(void);

int main() {
    Systemconfig_Clock();

    Lcd_Initialize();

    RGB565_t red   = { .R = 31, .G = 0,  .B = 0  };
    RGB565_t green = { .R = 0,  .G = 63, .B = 0  };
    RGB565_t blue  = { .R = 0,  .G = 0,  .B = 31 };

    Lcd_FillRectangle(10, 10, 100, 50, red);
    Lcd_FillRectangle(10, 70, 100, 50, green);
    Lcd_FillRectangle(10, 130, 100, 50, blue);

    RGB565_t black = { .R = 0,  .G = 0,  .B = 0  };
    RGB565_t white = { .R = 31, .G = 63, .B = 31 };

    Lcd_Print(10, 10, "Hallo Welt\nZeile 2\tTab", white, black, &Consolas);

    uint_fast16_t x = (LCD_WIDTH - Image.Width) / 2;
    uint_fast16_t y = (LCD_HEIGHT - Image.Height) / 2;

    Lcd_Draw(x, y, Image.Width, Image.Height, Image.Data);

    while (true) {
    }
}

void Systemconfig_Clock(void) {
    // Enable the internal 48 MHz Oscillator
    RCC->CR2 |= RCC_CR2_HSI48ON;
    while ((RCC->CR2 & RCC_CR2_HSI48RDY) == 0) {}

    // Configure flash before setting new clock frequency
    FLASH->ACR |= FLASH_ACR_LATENCY | FLASH_ACR_PRFTBE;

    RCC->CFGR = (RCC->CFGR &
                 ~(RCC_CFGR_SW | RCC_CFGR_HPRE | RCC_CFGR_PPRE))
                 | RCC_CFGR_SW_HSI48;

    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI48) {}

    SystemCoreClock = 48000000U;
}