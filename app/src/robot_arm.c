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
#include "indicators.h"

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

os_task_t robotArmTask;

/** Motor objects */
motor_t arm_axes[ARM_AXIS_LAST];

/* ----------------------*
 * Function declarations *
 * ----------------------*
 */

os_task_return_codes_t robot_task_callback(os_event_t event);

/* ----------------------*
 * Function definitions  *
 * ----------------------*
 */

/**
 * Init the robot arm function
 */
void robot_arm_init(void) {
	uint8_t index;
	//Let the motor init create tasks for the axis
	for(index = 0; index < ARM_AXIS_LAST; index++){
		motor_init(&arm_axes[index], robot_arm_config[index].motor_id);
	}

	//Add the robot arm task
	robotArmTask.task_cb = &robot_task_callback;
	robotArmTask.task_name = "Robot arm task";
	os_add_task(robotArmTask);
	//Init the indicator led task
	indicators_init();
}

/**
 * The robot arm task. This task handles the incoming coordinates and controllers the motors
 * @param event
 * @return
 */
os_task_return_codes_t robot_task_callback(os_event_t event) {
	os_msg_t msg;

	switch (event) {
	case os_event_init:

		break;

	case os_event_msg_pending:
		//Retrieve message
		os_retrieve_msg(&msg);
		//Check if message is from a motor driver
		if(msg.os_msg_id == MOTOR_MSG_STOPPED_ID){
			//Check the motor nmbr
		}
		break;

	default:
		break;
	}
	return os_task_succeed; //Succeed
}

/**
 * Open all the motors and needed function
 */
void robot_arm_motor_open(void)
{

}
