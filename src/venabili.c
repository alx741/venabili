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

/*
| ------------------------------------------------------------------
| Layers
| ------------------------------------------------------------------
|
| Declare your layers as 4x12 matrices...
|
|
*/

Layer l0 =
{
    { k_tab,                 k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i,     k_o,   k_p,         k_hyphen},
    { HLctrl(k_escape),      k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k,     k_l,   k_semicolon, HRctrl(k_enter)},
    { HLshift(k_open_paren), k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_comma, k_dot, k_slash,     HRshift(k_close_paren)},
    { k_empty,               k_empty, k_empty, k_empty, LS(2), LS(1), k_space, LS(3), k_empty, k_empty, k_empty, k_empty},
};

Layer l1 =
{
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_caret,     k_ampersand, k_asterisk, k_open_paren, k_close_paren, k_equal},
    { k_empty, k_empty, k_mute, k_pause, k_vol_up, m_lshift, k_arrow_left, k_arrow_down, k_arrow_up, k_arrow_right, k_single_quote, k_backslash},
    { m_lshift, k_empty, k_empty, k_empty, k_vol_down, k_empty, k_backspace, k_open_bracket, k_close_bracket, k_empty, k_empty, k_empty},
    { c_flash_mode, k_empty, k_empty, k_empty, k_empty, k_empty, k_space, k_empty, k_empty, k_empty, k_empty, k_empty},
};

Layer l2 =
{
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_delete,     k_7, k_8, k_9, k_empty, k_empty},
    { k_empty, k_empty, k_open_paren, k_close_paren, k_empty, k_empty, k_0, k_4, k_5, k_6, k_asterisk, k_empty},
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_backspace, k_1, k_2, k_3, k_slash, k_empty},
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_plus,     k_hyphen, k_empty, k_empty, k_empty, k_empty},
};

Layer l3 =
{
    { k_tilde, k_bang, k_at, k_hash, k_dollar, k_percent, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty},
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty},
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty},
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty},
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
add_layer(l2);
add_layer(l3);



/*
| ------------------------------------------------------------------
| Macros
| ------------------------------------------------------------------
|
| Declare your macros...
|
|
*/

Macro m1 = { Rctrl(k_c), k_l, k_s, k_enter, k_empty };

add_macro(m1);
add_string_macro("This is Venabili typing!");

}
