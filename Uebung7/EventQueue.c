#include "EventQueue.h"
#include <stddef.h>
#include <stm32f072xb.h>

static Event_t queue[MAX_EVENT_QUEUE_SIZE];
static int head = 0;   // where the next event is read
static int tail = 0;   // where the next event is written
static int count = 0;  // how many events are inside

int EventQueue_Initialize(void) {
    head = 0;
    tail = 0;
    count = 0;
    return 0; // success
}

int EventQueue_Put(Event_t const * event){
    if (event == NULL) {
        return 1;
    }

    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    int result = 0;
    if (count >= MAX_EVENT_QUEUE_SIZE) {
        result = 1; // queue is full
    } else {
        queue[tail] = *event;
        tail = (tail + 1) % MAX_EVENT_QUEUE_SIZE;
        count++;
    }

    __set_PRIMASK(primask);
    return result;
}

int EventQueue_Get(Event_t * event){
    if (event == NULL) {
        return 1;
    }

    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    int result = 0;
    if (count <= 0) {
        result = 1; // queue is empty
    } else {
        *event = queue[head];
        head = (head + 1) % MAX_EVENT_QUEUE_SIZE;
        count--;
    }

    __set_PRIMASK(primask);
    return result;
}

void EventQueue_Clear(void) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    head = 0;
    tail = 0;
    count = 0;

    __set_PRIMASK(primask);
}