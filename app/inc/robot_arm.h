/* -----------------------------------------------------------------------------
 * robot_arm.h                                           (c) 2017 Rocks
 * -----------------------------------------------------------------------------
 * Author: Gertjan Rocks
 * Web:    www.gertjanrocks.com
 * Mail:   gertjanrocks@outlook.com
 * -----------------------------------------------------------------------------
 * Description: 
 * -----------------------------------------------------------------------------
 * Created on: 7 apr. 2017
 * -----------------------------------------------------------------------------
 */

#ifndef ROBOT_ARM_H_
#define ROBOT_ARM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* --------------*
 * Include files *
 * --------------*
 */

#include "stdint.h"

/* -------------------------------*
 * Constant and macro definitions *
 * -------------------------------*
 */

enum{
	ARM_AXIS_1,
	ARM_AXIS_2,
	ARM_AXIS_3,
	ARM_AXIS_4,
	ARM_AXIS_5,
	ARM_AXIS_LAST
};

typedef struct{
	uint8_t motor_id;
	uint8_t pwm_channel;
	uint8_t in1_channel;
	uint8_t in2_channel;
}robot_arm_config_t;

/**
 * Default robot config
 */
static const robot_arm_config_t robot_arm_config[ARM_AXIS_LAST] = {
	/* 	AXES			motor_id,	pwm_channel,	in1_channel, 	in2_channel	*/
	/* ARM_AXIS_1 */{	1,			0,				5,				6	},
	/* ARM_AXIS_2 */{	2,			1,				9,				10	},
	/* ARM_AXIS_3 */{	3,			2,				4,				5	},
	/* ARM_AXIS_4 */{	4,			3,				6,				7	},
	/* ARM_AXIS_5 */{	5,			4,				8,				9	},
};

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

extern void robot_arm_init(void);

#ifdef __cplusplus
}
#endif

#endif /* ROBOT_ARM_H_ */
