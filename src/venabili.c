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

#define NLAYERS 3

#define LAYER0  0
#define LAYER1  1
#define LAYER2  2

#define CMD_NONE           0x0000
#define CMD_MOUSE_CLICK_1  0x0001
// ...
// #define  CMD_something  0x00FF

// Use the LS(n) macro for Layer Selection
#define _LS_FIRST 0x0100
#define _LS_LAST  0xFF00

/* Layer Selection
 *
 * LS(0) is the first (main) layer
 *
 * Up to 64 layers (0 - 63)
 */
#define LS(n) {KEY_NONE, MOD_NONE, _LS_FIRST + n}


typedef struct
{
    uint8_t usb_keycode;
    uint8_t modifiers;
    uint16_t command;
} Key;


const Key k_hole = {KEY_NONE, MOD_NONE, CMD_NONE};
const Key k_a = {KEY_A, MOD_NONE, CMD_NONE};
const Key k_A = {KEY_A, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_c = {KEY_C, MOD_NONE, CMD_NONE};
const Key k_at = {KEY_2, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_space = {KEY_SPACEBAR, MOD_NONE, CMD_NONE};
const Key k_lctrl = {KEY_NONE, MOD_LEFT_CTRL, CMD_NONE};
const Key k_rshift = {KEY_NONE, MOD_RIGHT_SHIFT, CMD_NONE};

bool isNormalKey(Key k)
{
    return (k.usb_keycode != KEY_NONE || k.modifiers != MOD_NONE)
            && k.command == CMD_NONE;
}

bool isCommandKey(Key k)
{
    return !isNormalKey(k);
}

bool isLayerSelectionKey(Key k)
{
    return isCommandKey(k) && (k.command & 0xFF00);
}

bool isHoleKey(Key k)
{
    return k.usb_keycode == KEY_NONE
        && k.modifiers == MOD_NONE
        && k.command == CMD_NONE;
}

void execute(Key k)
{
    if (isNormalKey(k))
    {
        report_keypress(usbd_dev, k.modifiers, k.usb_keycode);
    }
}


/* Should be given the default layer or the currently toggled layer
 *
 * Returns the selected layer number
 */
int detect_layer_selection(uint16_t current_layer, Key layers[NLAYERS][NROWS][NCOLS])
{
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            Key k = layers[current_layer][i][j];
            if (isLayerSelectionKey(k) && pressed(keys_matrix, i, j))
            {
                return detect_layer_selection(k.command - 0x00FF - 1, layers);
            }
        }
    }

    // If no layer selection key is pressed, the layer remains the same
    return current_layer;
}

int main(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    usbd_dev = usb_init(usbd_control_buffer);
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
            {k_c, k_lctrl},
        },

        // Layer 2
        {
            {k_a, k_A},
            {k_c, k_lctrl},
        },

    };


    while (1)
    {
        sense_keys();

        current_layer = detect_layer_selection(0, layers);

        if (current_layer == 0)
        {
            report_keypress(usbd_dev, MOD_NONE, KEY_0);
        }
        else if (current_layer == 1)
        {
            report_keypress(usbd_dev, MOD_NONE, KEY_1);
        }
        else if (current_layer == 2)
        {
            report_keypress(usbd_dev, MOD_NONE, KEY_2);
        }









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
