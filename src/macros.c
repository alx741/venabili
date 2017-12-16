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
#include "usb_keyboard.h"
#include "keys_internal.h"
#include "macros.h"

Key MACROS[NMACROS][MACRO_LENGTH];
int N_MACROS = 0;

void wipe_macro(int id)
{
    memset(MACROS[id], 0, sizeof(Key) * MACRO_LENGTH);
}

void add_macro(const Key macro[MACRO_LENGTH])
{
    wipe_macro(N_MACROS);
    int i = 0;
    const Key *k = &macro[0];
    while (! isEmptyKey(*k))
    {
        MACROS[N_MACROS][i++] = *k;
        k++;
    }
    N_MACROS++;
}

void add_string_macro(const char macro[MACRO_LENGTH])
{
    wipe_macro(N_MACROS);
    int i = 0;
    const char *c = &macro[0];
    while (*c != '\0')
    {
        MACROS[N_MACROS][i++] = char2key(*c);
        c++;
    }
    N_MACROS++;
}

void report_macro(int id)
{
    Key *k = MACROS[id];
    while (! isEmptyKey(*k))
    {
        if (isNormalKey(*k))
        {
            report_keypress(k->modifiers, k->usb_keycode);
        }
        k++;
    }
}
