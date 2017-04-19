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


/* -----------------*
 * Type definitions *
 * -----------------*
 */

typedef struct{
	uint8_t 		id;		//!Identifier
	/* Os settings */
	os_task_t		task;
	os_task_id_t	task_id;
	os_timer_id_t	timer;
	/* HAL settings */
	uint8_t pwm_channel;
	uint8_t dir_channel;
	uint8_t enable_channel;
}motor_t;

/* ---------------------*
 * File-scope variables *
 * ---------------------*
 */


/* ----------------------*
 * Function declarations *
 * ----------------------*
 */

void motor_init(motor_t* motor, uint8_t id);

#ifdef __cplusplus
}
#endif

#endif /* INC_MOTOR_C_ */
