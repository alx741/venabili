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


#include <stdlib.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>

#include "usb.h"
#include "usb_keys.h"
#include "usb_keyboard.h"
#include "sensing.h"

#include "keys.h"
#include "keyboard.h"
#include "macros.h"

#include "venabili.c"

int main(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    usb_init();
    keyboard_sensing_init();
    keyboard_init();

    // Invoke user code
    venabili();

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
