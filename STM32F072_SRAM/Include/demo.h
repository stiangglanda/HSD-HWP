#ifndef STM32F072_SRAM_DEMO_H
#define STM32F072_SRAM_DEMO_H

#include <stdint.h>

/* Adressen für das Watch-Fenster, in main() eingetragen. */
typedef struct {
    uint32_t vectors;
    uint32_t ro_words;
    uint32_t rw_words;
    uint32_t bss_probe;
    uint32_t main_code;
    uint32_t pc_sample;
    uint32_t msp_sample;
} demo_addresses_t;

extern const uint32_t __Vectors[];
extern const uint32_t g_ro_words[4];
extern volatile uint32_t g_rw_words[4];
extern volatile uint32_t g_bss_probe[4];
extern volatile uint32_t g_selftest_fail;
extern volatile uint32_t g_initial_data_seen;
extern volatile uint32_t g_initial_bss_seen;
extern volatile demo_addresses_t g_addresses;

void ram_system_init(void);
int main(void);

/* Benötigte Register/Definitionen, wären sonst in HAL. */
#define REG32(address) (*(volatile uint32_t *)(uintptr_t)(address))
#define RCC_APB2ENR    REG32(0x40021018u)
#define SYSCFG_CFGR1   REG32(0x40010000u)
#define SRAM_BASE      0x20000000u
#define SRAM_LIMIT     0x20004000u

#endif
