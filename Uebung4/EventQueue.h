/******************************************************************************* 
Provides information about an event. 
*******************************************************************************/
typedef struct Event_s { 
    int32_t EventType; // The type of the event (e.g. Button pressed) 
    int32_t X; // Additional information (meaning depends on event type). 
    int32_t Y; // Additional information (meaning depends on event type). 
    int32_t Z; // Additional information (meaning depends on event type). 
} Event_t; 

/*******************************************************************************
Initializes the event queue module. 
Must be called exactly once before any other functions. 
returns: Zero on success, an error code otherwise. 
*******************************************************************************/ 
int EventQueue_Initialize(void);

/******************************************************************************* 
Adds an event to the event queue. 
event: A pointer to the event to add. 
returns: Zero on success, an error code otherwise. 
0: Success
1: Event queue is full; event not added to the queue. 
*******************************************************************************/
int EventQueue_Put(Event_t const * event);
 
/******************************************************************************* 
Gets an event from the event queue. 
event: A pointer to an event. 
returns: Zero on success, an error code otherwise. 
0: Success 
1: Event queue is empty 
*******************************************************************************/ 
int EventQueue_Get(Event_t * event);

/******************************************************************************* 
Clears the event queue. 
*******************************************************************************/
void EventQueue_Clear(void);