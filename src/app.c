/*
 * app.c
 *
 * Created: 11/05/2018 11:37:59
 *  Author: Eric
 */ 

#include "app.h"
#include "common.h"
#include "display.h"

/*
*
*	Esta tarea recibe los datos de los ejes X,Y,Z del sensor,
*	los procesa y envía el output a la tarea display
*
*/
void myapptask()
{
	int16_t l_maxX, l_maxY, l_maxZ;
	int16_t tempX, tempY;
	
	ACCData accData;
	ACCData accData2;
	
	l_maxX = 0;
	l_maxY = 0;
	l_maxZ = 0;
	
	while(1)
	{
		xQueueReceive(sensor_data, &accData, portMAX_DELAY);
		
		tempX = abs(accData.ejeX);
		tempY= abs(l_maxX);
		if (tempY < tempX)
		{
			l_maxX = accData.ejeX;
			accData2.maxX = l_maxX;
		}
		accData2.ejeX = accData.ejeX;

		tempX = abs(accData.ejeY);
		tempY = abs(l_maxY);
		if (tempY < tempX)
		{
			l_maxY = accData.ejeY;
			accData2.maxY = accData.ejeY;
		}
		accData2.ejeY = accData.ejeY;

		tempX = abs(accData.ejeZ);
		tempY= abs(l_maxZ);
		if (tempY < tempX)
		{
			l_maxZ = accData.ejeZ;
			accData2.maxZ = accData.ejeZ;
		}
		accData2.ejeZ = accData.ejeZ;

		xQueueSend(display_data, &accData2, portMAX_DELAY );
	}
}