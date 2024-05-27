#include "software_timer.h"

#define MAX_TIMERS 10 // Define the maximum number of timers

static int timer_counter[MAX_TIMERS];
static int timer_flag[MAX_TIMERS];

// Set the counter for software timer
void setTimer(int index, int value) {
    if (index < 0 || index >= MAX_TIMERS) return; // Check for valid index
    timer_counter[index] = value / 10;
    timer_flag[index] = 0;
}

// Check if timer is expired
int isTimerExpired(int index) {
    if (index < 0 || index >= MAX_TIMERS) return 0; // Check for valid index
    if (timer_flag[index] == 1) {
        timer_flag[index] = 0;
        return 1;
    }
    return 0;
}

// Function to be invoked in Timer_ISR
void timerRun() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (timer_counter[i] > 0) {
            timer_counter[i]--;
            if (timer_counter[i] <= 0) timer_flag[i] = 1;
        }
    }
}

// Function to initialize timers (optional but recommended)
void initTimers() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        timer_counter[i] = 0;
        timer_flag[i] = 0;
    }
}
