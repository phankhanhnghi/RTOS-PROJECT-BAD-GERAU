#include "fsm_smart_irrigation.h"
#include "main.h"  // Include main header to access GPIO functions and constants
// Define states for the FSM
typedef enum {
    STATE_IDLE,
    STATE_VALVE1_ON,
    STATE_VALVE2_ON,
    STATE_VALVE3_ON,
    STATE_PUMP1_ON,
    STATE_PUMP2_ON,
    STATE_PUMP2_OFF,
} FSM_State;
FSM_State current_state;

void fsm_irrigation_init() {
    // Ensure all LEDs are off at the start
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_SET);

    current_state = STATE_VALVE1_ON;
    setTimer(0, 100); // Initial short delay
}

void fsm_irrigation_run() {
    if (isTimerExpired(0)) {
        switch (current_state) {
            case STATE_VALVE1_ON:
                // Turn on Valve 1 LED (Red) and move to the next state after 5 seconds
                HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
                current_state = STATE_VALVE2_ON;
                setTimer(0, 5000); // 5 seconds
                break;

            case STATE_VALVE2_ON:
                // Turn off Valve 1 LED (Red), turn on Valve 2 LED (Yellow) and move to the next state after 5 seconds
                HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
                current_state = STATE_VALVE3_ON;
                setTimer(0, 5000); // 5 seconds
                break;

            case STATE_VALVE3_ON:
                // Turn off Valve 2 LED (Yellow), turn on Valve 3 LED (Blue) and move to the next state after 5 seconds
                HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
                current_state = STATE_PUMP1_ON;
                setTimer(0, 5000); // 5 seconds
                break;

            case STATE_PUMP1_ON:
                // Turn off Valve 3 LED (Blue), turn on Pump 1 LED (Green) and move to the next state after 10 seconds
                HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
                current_state = STATE_PUMP2_ON;
                setTimer(0, 10000); // 10 seconds
                break;

            case STATE_PUMP2_ON:
                // Turn off Pump 1 LED (Green), turn on Pump 2 LED (Orange) and move to the next state after 30 seconds
                HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
                current_state = STATE_PUMP2_OFF;
                setTimer(0, 30000); // 30 seconds
                break;

            case STATE_PUMP2_OFF:
                // Turn off Pump 2 LED (Orange) and move to the idle state with 60 seconds delay
                HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_SET);
                current_state = STATE_IDLE;
                setTimer(0, 60000); // 60 seconds delay before the next cycle
                break;

            case STATE_IDLE:
                // Ensure all LEDs are off and move to the initial state
                HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_SET);
                current_state = STATE_VALVE1_ON;
                setTimer(0, 5000); // 5 seconds to start the next cycle
                break;

            default:
                current_state = STATE_IDLE;
                break;
       }
    }
}
