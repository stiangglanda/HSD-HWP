#include "Lcd.h"
#include <stm32f072xb.h>

void Systemconfig_Clock(void);

int main() {
    Systemconfig_Clock();

    Lcd_Initialize();

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