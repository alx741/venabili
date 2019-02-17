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


/*
| ------------------------------------------------------------------
| ------------------------------------------------------------------
|
|          Use this file to customize layers and macros
|
| ------------------------------------------------------------------
| ------------------------------------------------------------------
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
| Declare your layers as 4x12 matrices and then register them with:
|
|   add_layer(layer_name);
|
|
| The very first layer you register is the default one
|
| Check out the available keys in the `keys.h` file
|
*/

Layer l0 =
{
    { k_tab, k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_hyphen},
    { HLctrl(k_escape), k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, HRctrl(k_enter)},
    { m_lshift, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_comma, k_dot, k_slash, m_rshift},
    { m_lsuper, m_lalt, m_ralt, LS(3, k_empty), LS(2, k_empty), LS(1, k_space), k_space, LS(2, k_empty), LS(4, k_empty), m_ralt, m_lalt, m_rsuper},
};

Layer l1 =
{
    { HLshift(k_a), k_b, k_empty, k_empty, k_empty, k_empty, k_caret, k_ampersand, k_asterisk, k_open_paren, k_close_paren, k_equal},
    { m_lctrl, k_empty, k_mute, LS(2, k_space), m_lshift, m_lshift, k_arrow_left, k_arrow_down, k_arrow_up, k_arrow_right, k_single_quote, k_backslash},
    { m_lshift, k_empty, k_empty, k_empty, k_vol_down, k_empty, k_backspace, k_delete, k_open_bracket, k_close_bracket, k_double_quote, k_pipe},
    { c_flash_mode, k_empty, k_empty, k_empty, k_empty, k_empty, k_space, k_empty, k_empty, k_empty, k_empty, k_empty},
};

Layer l2 =
{
    { k_tilde, k_bang, k_at, k_hash, k_dollar, k_percent, k_dot, k_7, k_8, k_9, k_empty, k_equal},
    { k_back_quote, k_back_quote, k_single_quote, k_single_quote, k_double_quote, k_double_quote, k_0, k_4, k_5, k_6, k_asterisk, k_open_paren},
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_backspace, k_1, k_2, k_3, k_slash, k_close_paren},
    { c_layer_lock, k_empty, k_empty, k_empty, k_empty, k_empty, k_plus, k_empty, k_empty, k_empty, k_empty, k_empty},
};

Layer l3 =
{
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_f7, k_f8, k_f9, k_f10, k_home},
    { m_lctrl, k_empty, k_empty, k_empty, k_empty, k_empty, k_pagedown, k_f4, k_f5, k_f6, k_f11, k_end},
    { m_lshift, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_f1, k_f2, k_f3, k_f12, MACRO(2)},
    { Lctrl(m_lalt), m_lalt, m_ralt, k_empty, k_empty, k_space, k_escape, k_empty, k_empty, k_empty, k_empty, k_empty},
};

Layer l4 =
{
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty},
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, ML(5), MD(5), MU(5), MR(5), k_empty, k_empty},
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, k_empty},
    { k_empty, k_empty, k_empty, k_empty, k_empty, k_empty, m_click_1, m_click_2, k_empty, k_empty, k_empty, k_empty},
};


add_layer(l0);
add_layer(l1);
add_layer(l2);
add_layer(l3);
add_layer(l4);



/*
| ------------------------------------------------------------------
| Macros
| ------------------------------------------------------------------
|
| Declare your macros as a sequence of key presses, terminated
| with `k_empty`, and then register them with:
|
|   add_macro(m1);
|
|
| If you'd like a text string macro, declare it with:
|
|   add_string_macro("text string here");
|
|
| Macros are made available for use in layers through the
| `MACRO(id)` key, where 'id' goes from 0 in the order you
| register them.
|
*/


Macro m1 = { Rctrl(k_c), k_l, k_s, k_enter, k_empty };
Macro m2 = { Rctrl(k_c), Rctrl(k_v), k_empty };

add_macro(m1);
add_macro(m2);
add_string_macro("this_could_be_a_password");

}
