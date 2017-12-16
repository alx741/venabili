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
#include <stdint.h>
#include <libopencm3/usb/usbd.h>
#include "usb.h"
#include "usb_keyboard.h"
#include "usb_keys.h"
#include "keys_internal.h"

#define KEYBOARD_REPORT_ID 0x02

typedef struct _keyboard_report_t
{
    uint8_t report_id;
    uint8_t modifiers;
    uint8_t _reserved;
    uint8_t keycodes[6];
} keyboard_report_t;

void report_key(uint8_t modifiers, uint8_t keycode)
{
    keyboard_report_t kr = {0};
    kr.report_id = KEYBOARD_REPORT_ID;
    kr._reserved = 0x00;
    kr.modifiers = modifiers;
    kr.keycodes[0] = keycode;
    while(usbd_ep_write_packet(usbd_dev, 0x81, &kr, 9) != 9);
}

void report_6_keys(uint8_t modifiers, uint8_t keycodes[6])
{
    keyboard_report_t kr = {0};
    kr.report_id = KEYBOARD_REPORT_ID;
    kr._reserved = 0x00;
    kr.modifiers = modifiers;
    memcpy(kr.keycodes, keycodes, 6);
    while(usbd_ep_write_packet(usbd_dev, 0x81, &kr, 9) != 9);
}

void report_keypress(uint8_t modifiers, uint8_t keycode)
{
    report_key(modifiers, keycode);
    report_key(MOD_NONE, KEY_NONE);
}

void report_6_keypress(uint8_t modifiers, uint8_t keycodes[6])
{
    report_6_keys(modifiers, keycodes);
    report_key(MOD_NONE, KEY_NONE);
}

void type_string(const char *s)
{
    char c = *s;
    while (c != 0)
    {
        type_char(c);
        c = *(++s);
    }
}

void type_char(char c)
{
    Key k = char2key(c);
    report_keypress(k.modifiers, k.usb_keycode);
}
