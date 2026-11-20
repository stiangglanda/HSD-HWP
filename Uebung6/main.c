#include "Lcd.h"
#include "Tsc.h"
#include <stm32f072xb.h>
#include <stdio.h>

void Systemconfig_Clock(void);



int main() {
    Systemconfig_Clock();

    Lcd_Initialize();
    Tsc_Initialize();

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

    char buffer[40];
    uint16_t touchX = 0;
    uint16_t touchY = 0;

    while (true) {
        if (Tsc_TestRead(&touchX, &touchY)) {
            // Grünes Kästchen = Touch erkannt
            Lcd_FillRectangle(10, 40, 30, 30, green);
            snprintf(buffer, sizeof(buffer), "Touch: JA   X:%4u Y:%4u", touchX, touchY);
        } else {
            // Rotes Kästchen = kein Touch
            Lcd_FillRectangle(10, 40, 30, 30, red);
            snprintf(buffer, sizeof(buffer), "Touch: NEIN X:---- Y:----");
        }

        Lcd_Print(10, 85, buffer, white, black, &Consolas);

        // Kurze Pause gegen Flackern auf dem Display
        for (volatile uint32_t i = 0; i < 100000; i++) {
            __asm volatile ("nop");
        }
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