/*
 * display.h
 *
 * Created: 11/05/2018 11:22:10
 *  Author: Eric
 */ 

#include "common.h"

#ifndef DISPLAY_H_
#define DISPLAY_H_


void display_init(U32 fcpu_hz);
void printarDades(int16_t ejeX, int16_t ejeY, int16_t ejeZ, int16_t maxX, int16_t maxY, int16_t maxZ);


void mydisplaytask(U32 fcpu_hz);//,int16_t ejeX, int16_t ejeY, int16_t ejeZ, int16_t maxX, int16_t maxY, int16_t maxZ);


#endif /* DISPLAY_H_ */