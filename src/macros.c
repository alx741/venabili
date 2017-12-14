#include "keys.h"
#include "macros.h"

static Key MACROS[NMACROS][MACRO_LENGTH];
static int N_MACROS = 0;

void add_macro(Key macro[MACRO_LENGTH])
{
    Key *k = &macro[0];
    int i = 0;
    while (isEmptyKey(*k))
    {
        MACROS[N_MACROS][i++] = *k;
        k++;
    }
    N_MACROS++;
}
