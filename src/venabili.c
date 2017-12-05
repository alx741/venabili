#include <stdlib.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.c"
#include "sensing.h"
#include "usb_keyboard.h"
#include "usb_keys.h"

#include "keys.h"
#include "keyboard.c"

uint8_t usbd_control_buffer[128];


int main(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    usb_init(usbd_control_buffer);
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

/*         if (pressed(D1)) */
/*         { */
/*             current_layer = LAYER1; */

/*             if (pressed(A1)){ keypress(KEY_A); } */
/*             if (pressed(A2)){ keypress(KEY_B); } */
/*             if (pressed(B1)){ keypress(KEY_C); } */
/*             if (pressed(B2)){ keypress(KEY_D); } */
/*             if (pressed(C1)){ keypress(KEY_E); } */
/*             if (pressed(C2)){ keypress(KEY_F); } */
/*             //if (pressed(D1)){  } */
/*             if (pressed(D2)){ keypress(KEY_G); } */
/*         } */

/*         else if (pressed(D2)) */
/*         { */
/*             current_layer = LAYER2; */

/*             if (pressed(A1)){ keypress(KEY_H); } */
/*             if (pressed(A2)){ keypress(KEY_I); } */
/*             if (pressed(B1)){ keypress(KEY_J); } */
/*             if (pressed(B2)){ keypress(KEY_K); } */
/*             if (pressed(C1)){ keypress(KEY_L); } */
/*             /1* if (pressed(C2)){ keypress(KEY_M); } *1/ */

/*             if (tapped(C2)) { keypress(KEY_ENTER); } // TAP */

/*             if (pressed(C2)) */
/*             { */
/*                 if (pressed(A1)){ report_keypress(usbd_dev, MOD_LEFT_SHIFT, KEY_H); } */
/*                 // ... */
/*                 //if (pressed(C2)){ // SHIFT + M  } */
/*             } */

/*             //if (pressed(D2)){  } */
/*         } */

/*         else if (pressed(PD2) && !pressed(D2)) // Reset layer */
/*         { */
/*             current_layer = LAYER0; */
/*         } */

/*         // Layer 0 */
/*         else */
/*         { */
/*             if (pressed(A1)){ keypress(KEY_1); } */
/*             if (pressed(A2)){ keypress(KEY_2); } */
/*             if (pressed(B1)){ keypress(KEY_3); } */
/*             if (pressed(B2)){ keypress(KEY_4); } */
/*             if (pressed(C1)){ keypress(KEY_5); } */
/*             if (pressed(C2)){ keypress(KEY_6); } */

/*         } */


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
