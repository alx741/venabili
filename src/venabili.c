#include <stdlib.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.c"
#include "sensing.h"
#include "keyboard.h"
#include "keys.h"

static usbd_device *usbd_dev;
uint8_t usbd_control_buffer[128];

int main(void)
{
	/* rcc_clock_setup_in_hsi_out_48mhz(); */
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
    usbd_dev = usb_init(usbd_control_buffer);

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

    // PORTA as matrix inputs
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO_ALL);

    // PORTB (0-3) as matrix outputs
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO0 | GPIO1 | GPIO2 | GPIO3);
	gpio_clear(GPIOB, GPIO0 | GPIO1 | GPIO2 | GPIO3);

	/* gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO12); */
	/* gpio_clear(GPIOB, GPIO12); */

	while (1)
    {
        gpio_set(GPIOB, GPIO1);
        /* gpio_set(GPIOB, GPIO1); */

        if (gpio_get(GPIOA, GPIO0))
        {
            gpio_set(GPIOB, GPIO0);
            report_key(usbd_dev, MOD_LEFT_SHIFT, KEY_A);
        }
        else
        {
            report_key(usbd_dev, MOD_NONE, KEY_NONE);
        }
    }
}

void sys_tick_handler(void)
{
    /* int n = sense_keys(); */
    /* if (pressed_keys[0] == A2) */
    /* { */
    /*     gpio_set(GPIOB, GPIO11); */
    /* } */
    /* if (n == 1) */
    /* { */
    /*     gpio_set(GPIOB, GPIO12); */
    /* } */


    /* if (gpio_get(GPIOA, GPIO0)) */
    /* { */
    /*     gpio_set(GPIOB, GPIO1); */
    /* } */



    /* static int x = 0; */

    /* if (x == 0) */
    /* { */
    /*     x = 1; */
    /*     report_key(usbd_dev, MOD_LEFT_SHIFT, KEY_A); */
    /* } */
    /* else */
    /* { */
    /*     x = 0; */
    /*     report_key(usbd_dev, MOD_NONE, KEY_NONE); */
    /* } */
}

/* USB ISR handlers */
void usb_hp_can_tx_isr(void) { usbd_poll(usbd_dev); }
void usb_lp_can_rx0_isr(void) { usbd_poll(usbd_dev); }
