/* -----------------------------------------------------------------------------
 * motor.c                                           (c) 2017 Rocks
 * -----------------------------------------------------------------------------
 * Author: Gertjan Rocks
 * Web:    www.gertjanrocks.com
 * Mail:   gertjanrocks@outlook.com
 * -----------------------------------------------------------------------------
 * Description: 
 * -----------------------------------------------------------------------------
 * Created on: 18 apr. 2017
 * -----------------------------------------------------------------------------
 */

/* --------------*
 * Include files *
 * --------------*
 */

#include "os.h"
#include "gpio.h"
#include "indicators.h"

/* -------------------------------*
 * Constant and macro definitions *
 * -------------------------------*
 */


/* -----------------*
 * Type definitions *
 * -----------------*
 */

#define HEARTBEAT_LED_B			(7)
#define HEARTBEAT_LED_G			(8)
#define HEARTBEAT_LED_INTERVAL	(500)


/* ---------------------*
 * File-scope variables *
 * ---------------------*
 */

/* ----------------------*
 * Function declarations *
 * ----------------------*
 */
os_task_t indicator_task;
os_task_return_codes_t indicator_cb(os_event_t event);

/* ----------------------*
 * Function definitions  *
 * ----------------------*
 */

/**
 * Create an indicator task
 */
void indicators_init(void){
	//Create a indicator task
	indicator_task.task_cb = &indicator_cb;
	indicator_task.task_name = "Indicator task";
	//Create the task
	os_add_task(indicator_task);
}


os_task_return_codes_t indicator_cb(os_event_t event) {
	static bool led_state = false;
	os_timer_id_t timer;
	switch (event) {
	case os_event_init:
		//Init hart-beat leds
		gpio_open(HEARTBEAT_LED_G, GPIO_MODE_OUTPUT_PUSH_PULL);
		gpio_open(HEARTBEAT_LED_B, GPIO_MODE_OUTPUT_PUSH_PULL);
		//Subscribe for timer event
		os_subscribe_for_event(os_event_timer, os_current_task_id());
		//Create a timer with a interval of HEARTBEAT_LED_INTERVAL millisecond to create timer id.
		timer = os_timer_add(HEARTBEAT_LED_INTERVAL, os_timer_repeat);
		//Start the timer
		os_timer_start(timer);
		break;

	case os_event_timer:
		//Set blue led
		gpio_set_pin(HEARTBEAT_LED_B, led_state);
		//Toggle led
		led_state = !led_state;
		//Set green led
		gpio_set_pin(HEARTBEAT_LED_G, led_state);
		break;

	default:
		break;
	}
	return os_task_succeed; //Succeed
}

