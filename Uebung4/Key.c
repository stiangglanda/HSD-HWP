#include "Key.h"
#include "Gpio.h"
#include "Timer.h"
#include "EventQueue.h"

static uint32_t buttonWakeUpPressCount = 0;
static uint32_t buttonUser0PressCount = 0;
static uint32_t buttonUser1PressCount = 0;

static void CheckCallback(int id) {
    bool buttonState;
	Gpio_Get(GPIO_ID_BUTTON_WAKE_UP, &buttonState);
    if(buttonState) {
        buttonWakeUpPressCount++;
    } else {
        if(buttonWakeUpPressCount >= 2 && buttonWakeUpPressCount <= 19) {
            Event_t event;
            event.EventType = 1; // Button pressed event type
            event.X = 0; // Additional information (meaning depends on event type)
            event.Y = 0; // Additional information (meaning depends on event type)
            event.Z = 0; // Additional information (meaning depends on event type)
            EventQueue_Put(&event);
        }
        buttonWakeUpPressCount = 0;
    }
    Gpio_Get(GPIO_ID_BUTTON_USER0, &buttonState);
    if(buttonState) {
        buttonUser0PressCount++;
    } else {
        if(buttonUser0PressCount >= 2 && buttonUser0PressCount <= 19) {
            Event_t event;
            event.EventType = 1; // Button pressed event type
            event.X = 0; // Additional information (meaning depends on event type)
            event.Y = 0; // Additional information (meaning depends on event type)
            event.Z = 0; // Additional information (meaning depends on event type)
            EventQueue_Put(&event);
        }
        buttonUser0PressCount = 0;
    }
    Gpio_Get(GPIO_ID_BUTTON_USER1, &buttonState);
    if(buttonState) {
        buttonUser1PressCount++;
    } else {
        if(buttonUser1PressCount >= 2 && buttonUser1PressCount <= 19) {
            Event_t event;
            event.EventType = 1; // Button pressed event type
            event.X = 1; // Additional information (meaning depends on event type)
            event.Y = 0; // Additional information (meaning depends on event type)
            event.Z = 0; // Additional information (meaning depends on event type)
            EventQueue_Put(&event);
        }
        buttonUser1PressCount = 0;
    }
}

int Key_Initialize(void){
    buttonWakeUpPressCount = 0;
    buttonUser0PressCount = 0;
    buttonUser1PressCount = 0;

    Gpio_Initialize(GPIO_ID_BUTTON_WAKE_UP, GPIO_MODE_INPUT, false);
    Gpio_Initialize(GPIO_ID_BUTTON_USER0, GPIO_MODE_INPUT, false);
    Gpio_Initialize(GPIO_ID_BUTTON_USER1, GPIO_MODE_INPUT, false);

	Timer_Callback_t myCallbackVar = *CheckCallback;
	Timer_Initialize(TIMER_ID_TIM6);
	Timer_Enable(TIMER_ID_TIM6, myCallbackVar, 50, TIME_UNIT_MS, true);

    return 0;
}