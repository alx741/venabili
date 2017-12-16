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
