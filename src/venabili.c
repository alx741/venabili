#include <stdlib.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.h"
#include "usb_keys.h"
#include "usb_keyboard.h"
#include "sensing.h"

#include "keys.h"
#include "keyboard.h"

int main(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    usb_init();
    keyboard_sensing_init();
    keyboard_init();

    // FIXME: DEBUG ONLY
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	gpio_clear(GPIOB, GPIO13);

    Key layer0[NROWS][NCOLS] =
    {
        { k_a, k_caps                 },
        { k_c, HLshift(k_open_paren)  },
        { k_d, LS(1)                  },
        { k_A, HLshift(k_close_paren) },
    };

    Key layer1[NROWS][NCOLS] =
    {
        { MU(10), k_empty },
        { MD(5),  k_empty },
        { ML(15), k_empty },
        { MR(1),  k_empty },
    };


    add_layer(layer0);
    add_layer(layer1);


    while (1)
    {
    }
}

void sys_tick_handler(void)
{
    Key pressed_keys[NKEYS] = {0};

    sense_keys();
    select_layer();
    int n_pressed_keys = map_layer(pressed_keys);
    apply_modifiers(pressed_keys, n_pressed_keys);
    execute(pressed_keys, n_pressed_keys);
}

/* USB ISR handlers */
void usb_hp_can_tx_isr(void)
{
    usbd_poll(usbd_dev);
}
void usb_lp_can_rx0_isr(void)
{
    usbd_poll(usbd_dev);
}
