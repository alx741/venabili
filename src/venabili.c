#include <stdlib.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.c"
#include "sensing.h"
#include "keyboard.h"
#include "usb_keys.h"

static usbd_device *usbd_dev;
uint8_t usbd_control_buffer[128];

int main(void)
{
	/* rcc_clock_setup_in_hsi_out_48mhz(); */
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
    usbd_dev = usb_init(usbd_control_buffer);
    keyboard_sensing_init();

	while (1)
    {
        /* int nk = sense_keys(); */

        /* if (keys_matrix[0][0]) */
        /* { */
        /*     report_key(usbd_dev, MOD_NONE, KEY_A); */
        /* } */
        /* if (keys_matrix[1][1]) */
        /* { */
        /*     report_key(usbd_dev, MOD_NONE, KEY_B); */
        /* } */
        /* else */
        /* { */
        /*     // Will only report the 6 out of 48 possible simultanious keys */
        /*     // Becouse of USB 6KRO limitation */
        /*     report_key(usbd_dev, MOD_NONE, KEY_NONE); */
        /* } */

        /* report_key(usbd_dev, MOD_NONE, KEY_A); */
        /* report_key(usbd_dev, MOD_NONE, KEY_NONE); */
        /* report_keypress(usbd_dev, MOD_NONE, KEY_A); */
        report_keypress(usbd_dev, MOD_LEFT_CTRL, KEY_A);

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
