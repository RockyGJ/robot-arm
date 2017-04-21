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
#include "motor.h"

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

/** Motor objects */
motor_t arm_axis_1;
motor_t arm_axis_2;
motor_t arm_axis_3;
motor_t arm_axis_4;
motor_t arm_axis_5;
motor_t arm_axis_6;

/* ----------------------*
 * Function declarations *
 * ----------------------*
 */

/* ----------------------*
 * Function definitions  *
 * ----------------------*
 */

void robot_arm_init(void) {
	//Let the motor init create tasks for the axis
	motor_init(&arm_axis_1, 1);
	motor_init(&arm_axis_2, 2);
	motor_init(&arm_axis_3, 3);
	motor_init(&arm_axis_4, 4);
	motor_init(&arm_axis_5, 5);
	motor_init(&arm_axis_6, 6);
}

