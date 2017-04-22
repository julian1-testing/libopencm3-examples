/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

// #include <libopencm3/stm32/rcc.h>
// #include <libopencm3/stm32/gpio.h>

#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>


//#include <libopencm3/stm32/f1/rcc.h>
// #include <libopencm3/stm32/f1/gpio.h>

static void gpio_setup(void)
{
	/* Enable GPIOC clock. */
	/* Manually: */
	// RCC_AHB1ENR |= RCC_AHB1ENR_IOPDEN;
	/* Using API functions: */
	rcc_periph_clock_enable(RCC_GPIOE);

	/* Set GPIO1 (in GPIO port D) to 'output push-pull'. */
	/* Manually: */
	// GPIOC_CRH = (GPIO_CNF_OUTPUT_PUSHPULL << (((8 - 8) * 4) + 2));
	// GPIOC_CRH |= (GPIO_MODE_OUTPUT_2_MHZ << ((8 - 8) * 4));
	/* Using API functions: */
  // gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_OTYPE_OD, GPIO1);
  // gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);

  gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_OTYPE_OD, GPIO0);
  

}

static char *my_hithere = "hithere";

int main(void)
{
	int i;
  volatile char *my_hithere2 = my_hithere;

	gpio_setup();

	/* Blink the LED (PC8) on the board. */
	while (1) {
		/* Manually: */
		// GPIOC_BSRR = GPIO1;		/* LED off */
		// for (i = 0; i < 1000000; i++)	/* Wait a bit. */
		//	__asm__("nop");
		// GPIOC_BRR = GPIO1;		/* LED on */
		// for (i = 0; i < 1000000; i++)	/* Wait a bit. */
		//	__asm__("nop");

		/* Using API functions gpio_set()/gpio_clear(): */
		// gpio_set(GPIOC, GPIO1);	/* LED off */
		// for (i = 0; i < 1000000; i++)	/* Wait a bit. */
		//	__asm__("nop");
		// gpio_clear(GPIOC, GPIO1);	/* LED on */
		// for (i = 0; i < 1000000; i++)	/* Wait a bit. */
		//	__asm__("nop");

		/* Using API function gpio_toggle(): */

		gpio_toggle(GPIOE, GPIO0);	/* LED on/off */
		for (i = 0; i < 1000000; i++) {	/* Wait a bit. */
			__asm__("nop");
		}
	}

	return (int) (void *)my_hithere2 ;
}
