/* -----------------------------------------------------------------------------
 * main.c                                           (c) 2017 Rocks
 * -----------------------------------------------------------------------------
 * Author: Gertjan Rocks
 * Web:    www.gertjanrocks.com
 * Mail:   gertjanrocks@outlook.com
 * -----------------------------------------------------------------------------
 * Description: main application for robot arm
 * -----------------------------------------------------------------------------
 * Created on: 7 apr. 2017
 * -----------------------------------------------------------------------------
 */

/* --------------*
 * Include files *
 * --------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include "os.h"
#include "hal.h"
#include "systick.h"
#include "needle_unit.h"

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

os_functions_pointers_t function_pointers;

/* ----------------------*
 * Function declarations *
 * ----------------------*
 */

void disable_interrupt(void);
void enable_interrupt(void);
void stdio_function(void);
void systick_callback(void);
/* ----------------------*
 * Function definitions  *
 * ----------------------*
 */

/**
 * Systick callback function
 */
void systick_callback(void) {
	os_timer_count();
}

/**
 * main function
 * @return
 */
int main(void) {

	//Add functions pointers necessary for interrupt
	function_pointers.disable_irq = &disable_interrupt;
	function_pointers.enable_irq = &enable_interrupt;
	function_pointers.stdio = &stdio_function;
	//Add structure to os
	os_add_function_pointers(&function_pointers);
	//Call init
	os_init();
	//Init the HAL
	hal_init();
	//Init the main application cq robot arm
	//The robot arm should call all the inits for the modules
	needle_unit_init();
	//Open the systick
	systick_open(os_timer_counter_step_setting(), &systick_callback);
	//Start os should never return
	os_main();

}

/**
 * Function to disable interupt
 */
void disable_interrupt(void) {

}

/**
 * Function to enable interrupt
 */
void enable_interrupt(void) {

}

/**
 * Function used to output stdio
 */
void stdio_function(void) {

}
