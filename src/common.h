/*
 * definitions.h
 *
 * Created: 11/05/2018 11:23:17
 * Authors: Nuria Centellas & Eric Ciurana
			
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_


/* Environment include files. */
#include <stdlib.h>
#include <string.h>
#include <math.h>				// valor absolut per accelerometre
#include "power_clocks_lib.h"
#include "flashc.h"

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Demo file headers. */
#include "partest.h"
#include "ethernet.h"
#include "netif/etharp.h"
#include "flash.h"

/*** */
#include "dip204.h"
#include "intc.h"
#include "gpio.h"
#include "pm.h"
#include "delay.h"
#include "spi.h"
#include "conf_clock.h"

#include "myI2CLib.h"
/**** */

xQueueHandle sensor_data;
xQueueHandle display_data;

typedef struct {
	int16_t ejeX;
	int16_t ejeY;
	int16_t ejeZ;
	
	int16_t maxX;
	int16_t maxY;
	int16_t maxZ;
	}ACCData;


/* Priority definitions for most of the tasks in the demo application. */
#define mainLED_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )
#define mainETH_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )

#define mainLCDTEST_PERIOD          ( ( portTickType ) 100 / portTICK_RATE_MS  )


#endif /* DEFINITIONS_H_ */