#include <string.h>
#include "usb_keyboard.h"
#include "keys.h"
#include "macros.h"

Key MACROS[NMACROS][MACRO_LENGTH];
int N_MACROS = 0;

void wipe_macro(int id)
{
    memset(MACROS[id], 0, sizeof(Key) * MACRO_LENGTH);
}

void add_macro(Key macro[MACRO_LENGTH])
{
    wipe_macro(N_MACROS);
    int i = 0;
    Key *k = &macro[0];
    while (! isEmptyKey(*k))
    {
        MACROS[N_MACROS][i++] = *k;
        k++;
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
