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
