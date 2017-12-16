#include "keys.h"
#include "keyboard.h"
#include "macros.h"

void venabili(void)
{
    // Layers definition
    Key layer0[NROWS][NCOLS] =
    {
        { k_a, k_caps                 },
        { k_c, HLshift(k_open_paren)  },
        { k_d, LS(1)                  },
        { k_A, HLshift(k_close_paren) },
    };

    Key layer1[NROWS][NCOLS] =
    {
        { MU(10), MACRO(0) },
        { MD(5),  MACRO(1) },
        { ML(15), k_empty },
        { MR(1),  MACRO(2) },
    };

    // Macros definition
    Key macro0[MACRO_LENGTH] = { k_V, k_e, k_n, k_a, k_v, k_i, k_l, k_i, k_space, k_empty };
    Key macro1[MACRO_LENGTH] = { Rctrl(k_c), k_l, k_s, k_enter, k_empty };


    add_layer(layer0);
    add_layer(layer1);

    add_macro(macro0);
    add_macro(macro1);
    add_string_macro("This is Venabili typing!");
}
