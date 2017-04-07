/* -----------------------------------------------------------------------------
 * robot_arm.cpp                                           (c) 2017 Rocks
 * -----------------------------------------------------------------------------
 * Author: Gertjan Rocks
 * Web:    www.gertjanrocks.com
 * Mail:   gertjanrocks@outlook.com
 * -----------------------------------------------------------------------------
 * Description: 
 * -----------------------------------------------------------------------------
 * Created on: 31 mrt. 2017
 * -----------------------------------------------------------------------------
 */


/* --------------*
 * Include files *
 * --------------*
 */

#include "robot_arm.h"
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

//static os_task_return_codes_t robot_arm_task_cb(os_event_t event);

//	Motor motor1(1,1);

/* ----------------------*
 * Function definitions  *
 * ----------------------*
 */

robot_arm::robot_arm(int channel){
	//Open all the motors
//	this->motor2 = new Motor(1,1);
}


/**
 * Task 2
 * @param event
 * @return
 */
os_task_return_codes_t robot_arm::robot_arm_task_cb(os_event_t event)
//os_task_return_codes_t robot_arm_task_cb(os_event_t event)
{
	os_msg_t msg;
	static os_timer_id_t timer = OS_MAXIMUM_TIMERS;

	switch (event) {
	case os_event_init:
		//Save task id
//		taskID_2 = os_current_task_id();
		//Log the task id
		os_log(os_log_level_all, "Task %d is initialized\n\r", os_current_task_id());
		//Subscribe for message pending
		os_subscribe_for_event(os_event_msg_pending, os_current_task_id());
		//Subscribe for timer event
		os_subscribe_for_event(os_event_timer, os_current_task_id());
		//Create timer for 1 seconds = 1000 milliseconds
		timer = os_timer_add(1000, os_timer_one_shot);
		break;

	case os_event_msg_pending:
		//Retrieve message
		os_retrieve_msg(&msg);
		os_log(os_log_level_all, "Pending message = %d, %d\n\r", msg.os_msg_id, msg.data);
//		if((msg.os_msg_id == taskID_1) && (msg.data == 0x55)){
			// Start the timer
			os_timer_start(timer);
//		}
		break;

	case os_event_timer:
//		os_log(os_log_level_all, "Timer send message from %d to %d\n\r",os_current_task_id(),taskID_3);
//		msg.os_msg_id = taskID_2;
		msg.data = 0xAA;
		//Post message to task3
//		os_post_msg(msg, taskID_3, os_msg_priority_normal);
		break;
	default:
		break;
	}
	return os_task_succeed; //Succeed
}
