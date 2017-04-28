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
#include "gpio.h"

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
void motor_init(motor_t* motor, uint8_t id) {
	//Create a unique task for this motor
	motor->task.task_cb = &motor_task_cb;
	motor->task.task_name = "Motor task";
	//Save the pointer of the motor struct in the identifier field of the task
	motor->task.identifier = (uint32_t) motor;
	//Create the task
	os_add_task(motor->task);
	motor->id = id;
	motor->invert = false;
}

/**
 * The motor task is running to keep track of position / error
 * Each motor has its own task so the motor struct is retreived
 * @param event
 * @return
 */
os_task_return_codes_t motor_task_cb(os_event_t event) {
	os_msg_t msg;
	//Create a pointer to the motor object
	motor_t* _motor = 0;
	//Get the motor object
	os_get_task_identifier(os_current_task_id(), (uint32_t*) &_motor);

	switch (event) {
	case os_event_init:
		//Save task id
		_motor->task_id = os_current_task_id();
		//Log the task id
		os_log(os_log_level_all, "Motor %d with Task id %d is initialized\n\r",
				_motor->id, _motor->task_id);
		//Subscribe for timer event
		os_subscribe_for_event(os_event_timer, _motor->task_id);
		//Create a timer with a interval of 1000 millisecond to create timer id.
		_motor->timer = os_timer_add(1000, os_timer_one_shot);
		break;

	case os_event_timer:
		//Run timer has exceed so stop the motor
		motor_stop(_motor);
		//Inform parent task the motor has stopped
		msg.os_msg_id = MOTOR_MSG_STOPPED_ID;
		msg.data = _motor->id;
		//Send message
		os_post_msg(msg, _motor->parant_task, os_msg_priority_normal);
		break;

	default:
		break;
	}
	return os_task_succeed; //Succeed
}

/**
 * Opens a motor channel with a pwm channel, in1 and in2
 * The in1 and in2 are used for the direction the pwm channel for the speed
 * On the LN298
 * in1 -> in1
 * in2 -> in2
 * pwm -> enable
 * @param pwm_channel
 * @param in1_channel
 * @param in2_channel
 */
void motor_open(motor_t* motor, uint8_t pwm_channel, uint8_t in1_channel,
		uint8_t in2_channel) {

	//First save the values to the motor block
	motor->pwm_channel = pwm_channel;
	motor->in1_channel = in1_channel;
	motor->in2_channel = in2_channel;
	//Init the pwm with a default pwm frequency
	pwm_open(motor->pwm_channel, MOTOR_DEFAULT_PWM_FREQ);
	//Init the input 1 channel
	gpio_open(motor->in1_channel, GPIO_MODE_OUTPUT_PUSH_PULL);
	//Init the input 2 channel
	gpio_open(motor->in2_channel, GPIO_MODE_OUTPUT_PUSH_PULL);
	//Disable the motor
	motor_stop(motor);
}

/**
 * Stops a motor by disabling the outputs
 * @param motor
 */
void motor_stop(motor_t* motor) {
	//To stop the motor set both in channels to low
	gpio_set_pin(motor->in1_channel, false);
	gpio_set_pin(motor->in2_channel, false);
	//Set pwm dutycyle to 0
	pwm_change_dutyCyle(motor->pwm_channel, 0);
	//Motor is not running anymore
	motor->running = false;
}

/**
 * A simple run starts the motor with a given dutycyle and will run the motor
 * until the stop has been given.
 * @param motor
 * @param direction
 * @param dutycyle 0 - 1000
 */
void motor_simple_run(motor_t* motor, motor_direction_t direction,
		uint16_t dutycyle) {
	//First set the in pins to set the direction
	if ((direction == MOTOR_DIRECTION_CW) && (!motor->invert)) {
		//CW & !invert = in1 high and in2 low
		gpio_set_pin(motor->in1_channel, true);
		gpio_set_pin(motor->in1_channel, false);
	} else if ((direction == MOTOR_DIRECTION_CW) && (motor->invert)) {
		//CW & invert = in1 low and in2 high
		gpio_set_pin(motor->in1_channel, false);
		gpio_set_pin(motor->in1_channel, true);
	} else if ((direction == MOTOR_DIRECTION_CCW) && (!motor->invert)) {
		//CCW & !invert = in1 low and in2 high
		gpio_set_pin(motor->in1_channel, false);
		gpio_set_pin(motor->in1_channel, true);
	} else if ((direction == MOTOR_DIRECTION_CCW) && (motor->invert)) {
		//CCW & invert = in1 high and in2 low
		gpio_set_pin(motor->in1_channel, true);
		gpio_set_pin(motor->in1_channel, false);
	}
	//After the direction set the dutycyle
	pwm_change_dutyCyle(motor->pwm_channel, dutycyle);
	//Motor is running
	motor->running = true;
}

/**
 * Start the motor with a dutycyle and direction for a given time.
 * The motor will stop automatically and send a message to the given task
 * @param motor
 * @param direction
 * @param dutycyle  0 - 1000
 * @param run_time in ms
 * @param task_id
 */
void motor_run_time(motor_t* motor, motor_direction_t direction,
		uint16_t dutycyle, uint16_t run_time, os_task_id_t task_id) {
	//First set the in pins to set the direction
	if ((direction == MOTOR_DIRECTION_CW) && (!motor->invert)) {
		//CW & !invert = in1 high and in2 low
		gpio_set_pin(motor->in1_channel, true);
		gpio_set_pin(motor->in1_channel, false);
	} else if ((direction == MOTOR_DIRECTION_CW) && (motor->invert)) {
		//CW & invert = in1 low and in2 high
		gpio_set_pin(motor->in1_channel, false);
		gpio_set_pin(motor->in1_channel, true);
	} else if ((direction == MOTOR_DIRECTION_CCW) && (!motor->invert)) {
		//CCW & !invert = in1 low and in2 high
		gpio_set_pin(motor->in1_channel, false);
		gpio_set_pin(motor->in1_channel, true);
	} else if ((direction == MOTOR_DIRECTION_CCW) && (motor->invert)) {
		//CCW & invert = in1 high and in2 low
		gpio_set_pin(motor->in1_channel, true);
		gpio_set_pin(motor->in1_channel, false);
	}
	//After the direction set the dutycyle
	pwm_change_dutyCyle(motor->pwm_channel, dutycyle);
	//Motor is running
	motor->running = true;
	//Save task to inform motor stopped
	motor->parant_task = task_id;
	//Setup the timer for stopping the motor
	os_timer_new_value(motor->timer, run_time);
	//Start the timer
	os_timer_start(motor->timer);
}

/**
 * enable of disable the motor invert
 * @param motor
 * @param inverted
 */
void motor_invert(motor_t* motor, bool inverted) {
	motor->invert = inverted;
}

/**
 * set the frequency for the motor
 * @param motor
 * @param frequency
 */
void motor_set_pwmfreq(motor_t* motor, uint16_t frequency) {
	pwm_change_frequency(motor->pwm_channel, frequency);
}

/**
 *  return the status of the motor running
 * @param motor
 * @return
 */
bool motor_get_running(motor_t* motor) {
	return motor->running;
}
