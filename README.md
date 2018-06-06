# CrashRegister
FreeRTOS, LSM9DS1 based crash register code.
This is the code of a uni project in which we were ask to create a prototype of using a dev board, 
a sensor of some kind and a RTOS, so using FreeRTOS, a LSM9DS1 (accelerometer) and the provided EVK1100 dev board,
we (my lab mate and I) created a crash register that displays both the current and max acceleration on the X, Y and Z axis.

In a real world scenario it would not display the data but log it and save it into a non volatile
memory, and it could be for instance used on the inside of a dummy to register local G-forces on 
crash tests.