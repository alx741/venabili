/*
 *  Copyright 2017 Daniel Campoverde C. <alx@sillybytes.net>
 *
 *  This file is part of Venabili.
 *
 *  Venabili is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Venabili is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Venabili.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdint.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>
#include "sensing.h"
#include "usb_keys.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "keys_internal.h"
#include "keys.h"
#include "macros.h"
#include "keyboard.h"

static Key LAYERS[NLAYERS][NROWS][NCOLS];
static int N_LAYERS = 0;
static int CURRENT_LAYER = 0;
static int CURRENT_LOCKED_LAYER = 0;
static bool LAYER_LOCKED = false;
static bool TAP_IS_TIMEDOUT = false;

void handle_6_normal_keys(Key k[6], int n);
void handle_command_keys(Key k);
void handle_mouse_movement(Key k);
void lock_layer(void);
void unlock_layer(void);
void reset_tap_timer(void);

// USB can handle up to 6KRO
#define XKRO  6

void execute(const Key keys[NKEYS], int n)
{
    Key normal_keys[XKRO] = {0};
    int n_normal_keys = 0;

    MouseButton mouse_btns[N_MOUSE_BTNS] = {0};
    int n_mouse_btns = 0;

    for (int i = 0; i < n; i++)
    {
        Key k = keys[i];

        if (isNormalKey(k))
        {
            if (n_normal_keys < XKRO)
            {
                normal_keys[n_normal_keys++] = k;
            }
        }
        else if (isMouseClickKey(k))
        {
            if (n_mouse_btns < N_MOUSE_BTNS)
            {
                mouse_btns[n_mouse_btns++] = getMouseClickButton(k);
            }
        }
        else if (isCommandKey(k))
        {
            handle_command_keys(k);
        }
    }

    handle_6_normal_keys(normal_keys, n_normal_keys);
    report_mouse_buttons(mouse_btns);
}

void handle_6_normal_keys(Key k[6], int n)
{
    uint8_t mods = 0;
    uint8_t keycodes[6] = {0};

    // Combine modifiers
    for (int i = 0; i < n; i++)
    {
        mods |= k[i].modifiers;
        keycodes[i] = k[i].usb_keycode;
    }
    report_6_keys(mods, keycodes);
}

void handle_command_keys(Key k)
{
    if (areKeysEqual(k, c_layer_lock))
    {
        // Togle layer locking
        if (LAYER_LOCKED) { unlock_layer(); }
        else { lock_layer(); }
    }

    else if (isMouseMovementKey(k)) { handle_mouse_movement(k); }
    else if (isMacroCommandkey(k)) { report_macro(getMacroId(k)); }
}

void handle_mouse_movement(Key k)
{
    uint8_t speed = getMouseMovementSpeed(k);
    if (isMouseUpKey(k))             { report_mouse_movement(UP, speed); }
    else if (isMouseDownKey(k))      { report_mouse_movement(DOWN, speed); }
    else if (isMouseRightKey(k))     { report_mouse_movement(RIGHT, speed); }
    else if (isMouseLeftKey(k))      { report_mouse_movement(LEFT, speed); }
    else if (isMouseWheelUpKey(k))   { report_mouse_movement(WHEELUP, speed); }
    else if (isMouseWheelDownKey(k)) { report_mouse_movement(WHEELDOWN, speed); }
}


void add_layer(const Key layer[NROWS][NCOLS])
{
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            LAYERS[N_LAYERS][i][j] = layer[i][j];
        }
    }
    N_LAYERS++;
}

int get_layer_selection(uint16_t current_layer)
{
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            Key k = LAYERS[current_layer][i][j];
            if (isLayerSelectionKey(k) && currently_pressed(i, j))
            {
                return get_layer_selection(k.command - 0x00FF - 1);
            }
        }
    }

    // If no layer selection key is pressed, the layer remains the same
    return current_layer;
}


void select_layer()
{
    if (LAYER_LOCKED)
    {
        CURRENT_LAYER = get_layer_selection(CURRENT_LOCKED_LAYER);
    }
    else
    {
        // Start layer evaluation from layer 0
        CURRENT_LAYER = get_layer_selection(0);
    }
}


int map_layer(Key keys[NKEYS])
{
    int index = 0;

    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            Key k = LAYERS[CURRENT_LAYER][i][j];

            // Handle normal key presses
            if (currently_pressed(i, j))
            {
                if (hasHoldKey(k)) // Double functionality
                {
                    // Send a key which is only a modifier
                    Key nk = {KEY_NONE, k.hold_mod, k.hold_mod, CMD_NONE};
                    keys[index++] = nk;
                }
                else // Only press functionality
                {
                    keys[index++] = k;
                }
            }

            // Handle Taps
            if (hasHoldKey(k))
            {
                // Reset Tap timer on first pressed of a key with Tap
                // functionality
                if (! previously_pressed(i, j) && currently_pressed(i, j))
                {
                    reset_tap_timer();
                }

                // Tap functionality is only triggered when tapped alone
                else if (tapped_alone(i, j) && ! TAP_IS_TIMEDOUT)
                {
                    keys[index++] = k;
                }
            }

#ifdef ENABLE_DOUBLE_SHIFT_CAPS_LOCK
            static bool shifted = false;
            static Key_coordinate shift_coord = {0};
            if ((k.modifiers == MOD_LEFT_SHIFT
                    || k.modifiers == MOD_RIGHT_SHIFT
                    || k.hold_mod == MOD_LEFT_SHIFT
                    || k.hold_mod == MOD_RIGHT_SHIFT)
                    && currently_pressed(i, j))
            {
                if (!shifted) // First shift pressed
                {
                    shifted = true;
                    shift_coord.i = i;
                    shift_coord.j = j;
                }
                // If the shift keys are in different positions, then
                // trigger caps lock
                else if ((shift_coord.i != i || shift_coord.j != j)
                        && currently_pressed(shift_coord.i, shift_coord.j))
                {
                    keys[index++] = k_caps;
                    shifted = false;
                }
            }
#endif // ENABLE_DOUBLE_SHIFT_CAPS_LOCK

        }
    }

    return index;
}


uint8_t retrieve_modifiers(Key keys[NKEYS])
{
    uint8_t mods = MOD_NONE;
    for (int i = 0; i < N_PRESSED; i++)
    {
        if (isModifierKey(keys[i]))
        {
            mods |= keys[i].modifiers;
        }
    }
    return mods;
}


void apply_modifiers(Key keys[NKEYS], int n)
{
    uint8_t mods = retrieve_modifiers(keys);
    for (int i = 0; i < n; i++)
    {
        if (isNormalKey(keys[i]))
        {
            keys[i].modifiers |= mods;
        }
    }
}


void lock_layer()
{
    CURRENT_LOCKED_LAYER = CURRENT_LAYER;
    LAYER_LOCKED = true;
}

void unlock_layer()
{
    CURRENT_LOCKED_LAYER = 0;
    LAYER_LOCKED = false;
}

void keyboard_init(void)
{
    // Enable tap timer interrupt
    nvic_enable_irq(NVIC_TIM2_IRQ);
    nvic_set_priority(NVIC_TIM2_IRQ, 1);
    rcc_periph_clock_enable(RCC_TIM2);
    reset_tap_timer();
}

void tim2_isr(void)
{
    TAP_IS_TIMEDOUT = true;
    TIM_SR(TIM2) &= ~TIM_SR_UIF; // Clear interrupt flag
}

void reset_tap_timer(void)
{
    TAP_IS_TIMEDOUT = false;
    TIM_CNT(TIM2) = 1;
    TIM_PSC(TIM2) = 72000; // 1000 counts per second (1ms)
    TIM_ARR(TIM2) = TAP_TIMEOUT_MS;
    TIM_DIER(TIM2) |= TIM_DIER_UIE; // Enable TIM2 interrupt

    // Configure TIM2
    TIM_CR1(TIM2) |= TIM_CR1_DIR_UP;
    TIM_CR1(TIM2) |= TIM_CR1_OPM;

    // Start TIM2
    TIM_CR1(TIM2) |= TIM_CR1_CEN;
}
