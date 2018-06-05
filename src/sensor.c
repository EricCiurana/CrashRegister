/*
 * sensor.c
 *
 * Created: 11/05/2018 11:23:34
 *  Author: Eric
 */ 
#include "sensor.h"
#include "app.h"

/*
*
*	Esta tarea procesa los datos crudos del acelerómetro y los convierte
*	en algo practicable (construye un entero de 16b con el contenido de
*	dos registros de 8b) y los envía a la tarea app para procesarlos.
*
*/
void mysensortask(void *p)
{
	uint8_t i = 0;
	uint8_t status;
	uint8_t pdata;
	
	display_init(FOSC0*8);
	//display_init(configCPU_CLOCK_HZ);
	
	I2C_Init();
	
	/* Check that Proximity sensor is OK */
	I2C_readRegister(LSM9DS1_ACC_ADDRESS, 0x0F, &status);
	if (status != 104) {
		dip204_set_cursor_position(1,1);
		dip204_printf_string("Sensor error");
		while(1) {
			vTaskDelay(mainLCDTEST_PERIOD);
		}
		} else {
		dip204_set_cursor_position(1,1);
		dip204_printf_string("Sensor OK");
	}
	
	/* Enable Accelerometer mode */
	uint8_t accelSettings = 0b11011000;
	I2C_writeRegister(LSM9DS1_ACC_ADDRESS, CTRL_REG6_XL, accelSettings);

	
	uint8_t dataRead, dataH, dataL;
	ACCData accData;

	while(1)
	{
		I2C_readRegister(LSM9DS1_ACC_ADDRESS, ACCEL_SENSOR_X_h, &dataH );
		delay_ms(200);
		I2C_readRegister(LSM9DS1_ACC_ADDRESS, ACCEL_SENSOR_X_l, &dataL );
		accData.ejeX = dataH << 8 | dataL;

		//xQueueSend(sensor_data, &ejeX, 10 );
		
		I2C_readRegister(LSM9DS1_ACC_ADDRESS, ACCEL_SENSOR_Y_h, &dataH );
		delay_ms(200);
		I2C_readRegister(LSM9DS1_ACC_ADDRESS, ACCEL_SENSOR_Y_l, &dataL );
		accData.ejeY = dataH << 8 | dataL;

		//xQueueSend(sensor_data, &ejeY, 10 );

		I2C_readRegister(LSM9DS1_ACC_ADDRESS, ACCEL_SENSOR_Z_h, &dataH );
		delay_ms(200);
		I2C_readRegister(LSM9DS1_ACC_ADDRESS, ACCEL_SENSOR_Z_l, &dataL );
		accData.ejeZ = dataH << 8 | dataL;

		//xQueueSend(sensor_data, &ejeZ, 10 );
		xQueueSend(sensor_data, &accData, portMAX_DELAY);

		vTaskDelay(mainLCDTEST_PERIOD);
	}
}

