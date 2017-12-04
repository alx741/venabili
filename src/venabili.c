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

/* bool layers[NLAYERS][NROWS][NCOLS] = {false}; */

/* int current_layer = LAYER0; */

typedef enum _Action_type {KEY_PRESS, LAYER_SELECTION, MACRO, MOUSE_CLICK, MOUSE_MOVEMENT} Action_type;

typedef struct
{
    uint8_t keycode;
    uint8_t modifiers;
} Key_press;

typedef struct
{
    uint8_t button;
} Mouse_click;

typedef struct
{
    uint8_t axis;
    uint8_t speed;
} Mouse_movement;

typedef struct
{
    uint8_t layer;
} Layer_selection;

typedef struct
{
    Action_type action_type;
    union
    {
        Key_press        key_press;
        Layer_selection  layer_selection;
        Mouse_click      mouse_click;
        Mouse_movement   mouse_movement;
    } action;
} Key_action;


const Mouse_click mc_1 = {0x01};
const Mouse_movement mm_x = {0x01, 0x10};
const Mouse_movement mm_y = {0x02, 0x10};
const Mouse_movement mm_z = {0x03, 0x10};

const Layer_selection ls_0 = {0};
const Layer_selection ls_1 = {1};

const Key_press k_a = {KEY_A, MOD_NONE};
const Key_press k_A = {KEY_A, MOD_LEFT_SHIFT};
const Key_press k_at = {KEY_2, MOD_LEFT_SHIFT};
const Key_press k_3 = {KEY_3, MOD_NONE};
/* K_AT.modifiers |= MOD_RIGHT_CTRL; */

void execute(Key_action ka)
{
    switch (ka.action_type)
    {
        case KEY_PRESS:
            report_keypress(usbd_dev, ka.action.key_press.modifiers, ka.action.key_press.keycode);
            break;

        default:
            /* keypress(KEY_O); */
            break;
    }
}


int main(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    usbd_dev = usb_init(usbd_control_buffer);
    keyboard_sensing_init();

    /* Key_action layers[1][NROWS][NCOLS] = */
    Key_action layers[1][2][2] =
    {
        {
            { {KEY_PRESS, {k_a}}, {KEY_PRESS, {k_A}}, },
            { {KEY_PRESS, {k_at}}, {KEY_PRESS, {k_3}}, },
        },
    };

    while (1)
    {
        sense_keys();

        if (pressed(A1))
        {
            execute(layers[0][0][0]);
        }
        else if (pressed(A2))
        {
            execute(layers[0][0][1]);
        }
        else if (pressed(B1))
        {
            execute(layers[0][1][0]);
        }
        else if (pressed(B2))
        {
            execute(layers[0][1][1]);
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
void usb_hp_can_tx_isr(void)
{
    usbd_poll(usbd_dev);
}
void usb_lp_can_rx0_isr(void)
{
    usbd_poll(usbd_dev);
}
