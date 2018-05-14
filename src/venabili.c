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
        { k_tab,                 k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i,     k_o,   k_p,         k_backslash},
        { HLctrl(k_escape),      k_a, k_s, k_d, k_f, HLshift(k_g), HRshift(k_h), k_j, k_k,     k_l,   k_semicolon, HRctrl(k_enter)},
        { HLshift(k_open_paren), k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_comma, k_dot, k_slash,     HRshift(k_close_paren)},
        { k_empty,               k_empty, k_empty, k_empty, k_empty, LS(1), k_space, k_empty, k_empty, k_empty, k_empty, k_empty},
    };

    Layer l1 =
    {
        { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty,     k_empty, k_empty, k_empty, k_empty, k_empty},
        { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_backspace, k_empty, k_empty, k_empty, k_empty, k_empty},
        { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty,     k_empty, k_empty, k_empty, k_empty, k_empty},
        { c_flash_mode, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty,     k_empty, k_empty, k_empty, k_empty, k_empty},
    };

    /* { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty}, */

    /* Layer l2 = */
    /* { */
    /*     { m_click_1,     MACRO(0) }, */
    /*     { m_click_2,     MACRO(1) }, */
    /*     { m_click_3,     k_empty  }, */
    /*     { c_flash_mode,  k_empty  }, */
    /* }; */

    add_layer(l0);
    add_layer(l1);




    /*********************
    *      MACROS
    *********************/

    Macro m1 = { Rctrl(k_c), k_l, k_s, k_enter, k_empty };

    add_macro(m1);
    add_string_macro("This is Venabili typing!");
}
