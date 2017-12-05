#include <stdlib.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.c"
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

    int current_layer = 0;

    /* layers = */
    Key layers[NLAYERS][NROWS][NCOLS]=
    {

        // Layer 0
        {
            {k_a, k_A},
            {k_c, k_lctrl},
            {k_space, LS(1)},
            {k_hole, k_A},
        },

        // Layer 1
        {
            {LS(2), k_A},
            {k_c, k_a},
        },

        // Layer 2
        {
            {k_a, LS(3)},
            {k_c, k_hole},
        },

        // Layer 3
        {
            {k_a, k_A},
            {k_c, k_lctrl},
        },

    };


    while (1)
    {
        sense_keys();

        current_layer = get_layer_selection(0, layers);

        #ifdef DEBUG
        report_layer(current_layer);
        #endif

        uint8_t mods = get_modifiers(layers[current_layer]);
        infect_with_modifiers(mods, layers[current_layer]);
    }
}

void sys_tick_handler(void)
{
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
