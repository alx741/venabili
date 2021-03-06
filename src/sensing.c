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


#include <string.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include "sensing.h"
#include "usb_keys.h"

int N_PRESSED = 0;
int N_PREV_PRESSED = 0;
bool KMAT_PREV_STATE[NROWS][NCOLS] = { { false } };
bool KMAT_STATE[NROWS][NCOLS] = { { false } };
Key_coord PRESSED_KEYS[NKEYS] = { {0, 0} };
Key_coord PRESSED_PREV_KEYS[NKEYS] = { {0, 0} };

#define MATRIX_OUTPUTS_START 6

void keyboard_sensing_init(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);

    // PORTA [0-10], PORTB 15 as matrix inputs
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7
            | GPIO8 | GPIO9 | GPIO10);
    gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO15);

    // PORTB [6-9] as matrix outputs
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
            GPIO6 | GPIO7 | GPIO8 | GPIO9);
    gpio_clear(GPIOB, GPIO6 | GPIO7 | GPIO8 | GPIO9);
}

void backup_and_wipe_current_state(void)
{
    memcpy(KMAT_PREV_STATE, KMAT_STATE, sizeof(bool) * NROWS * NCOLS);
    memcpy(PRESSED_PREV_KEYS, PRESSED_KEYS, sizeof(Key_coord) * NKEYS);
    memset(KMAT_STATE, 0, sizeof(bool) * NROWS * NCOLS);
    memset(PRESSED_KEYS, 0, sizeof(Key_coord) * NKEYS);

    N_PREV_PRESSED = N_PRESSED;
    N_PRESSED = 0;
}

uint16_t read_column(uint16_t c)
{
    if (c < 11)
    {
        return gpio_get(GPIOA, 1 << c);
    }
    else
    {
        return gpio_get(GPIOB, 1 << 15);
    }
}

int sense_keys(void)
{
    int n = 0;
    int i, j = 0; // Key index
    Key_coord coordinate = {0, 0};

    // Debouncing variables
    int debounce_counter = 0;
    bool key_state = false;
    bool key_prev_state = false;

    backup_and_wipe_current_state();

    for (int r = MATRIX_OUTPUTS_START; r < (NROWS + MATRIX_OUTPUTS_START); r++)
    {
        i = r - MATRIX_OUTPUTS_START;
        gpio_set(GPIOB, 1 << r);
        for (int c = 0; c < NCOLS; c++)
        {
            j = c;
            coordinate.i = i;
            coordinate.j = j;

            // Debounce
            debounce_counter = 0;
            while (debounce_counter < DEBOUNCE_FACTOR)
            {
                key_state = read_column(c);
                // Some bouncing going on
                if (key_state != key_prev_state) { debounce_counter = 0; }
                // Seems stable
                else { debounce_counter++; }
                key_prev_state = key_state;
                key_state = false;
            }

            // Read key state
            if (read_column(c))
            {
                KMAT_STATE[i][j] = true;
                PRESSED_KEYS[n++] = coordinate;
            }
            else
            {
                KMAT_STATE[i][j] = false;
            }
        }
        gpio_clear(GPIOB, 1 << r);
    }

    PRESSED_KEYS[n].i = -1;
    PRESSED_KEYS[n].j = -1;
    N_PRESSED = n;
    return n;
}

bool currently_pressed(int i, int j)
{
    return KMAT_STATE[i][j];
}

bool previously_pressed(int i, int j)
{
    return KMAT_PREV_STATE[i][j];
}

bool currently_pressed_alone(int i, int j)
{
    return (currently_pressed(i, j) && N_PRESSED == 1);
}

bool previously_pressed_alone(int i, int j)
{
    return (previously_pressed(i, j) && N_PREV_PRESSED == 1);
}

bool tapped(int i, int j)
{
    return (previously_pressed(i, j) && !currently_pressed(i, j));
}

bool tapped_alone(int i, int j)
{
    return (previously_pressed_alone(i, j) && !currently_pressed(i, j));
}

bool isNullCoordinate(Key_coord kc)
{
    return (kc.i == -1 && kc.j == -1);
}

bool areKeysInSamePlace(Key_coord kc1, Key_coord kc2)
{
    return (kc1.i == kc2.i && kc1.j == kc2.j);
}

Key_coord coord(int i, int j)
{
    Key_coord kc = {i, j};
    return kc;
}
