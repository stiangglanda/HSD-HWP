#include "demo.h"

/* Die Scatter-Datei legt DEMO_RO an SRAM-Adresse ToDo. */
__attribute__((section("DEMO_RO"), used, aligned(4)))
const uint32_t g_ro_words[4] = {
    0x11223344u, 0xA5A55A5Au, 0xCAFEBABEu, 0x5352414Du
};

/* Die Scatter-Datei legt diese Marker an feste SRAM-Adressen für RO (ToDo). */
__attribute__((section("DEMO_RW"), used, aligned(4)))
volatile uint32_t g_rw_words[4] = {
    0x12345678u, 0x89ABCDEFu, 0x13579BDFu, 0x2468ACE0u
};

/* __main der normalen C-Library setzt diese ZI/.bss-Variablen auf null. */
volatile uint32_t g_bss_probe[4];
volatile uint32_t g_initial_data_seen;
volatile uint32_t g_initial_bss_seen;
volatile demo_addresses_t g_addresses;

static inline uint32_t read_msp(void) {
    uint32_t value;
    __asm volatile ("mrs %0, msp" : "=r" (value));
    return value;
}

static inline uint32_t read_pc(void) {
    uint32_t value;
    __asm volatile ("mov %0, pc" : "=r" (value));
    return value;
}

/* Diese Funktion läuft vor main und mappt SRAM auf Adresse 0. */
void ram_system_init(void) {
    SYSCFG_CFGR1 = (SYSCFG_CFGR1 & ~3u) | 3u; /* SRAM bei Adresse 0. */
    __asm volatile ("dsb\n\tisb" ::: "memory"); /* Memory Barrier mit neuer Vektortabelle */
}

int main(void) {
    uint32_t i;
    const volatile uint32_t *vectors_in_sram =
        (const volatile uint32_t *)(uintptr_t)SRAM_BASE;

    /* Anfangszustand von RW und ZI fuer das Watch-Fenster sichern. */
    g_initial_data_seen = g_rw_words[0];
    g_initial_bss_seen = g_bss_probe[0];

    g_addresses.vectors = (uint32_t)(uintptr_t)__Vectors;
    g_addresses.ro_words = (uint32_t)(uintptr_t)g_ro_words;
    g_addresses.rw_words = (uint32_t)(uintptr_t)g_rw_words;
    g_addresses.bss_probe = (uint32_t)(uintptr_t)g_bss_probe;
    g_addresses.main_code = (uint32_t)(uintptr_t)&main;
    g_addresses.pc_sample = read_pc();
    g_addresses.msp_sample = read_msp();

    /* ZI nach der Initialisierung veraendern. */
    g_bss_probe[0] = 0xDEADBEEFu;
    g_bss_probe[1] = 0x01020304u;
    g_bss_probe[2] = 0x55667788u;
    g_bss_probe[3] = 0xAABBCCDDu;

    /* Hier sind alle Werte im Watch Window bereit. */
    while (1) {
        __asm volatile ("nop");
    }
}
