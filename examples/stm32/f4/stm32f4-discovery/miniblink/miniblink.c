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

#include <libopencm3/stm32/pwr.h>

//#include <libopencm3/stm32/flash.h>


static void clock_setup(void)
{
  if(false) {

    // works - uses 50mA
    // hse is the external clock  - need to check its 8MHz
    rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
  } else if(false) {

    // works - uses 25mA 
    // ok 48mhz - ok - and uart appears to work ok - .
    rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_48MHZ]);
  } else if(true) {

    // works - uses 17mA 

    // Enable external high-speed oscillator - 8MHz.
    rcc_osc_on(RCC_HSE);
    rcc_wait_for_osc_ready(RCC_HSE);

    /* disable high performance mode */
    pwr_set_vos_scale(PWR_SCALE2);

    // Select HSE as SYSCLK source.
    rcc_set_sysclk_source(RCC_CFGR_SW_HSE);

    // needed?
    rcc_wait_for_sysclk_status(RCC_HSE);

	  // Set the peripheral clock frequencies used.
    rcc_ahb_frequency  = 8000000;
    rcc_apb1_frequency = 8000000;
    rcc_apb2_frequency = 8000000;

    // turn internal clock off
    rcc_osc_off(RCC_HSI);

    // 60 flashes - in 1 minute

/*  something about this code - and having the resistor that it doesn't like...
    rcc_osc_off(RCC_PLL);
    rcc_osc_off(RCC_LSE);
    rcc_osc_off(RCC_LSI);
    rcc_osc_off(RCC_PLLSAI);
    rcc_osc_off(RCC_PLLI2S);
*/
  }
}


static void gpio_setup(void)
{
	/* Using API functions: */
	// rcc_periph_clock_enable(RCC_GPIOE);

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOD);
	rcc_periph_clock_enable(RCC_GPIOE);
	rcc_periph_clock_enable(RCC_GPIOF);
	rcc_periph_clock_enable(RCC_GPIOG);

 
  // GPIO_MODE_ANALOG, Configure pin as analog function
  gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ALL);
  gpio_mode_setup(GPIOB, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ALL);
  gpio_mode_setup(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ALL);
  gpio_mode_setup(GPIOD, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ALL);
  gpio_mode_setup(GPIOE, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ALL);
  gpio_mode_setup(GPIOF, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ALL);
  gpio_mode_setup(GPIOG, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ALL);

  // gpio_mode_setup(GPIOE, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ALL);

  // change led for open-drain 
  gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_OTYPE_OD, GPIO0);
}




static char *my_hithere = "hithere";

int main(void)
{
	int i;
  volatile char *my_hithere2 = my_hithere;

  clock_setup();
	gpio_setup();

	/* Blink the LED (PC8) on the board. */
	while (1) {

		/* Using API function gpio_toggle(): */

		gpio_toggle(GPIOE, GPIO0);	/* LED on/off */
		for (i = 0; i < 1000000; i++) {	/* Wait a bit. */
			__asm__("nop");
		}
	}

	return (int) (void *)my_hithere2 ;
}
