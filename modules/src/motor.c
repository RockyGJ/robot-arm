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

#include "motor.h"
#include "os.h"

/* -------------------------------*
 * Constant and macro definitions *
 * -------------------------------*
 */


/* -----------------*
 * Type definitions *
 * -----------------*
 */


/* ---------------------*
 * File-scope variables *
 * ---------------------*
 */


/* ----------------------*
 * Function declarations *
 * ----------------------*
 */
os_task_return_codes_t motor_task_cb(os_event_t event);


/* ----------------------*
 * Function definitions  *
 * ----------------------*
 */

void motor_init(motor_t* motor, uint8_t id)
{
	//Create a unique task for this motor
	motor->motor_task.task_cb = &motor_task_cb;
	motor->motor_task.task_name = "Motor task";
	//Save the pointer of the motor struct in the identifier field of the task
	motor->motor_task.identifier = (uint32_t)motor;
	//Create the task
	os_add_task(motor->motor_task);
	motor->motor_id = id;

}

/**
 * motor task
 * @param event
 * @return
 */
os_task_return_codes_t motor_task_cb(os_event_t event) {
	os_msg_t msg;
//	static os_timer_id_t timer;

	motor_t* _motor = 0;
	os_get_task_identifier(os_current_task_id(),(uint32_t*)_motor);
	_motor->motor_id;
	switch (event) {
	case os_event_init:
		//Save task id
//		taskID_1 = os_current_task_id();
		//Log the task id
		os_log(os_log_level_all, "Task %d is initialized\n\r", os_current_task_id());
		//Subscribe for timer event
		os_subscribe_for_event(os_event_timer, os_current_task_id());
		//Create timer for 10 seconds = 10000 milliseconds
//		timer = os_timer_add(10000, os_timer_repeat);
		// Start the timer
//		os_timer_start(timer);
		break;

	case os_event_timer:
//		os_log(os_log_level_all, "Timer send message from %d to %d\n\r",os_current_task_id(),taskID_2);
//		msg.os_msg_id = taskID_1;
//		msg.data = 0x55;
		//Post message to task2
//		os_post_msg(msg, taskID_2, os_msg_priority_normal);
		break;

	default:
		break;
	}
	return os_task_succeed; //Succeed
}
