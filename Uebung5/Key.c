#include "Key.h"
#include "Gpio.h"
#include "Timer.h"
#include "EventQueue.h"

#define KEY_CHECK_INTERVAL_MS 50
#define KEY_MIN_PRESS_MS      100
#define KEY_MAX_PRESS_MS      1000

static uint32_t wakeUpCount = 0;
static uint32_t user0Count = 0;
static uint32_t user1Count = 0;

// Returns true if a valid key press just ended
static bool UpdateKey(int gpioId, uint32_t * counter) {
    bool pressed = false;
    Gpio_Get(gpioId, &pressed);

    if (pressed) {
        (*counter)++;
        return false;
    }

    uint32_t time = *counter * KEY_CHECK_INTERVAL_MS;
    *counter = 0;
    return (time >= KEY_MIN_PRESS_MS && time < KEY_MAX_PRESS_MS);
}

static void SendKeyEvent(int32_t key) {
    Event_t event = { 1, key, 0, 0 };
    EventQueue_Put(&event);
}

static void CheckCallback(int id) {
    (void)id;

    UpdateKey(GPIO_ID_BUTTON_WAKE_UP, &wakeUpCount); // no event for Wake-Up

    if (UpdateKey(GPIO_ID_BUTTON_USER0, &user0Count)) {
        SendKeyEvent(0);
    }
    if (UpdateKey(GPIO_ID_BUTTON_USER1, &user1Count)) {
        SendKeyEvent(1);
    }
}

int Key_Initialize(void) {
    wakeUpCount = 0;
    user0Count = 0;
    user1Count = 0;

    Gpio_Initialize(GPIO_ID_BUTTON_WAKE_UP, GPIO_MODE_INPUT, false);
    Gpio_Initialize(GPIO_ID_BUTTON_USER0, GPIO_MODE_INPUT, false);
    Gpio_Initialize(GPIO_ID_BUTTON_USER1, GPIO_MODE_INPUT, false);

    Timer_Initialize(TIMER_ID_TIM6);
    return Timer_Enable(TIMER_ID_TIM6, CheckCallback, KEY_CHECK_INTERVAL_MS, TIME_UNIT_MS, true);
}