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

#include "needle_unit.h"
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

static void robot_arm_motor_open(void);
static void robot_arm_test(void);

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
		//Subscribe to motor msg
		os_subscribe_for_event(os_event_msg_pending, os_current_task_id());
		//Open the necessery functions
		robot_arm_motor_open();
		motor_run_time(&arm_axes[ARM_AXIS_1],MOTOR_DIRECTION_CCW, 500, 200, os_current_task_id());
		break;

	case os_event_msg_pending:
		//Retrieve message
		os_retrieve_msg(&msg);
		//Check if message is from a motor driver
		if(msg.os_msg_id == MOTOR_MSG_STOPPED_ID){
			//Check the motor nmbr
			if(msg.data == robot_arm_config[ARM_AXIS_1].motor_id){
				robot_arm_test();
			}
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
	uint8_t index;
	//Set all the motor channels
	for(index = 0; index < ARM_AXIS_LAST; index++){
		motor_open(&arm_axes[index], robot_arm_config[index].pwm_channel,
									 robot_arm_config[index].in1_channel,
									 robot_arm_config[index].in2_channel);
	}
}

void robot_arm_test(void)
{
	static test_state = 0;

	switch(test_state){
	case 0:
		motor_run_time(&arm_axes[ARM_AXIS_1],MOTOR_DIRECTION_CCW, 900, 1000, os_current_task_id());
		motor_run_time(&arm_axes[ARM_AXIS_2],MOTOR_DIRECTION_CCW, 900, 1000, os_current_task_id());
		test_state++;
		break;
	case 1:
		motor_run_time(&arm_axes[ARM_AXIS_1],MOTOR_DIRECTION_CW, 900, 1000, os_current_task_id());
		motor_run_time(&arm_axes[ARM_AXIS_2],MOTOR_DIRECTION_CW, 900, 1000, os_current_task_id());
		test_state = 0;
		break;
	case 2:
		motor_run_time(&arm_axes[ARM_AXIS_1],MOTOR_DIRECTION_CCW, 250, 2000, os_current_task_id());
		test_state++;
		break;
	case 3:
		motor_run_time(&arm_axes[ARM_AXIS_1],MOTOR_DIRECTION_CCW, 500, 2000, os_current_task_id());
		test_state++;
		break;
	case 4:
		motor_run_time(&arm_axes[ARM_AXIS_1],MOTOR_DIRECTION_CCW, 750, 2000, os_current_task_id());
		test_state++;
		break;
	case 5:
		motor_run_time(&arm_axes[ARM_AXIS_1],MOTOR_DIRECTION_CCW, 1000, 2000, os_current_task_id());
		test_state = 0;
		break;
	}
}
