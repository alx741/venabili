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

    /*********************
    *      LAYERS
    *********************/

    Layer l0 =
    {
        { k_r,           k_t          },
        { HRshift(k_f),  HLshift(k_g) },
        { k_v,           k_b          },
        { m_lshift,      LS(1)        },
    };

    Layer l1 =
    {
        { m_click_1,     MACRO(0) },
        { m_click_2,     MACRO(1) },
        { m_click_3,     k_empty  },
        { c_flash_mode,  k_empty  },
    };

    add_layer(l0);
    add_layer(l1);




    /*********************
    *      MACROS
    *********************/

    Key macro0[MAX_MACRO_LENGTH] = { k_V, k_e, k_n, k_a, k_v, k_i, k_l, k_i, k_space, k_empty };
    Key macro1[MAX_MACRO_LENGTH] = { Rctrl(k_c), k_l, k_s, k_enter, k_empty };

    add_macro(macro0);
    add_macro(macro1);
    add_string_macro("This is Venabili typing!");
}
