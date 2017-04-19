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
	os_task_t	motor_task;
	uint8_t 	motor_id;
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
