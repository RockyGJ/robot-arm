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
#include "pwm.h"

/* -------------------------------*
 * Constant and macro definitions *
 * -------------------------------*
 */

#define MOTOR_DEFAULT_PWM_FREQ		(1000)
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

/**
 * Create a motor task and save the id
 * @param motor
 * @param id
 */
void motor_init(motor_t* motor, uint8_t id)
{
	//Create a unique task for this motor
	motor->task.task_cb = &motor_task_cb;
	motor->task.task_name = "Motor task";
	//Save the pointer of the motor struct in the identifier field of the task
	motor->task.identifier = (uint32_t)motor;
	//Create the task
	os_add_task(motor->task);
	motor->id = id;
}

/**
 * The motor task is running to keep track of position / error
 * Each motor has its own task so the motor struct is retreived
 * @param event
 * @return
 */
os_task_return_codes_t motor_task_cb(os_event_t event) {
	//Create a pointer to the motor object
	motor_t* _motor = 0;
	//Get the motor object
	os_get_task_identifier(os_current_task_id(),(uint32_t*)_motor);

	switch (event) {
	case os_event_init:
		//Save task id
		_motor->task_id = os_current_task_id();
		//Log the task id
		os_log(os_log_level_all, "Motor %d with Task id %d is initialized\n\r", _motor->id, _motor->task_id);
		//Subscribe for timer event
		os_subscribe_for_event(os_event_timer,_motor->task_id);
		//Create a timer with a interval of 1000 milisecond to create timer id.
		_motor->timer = os_timer_add(1000, os_timer_one_shot);
		break;

	case os_event_timer:

		break;

	default:
		break;
	}
	return os_task_succeed; //Succeed
}

/**
 * Opens a motor channel with a direction and enable
 * The pins and channels are described in the device_config in the hal
 * @param pwm_channel
 * @param dir
 * @param enable
 */
void motor_open(motor_t* motor, uint8_t pwm_channel, uint8_t dir_channel, uint8_t enable_channel){

	//First save the values to the motor block
	motor->pwm_channel = pwm_channel;
	motor->dir_channel = dir_channel;
	motor->enable_channel = enable_channel;
	//Init the pwm with a default pwm frequency
	pwm_open(motor->pwm_channel, MOTOR_DEFAULT_PWM_FREQ);
}
