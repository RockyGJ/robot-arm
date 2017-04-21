/* -----------------------------------------------------------------------------
 * motor.c                                           (c) 2017 Rocks
 * -----------------------------------------------------------------------------
 * Author: Gertjan Rocks
 * Web:    www.gertjanrocks.com
 * Mail:   gertjanrocks@outlook.com
 * -----------------------------------------------------------------------------
 * Description: Motor driver is created to use with the LN298 driver
 * -----------------------------------------------------------------------------
 * Created on: 18 apr. 2017
 * -----------------------------------------------------------------------------
 */


#ifndef INC_MOTOR_C_
#define INC_MOTOR_C_

#ifdef __cplusplus
extern "C" {
#endif

/* --------------*
 * Include files *
 * --------------*
 */

#include "os.h"

/* -------------------------------*
 * Constant and macro definitions *
 * -------------------------------*
 */

#define MOTOR_MSG_STOPPED_ID	(0x200)

/* -----------------*
 * Type definitions *
 * -----------------*
 */

/**
 * The motor struct is private and should only be changed by the motor
 * block itself. Each motor needs its own motor block
 */
typedef struct{
	uint8_t 		id;
	/* Os settings */
	os_task_t		task;
	os_task_id_t	task_id;
	os_timer_id_t	timer;
	/* HAL settings */
	uint8_t pwm_channel;
	uint8_t in1_channel;
	uint8_t in2_channel;
	/* Motor settings */
	bool invert;
	bool running;
	os_task_id_t 	parant_task;
}motor_t;

/**
 * Motor direction
 */
typedef enum{
	MOTOR_DIRECTION_CW,//!< MOTOR_DIRECTION_CW
	MOTOR_DIRECTION_CCW//!< MOTOR_DIRECTION_CCW
}motor_direction_t;

/* ---------------------*
 * File-scope variables *
 * ---------------------*
 */


/* ----------------------*
 * Function declarations *
 * ----------------------*
 */

/**
 * Create a motor task and save the id
 * @param motor
 * @param id
 */
void motor_init(motor_t* motor, uint8_t id);

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
void motor_open(motor_t* motor, uint8_t pwm_channel, uint8_t in1_channel, uint8_t in2_channel);

/**
 * Stops a motor by disabling the outputs
 * @param motor
 */
void motor_stop(motor_t* motor);

/**
 * A simple run starts the motor with a given dutycyle and will run the motor
 * until the stop has been given.
 * @param motor
 * @param direction
 * @param dutycyle 0 - 1000
 */
void motor_simple_run(motor_t* motor, motor_direction_t direction, uint16_t dutycyle);

/**
 * Start the motor with a dutycyle and direction for a given time.
 * The motor will stop automatically and send a message to the given task
 * @param motor
 * @param direction
 * @param dutycyle  0 - 1000
 * @param run_time in ms
 * @param task_id
 */
void motor_run_time(motor_t* motor, motor_direction_t direction, uint16_t dutycyle, uint16_t run_time, os_task_id_t task_id);

/**
 * enable of disable the motor invert
 * @param motor
 * @param inverted
 */
void motor_invert(motor_t* motor, bool inverted);

/**
 * set the frequency for the motor
 * @param motor
 * @param frequency
 */
void motor_set_pwmfreq(motor_t* motor, uint16_t frequency);

/**
 *  return the status of the motor running
 * @param motor
 * @return
 */
bool motor_get_running(motor_t* motor);

#ifdef __cplusplus
}
#endif

#endif /* INC_MOTOR_C_ */
