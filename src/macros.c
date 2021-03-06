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

Key MACROS[N_MACROS][MAX_MACRO_LENGTH];
int MACROS_CTR = 0;

void wipe_macro(int id)
{
    memset(MACROS[id], 0, sizeof(Key) * MAX_MACRO_LENGTH);
}

void add_macro(const Macro macro)
{
    wipe_macro(MACROS_CTR);
    int i = 0;
    const Key *k = &macro[0];
    while (! isEmptyKey(*k))
    {
        MACROS[MACROS_CTR][i++] = *k;
        k++;
    }
    MACROS_CTR++;
}

void add_string_macro(const char macro[MAX_MACRO_LENGTH])
{
    wipe_macro(MACROS_CTR);
    int i = 0;
    const char *c = &macro[0];
    while (*c != '\0')
    {
        MACROS[MACROS_CTR][i++] = char2key(*c);
        c++;
    }
    MACROS_CTR++;
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
