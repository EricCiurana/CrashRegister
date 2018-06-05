/*
 * display.c
 *
 * Created: 11/05/2018 11:21:36
 *  Author: Eric
 */ 
#include "display.h"
//#include "common.h"



void display_init(U32 fcpu_hz)
{
	static const gpio_map_t DIP204_SPI_GPIO_MAP =
	{
		{DIP204_SPI_SCK_PIN,  DIP204_SPI_SCK_FUNCTION },  // SPI Clock.
		{DIP204_SPI_MISO_PIN, DIP204_SPI_MISO_FUNCTION},  // MISO.
		{DIP204_SPI_MOSI_PIN, DIP204_SPI_MOSI_FUNCTION},  // MOSI.
		{DIP204_SPI_NPCS_PIN, DIP204_SPI_NPCS_FUNCTION}   // Chip Select NPCS.
	};

	// add the spi options driver structure for the LCD DIP204
	spi_options_t spiOptions =
	{
		.reg          = DIP204_SPI_NPCS,
		.baudrate     = 1000000,
		.bits         = 8,
		.spck_delay   = 0,
		.trans_delay  = 0,
		.stay_act     = 1,
		.spi_mode     = 0,
		.modfdis      = 1
	};

	// Assign I/Os to SPI
	gpio_enable_module(DIP204_SPI_GPIO_MAP,
	sizeof(DIP204_SPI_GPIO_MAP) / sizeof(DIP204_SPI_GPIO_MAP[0]));

	// Initialize as master
	spi_initMaster(DIP204_SPI, &spiOptions);

	// Set selection mode: variable_ps, pcs_decode, delay
	spi_selectionMode(DIP204_SPI, 0, 0, 0);

	// Enable SPI
	spi_enable(DIP204_SPI);

	// setup chip registers
	spi_setupChipReg(DIP204_SPI, &spiOptions, fcpu_hz);

	// initialize LCD
	dip204_init(backlight_PWM, true);

	dip204_hide_cursor();
}



void printarDades(int16_t ejeX, int16_t ejeY, int16_t ejeZ, int16_t maxX, int16_t maxY, int16_t maxZ)
{
	dip204_set_cursor_position(1,1);
	dip204_printf_string("X: %.2fg ", ejeX/4096.0);	// Para 8G dividir entre 4096.0
	dip204_printf_string("mX: %.2fg ", maxX/4096.0);
	
	dip204_set_cursor_position(1,2);
	dip204_printf_string("Y: %.2fg ", ejeY/4096.0);	// Para 8G dividir entre 4096.0
	dip204_printf_string("mY: %.2fg ", maxY/4096.0);
	
	dip204_set_cursor_position(1,3);
	dip204_printf_string("Z: %.2fg ", ejeZ/4096.0);	// Para 8G dividir entre 4096.0
	dip204_printf_string("mZ: %.2fg ", maxZ/4096.0);
}


/*
*
*	Esta tarea recibe los datos del acelerómetro completamente
*	procesados y los imprime en el display mediante la función "printarDades"
*
*/
void mydisplaytask(U32 fcpu_hz)
{
	ACCData accData;
	while(1)
	{
		xQueueReceive(display_data, &accData, portMAX_DELAY);	
		printarDades(accData.ejeX, accData.ejeY, accData.ejeZ, accData.maxX, accData.maxY, accData.maxZ);
	}
}