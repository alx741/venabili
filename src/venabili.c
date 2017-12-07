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

void report_layer(int);
void report_layer(layer)
{
    if (layer == 0)
    {
        report_keypress(MOD_NONE, KEY_0);
    }
    else if (layer == 1)
    {
        report_keypress(MOD_NONE, KEY_1);
    }
    else if (layer == 2)
    {
        report_keypress(MOD_NONE, KEY_2);
    }
    else if (layer == 3)
    {
        report_keypress(MOD_NONE, KEY_3);
    }
}

int main(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    usb_init();
    keyboard_sensing_init();

    Key layer0[NROWS][NCOLS] = 
        {
            {k_d, k_A},
            {k_a, k_lctrl},
            {k_space, LS(1)},
            {k_empty, k_rshift},
        };

    Key layer1[NROWS][NCOLS] = 
        {
            {LS(2), k_B},
            {k_empty, c_layer_lock},
        };

    Key layer2[NROWS][NCOLS] = 
        {
            {k_empty, LS(3)},
            {k_c, c_layer_lock},
        };

    Key layer3[NROWS][NCOLS] = 
        {
            {k_empty, k_empty},
            {k_d, k_D},
        };


    add_layer(layer0);
    add_layer(layer1);
    add_layer(layer2);
    add_layer(layer3);


    while (1)
    {
        Key pressed_keys[NKEYS] = {0};

        sense_keys();
        select_layer();
        map_layer(pressed_keys);
        apply_modifiers(pressed_keys);
        execute(pressed_keys);
        /* report_layer(current_layer); */
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
