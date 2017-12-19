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


#include "usb_keys.h"
#include "keys_internal.h"

bool hasHoldKey(Key k)
{
    return k.hold_mod != MOD_NONE;
}

bool isNormalKey(Key k)
{
    return (k.usb_keycode != KEY_NONE || k.modifiers != MOD_NONE)
            && k.command == CMD_NONE;
}

bool isCommandKey(Key k)
{
    return !isNormalKey(k);
}

bool isLayerSelectionKey(Key k)
{
    return isCommandKey(k) && (k.command & 0xFF00);
}

bool isModifierKey(Key k)
{
    return isNormalKey(k)
        && k.usb_keycode == KEY_NONE
        && k.modifiers != MOD_NONE;
}

bool isEmptyKey(Key k)
{
    return k.usb_keycode == KEY_NONE
        && k.modifiers == MOD_NONE
        && k.command == CMD_NONE;
}

bool areKeysEqual(Key k1, Key k2)
{
    return k1.usb_keycode == k2.usb_keycode
            && k1.modifiers == k2.modifiers
            && k1.command == k2.command;
}


// Macro commands identification
bool isMacroCommandkey(Key k)
{
    return isCommandKey(k)
            && k.command >= CMD_MACRO_FIRST
            && k.command <= CMD_MACRO_LAST;
}

int getMacroId(Key k)
{
    return k.command - 0x0075;
}

// Mouse commands identification
bool isMouseCommandKey(Key k)
{
    return isCommandKey(k)
        && k.command >= CMD_MOUSE_UP
        && k.command <= CMD_MOUSE_CLICK_5;
}

bool isMouseMovementKey(Key k)
{
    return isMouseCommandKey(k)
        && k.command >= CMD_MOUSE_UP
        && k.command < CMD_MOUSE_CLICK_1;
}

bool isMouseClickKey(Key k)
{
    return isMouseCommandKey(k)
        && k.command >= CMD_MOUSE_CLICK_1
        && k.command <= CMD_MOUSE_CLICK_5;
}

bool isMouseUpKey(Key k)
{
    return isCommandKey(k)
        && k.command >= CMD_MOUSE_UP
        && k.command < CMD_MOUSE_DOWN;
}

bool isMouseDownKey(Key k)
{
    return isCommandKey(k)
        && k.command >= CMD_MOUSE_DOWN
        && k.command < CMD_MOUSE_RIGHT;
}

bool isMouseRightKey(Key k)
{
    return isCommandKey(k)
        && k.command >= CMD_MOUSE_RIGHT
        && k.command < CMD_MOUSE_LEFT;
}

bool isMouseLeftKey(Key k)
{
    return isCommandKey(k)
        && k.command >= CMD_MOUSE_LEFT
        && k.command < CMD_MOUSE_WHEELUP;
}

bool isMouseWheelUpKey(Key k)
{
    return isCommandKey(k)
        && k.command >= CMD_MOUSE_WHEELUP
        && k.command < CMD_MOUSE_WHEELDOWN;
}

bool isMouseWheelDownKey(Key k)
{
    return isCommandKey(k)
        && k.command >= CMD_MOUSE_WHEELDOWN
        && k.command < CMD_MOUSE_CLICK_1;
}

uint8_t getMouseMovementSpeed(Key k)
{
    // Movement speed is in the first nibble
    return k.command & 0x000F;
}

uint8_t getMouseClickButton(Key k)
{
    // Click button is in the first nibble
    return (k.command & 0x000F) + 1;
}



Key apply_mod(Key k, uint8_t mod)
{
    Key new;
    new.modifiers = k.modifiers;
    new.modifiers |= mod;
    new.hold_mod = k.hold_mod;
    new.usb_keycode = k.usb_keycode;
    new.command = k.command;
    return new;
}

Key apply_hold_mod(Key k, uint8_t mod)
{
    Key new;
    new.modifiers = k.modifiers;
    new.hold_mod = mod;
    new.usb_keycode = k.usb_keycode;
    new.command = k.command;
    return new;
}

Key Lctrl(Key k)  { return apply_mod(k, MOD_LEFT_CTRL); }
Key Lshift(Key k) { return apply_mod(k, MOD_LEFT_SHIFT); }
Key Lalt(Key k)   { return apply_mod(k, MOD_LEFT_ALT); }
Key Lsuper(Key k) { return apply_mod(k, MOD_LEFT_SUPER); }
Key Rctrl(Key k)  { return apply_mod(k, MOD_RIGHT_CTRL); }
Key Rshift(Key k) { return apply_mod(k, MOD_RIGHT_SHIFT); }
Key Ralt(Key k)   { return apply_mod(k, MOD_RIGHT_ALT); }
Key Rsuper(Key k) { return apply_mod(k, MOD_RIGHT_SUPER); }

Key HLctrl(Key k)  { return apply_hold_mod(k, MOD_LEFT_CTRL); }
Key HLshift(Key k) { return apply_hold_mod(k, MOD_LEFT_SHIFT); }
Key HLalt(Key k)   { return apply_hold_mod(k, MOD_LEFT_ALT); }
Key HLsuper(Key k) { return apply_hold_mod(k, MOD_LEFT_SUPER); }
Key HRctrl(Key k)  { return apply_hold_mod(k, MOD_RIGHT_CTRL); }
Key HRshift(Key k) { return apply_hold_mod(k, MOD_RIGHT_SHIFT); }
Key HRalt(Key k)   { return apply_hold_mod(k, MOD_RIGHT_ALT); }
Key HRsuper(Key k) { return apply_hold_mod(k, MOD_RIGHT_SUPER); }


/**********
 *  Keys
 *********/

#define mkNormalKey(keycode) {keycode, MOD_NONE, MOD_NONE, CMD_NONE}
#define mkNormalShiftedKey(keycode) {keycode, MOD_LEFT_SHIFT, MOD_NONE, CMD_NONE}
#define mkCommandKey(command) {KEY_NONE, MOD_NONE, MOD_NONE, command}

const Key k_empty = mkCommandKey(CMD_NONE);

const Key k_a = mkNormalKey(KEY_A),   k_A = mkNormalShiftedKey(KEY_A);
const Key k_b = mkNormalKey(KEY_B),   k_B = mkNormalShiftedKey(KEY_B);
const Key k_c = mkNormalKey(KEY_C),   k_C = mkNormalShiftedKey(KEY_C);
const Key k_d = mkNormalKey(KEY_D),   k_D = mkNormalShiftedKey(KEY_D);
const Key k_e = mkNormalKey(KEY_E),   k_E = mkNormalShiftedKey(KEY_E);
const Key k_f = mkNormalKey(KEY_F),   k_F = mkNormalShiftedKey(KEY_F);
const Key k_g = mkNormalKey(KEY_G),   k_G = mkNormalShiftedKey(KEY_G);
const Key k_h = mkNormalKey(KEY_H),   k_H = mkNormalShiftedKey(KEY_H);
const Key k_i = mkNormalKey(KEY_I),   k_I = mkNormalShiftedKey(KEY_I);
const Key k_j = mkNormalKey(KEY_J),   k_J = mkNormalShiftedKey(KEY_J);
const Key k_k = mkNormalKey(KEY_K),   k_K = mkNormalShiftedKey(KEY_K);
const Key k_l = mkNormalKey(KEY_L),   k_L = mkNormalShiftedKey(KEY_L);
const Key k_m = mkNormalKey(KEY_M),   k_M = mkNormalShiftedKey(KEY_M);
const Key k_n = mkNormalKey(KEY_N),   k_N = mkNormalShiftedKey(KEY_N);
const Key k_o = mkNormalKey(KEY_O),   k_O = mkNormalShiftedKey(KEY_O);
const Key k_p = mkNormalKey(KEY_P),   k_P = mkNormalShiftedKey(KEY_P);
const Key k_q = mkNormalKey(KEY_Q),   k_Q = mkNormalShiftedKey(KEY_Q);
const Key k_r = mkNormalKey(KEY_R),   k_R = mkNormalShiftedKey(KEY_R);
const Key k_s = mkNormalKey(KEY_S),   k_S = mkNormalShiftedKey(KEY_S);
const Key k_t = mkNormalKey(KEY_T),   k_T = mkNormalShiftedKey(KEY_T);
const Key k_u = mkNormalKey(KEY_U),   k_U = mkNormalShiftedKey(KEY_U);
const Key k_v = mkNormalKey(KEY_V),   k_V = mkNormalShiftedKey(KEY_V);
const Key k_w = mkNormalKey(KEY_W),   k_W = mkNormalShiftedKey(KEY_W);
const Key k_x = mkNormalKey(KEY_X),   k_X = mkNormalShiftedKey(KEY_X);
const Key k_y = mkNormalKey(KEY_Y),   k_Y = mkNormalShiftedKey(KEY_Y);
const Key k_z = mkNormalKey(KEY_Z),   k_Z = mkNormalShiftedKey(KEY_Z);

const Key k_0 = mkNormalKey(KEY_0);
const Key k_1 = mkNormalKey(KEY_1);
const Key k_2 = mkNormalKey(KEY_2);
const Key k_3 = mkNormalKey(KEY_3);
const Key k_4 = mkNormalKey(KEY_4);
const Key k_5 = mkNormalKey(KEY_5);
const Key k_6 = mkNormalKey(KEY_6);
const Key k_7 = mkNormalKey(KEY_7);
const Key k_8 = mkNormalKey(KEY_8);
const Key k_9 = mkNormalKey(KEY_9);

const Key m_lctrl  = { KEY_NONE, MOD_LEFT_CTRL, CMD_NONE, CMD_NONE};
const Key m_lshift = { KEY_NONE, MOD_LEFT_SHIFT, CMD_NONE, CMD_NONE};
const Key m_lalt   = { KEY_NONE, MOD_LEFT_ALT, CMD_NONE, CMD_NONE};
const Key m_lsuper = { KEY_NONE, MOD_LEFT_SUPER, CMD_NONE, CMD_NONE};
const Key m_rctrl  = { KEY_NONE, MOD_RIGHT_CTRL, CMD_NONE, CMD_NONE};
const Key m_rshift = { KEY_NONE, MOD_RIGHT_SHIFT, CMD_NONE, CMD_NONE};
const Key m_ralt   = { KEY_NONE, MOD_RIGHT_ALT, CMD_NONE, CMD_NONE};
const Key m_rsuper = { KEY_NONE, MOD_RIGHT_SUPER, CMD_NONE, CMD_NONE};

const Key k_back_quote    = mkNormalKey(KEY_GRAVE_ACCENT);
const Key k_single_quote  = mkNormalKey(KEY_SINGLE_QUOTE);
const Key k_hyphen        = mkNormalKey(KEY_HYPHEN);
const Key k_equal         = mkNormalKey(KEY_EQUAL);
const Key k_semicolon     = mkNormalKey(KEY_SEMICOLON);
const Key k_dot           = mkNormalKey(KEY_DOT);
const Key k_slash         = mkNormalKey(KEY_SLASH);
const Key k_backslash     = mkNormalKey(KEY_BACKSLASH);
const Key k_double_quote  = mkNormalShiftedKey(KEY_SINGLE_QUOTE);
const Key k_tilde         = mkNormalShiftedKey(KEY_GRAVE_ACCENT);
const Key k_bang          = mkNormalShiftedKey(KEY_1);
const Key k_at            = mkNormalShiftedKey(KEY_2);
const Key k_hash          = mkNormalShiftedKey(KEY_3);
const Key k_dollar        = mkNormalShiftedKey(KEY_4);
const Key k_percent       = mkNormalShiftedKey(KEY_5);
const Key k_caret         = mkNormalShiftedKey(KEY_6);
const Key k_ampersand     = mkNormalShiftedKey(KEY_7);
const Key k_asterisk      = mkNormalShiftedKey(KEY_8);
const Key k_under_score   = mkNormalShiftedKey(KEY_HYPHEN);
const Key k_plus          = mkNormalShiftedKey(KEY_EQUAL);
const Key k_colon         = mkNormalShiftedKey(KEY_SEMICOLON);
const Key k_comma         = mkNormalShiftedKey(KEY_DOT);
const Key k_question_mark = mkNormalShiftedKey(KEY_SLASH);
const Key k_pipe          = mkNormalShiftedKey(KEY_BACKSLASH);
const Key k_greater_than  = mkNormalShiftedKey(KEY_DOT);
const Key k_less_than     = mkNormalShiftedKey(KEY_COMMA);
const Key k_open_paren    = mkNormalShiftedKey(KEY_9);
const Key k_close_paren   = mkNormalShiftedKey(KEY_0);
const Key k_open_bracket  = mkNormalKey(KEY_OPEN_BRACKET);
const Key k_close_bracket = mkNormalKey(KEY_CLOSE_BRACKET);
const Key k_open_brace    = mkNormalShiftedKey(KEY_OPEN_BRACKET);
const Key k_close_brace   = mkNormalShiftedKey(KEY_CLOSE_BRACKET);

const Key k_enter        = mkNormalKey(KEY_ENTER);
const Key k_escape       = mkNormalKey(KEY_ESCAPE);
const Key k_backspace    = mkNormalKey(KEY_BACKSPACE);
const Key k_tab          = mkNormalKey(KEY_TAB);
const Key k_space        = mkNormalKey(KEY_SPACEBAR);
const Key k_caps         = mkNormalKey(KEY_CAPS);
const Key k_print_screen = mkNormalKey(KEY_PRINT_SCREEN);
const Key k_scroll_lock  = mkNormalKey(KEY_SCROLL_LOCK);
const Key k_pause        = mkNormalKey(KEY_PAUSE);
const Key k_insert       = mkNormalKey(KEY_INSERT);
const Key k_delete       = mkNormalKey(KEY_DELETE);
const Key k_home         = mkNormalKey(KEY_HOME);
const Key k_end          = mkNormalKey(KEY_END);
const Key k_pageup       = mkNormalKey(KEY_PAGE_UP);
const Key k_pagedown     = mkNormalKey(KEY_PAGE_DOWN);
const Key k_arrow_up     = mkNormalKey(KEY_UP_ARROW);
const Key k_arrow_down   = mkNormalKey(KEY_DOWN_ARROW);
const Key k_arrow_left   = mkNormalKey(KEY_LEFT_ARROW);
const Key k_arrow_right  = mkNormalKey(KEY_RIGHT_ARROW);

const Key k_menu         = mkNormalKey(KEY_MENU);
const Key k_select       = mkNormalKey(KEY_SELECT);
const Key k_stop         = mkNormalKey(KEY_STOP);
const Key k_again        = mkNormalKey(KEY_AGAIN);
const Key k_undo         = mkNormalKey(KEY_UNDO);
const Key k_cut          = mkNormalKey(KEY_CUT);
const Key k_copy         = mkNormalKey(KEY_COPY);
const Key k_paste        = mkNormalKey(KEY_PASTE);
const Key k_find         = mkNormalKey(KEY_FIND);
const Key k_mute         = mkNormalKey(KEY_MUTE);
const Key k_vol_up       = mkNormalKey(KEY_VOL_UP);
const Key k_vol_down     = mkNormalKey(KEY_VOL_DOWN);

const Key k_f1           = mkNormalKey(KEY_F1);
const Key k_f2           = mkNormalKey(KEY_F2);
const Key k_f3           = mkNormalKey(KEY_F3);
const Key k_f4           = mkNormalKey(KEY_F4);
const Key k_f5           = mkNormalKey(KEY_F5);
const Key k_f6           = mkNormalKey(KEY_F6);
const Key k_f7           = mkNormalKey(KEY_F7);
const Key k_f8           = mkNormalKey(KEY_F8);
const Key k_f9           = mkNormalKey(KEY_F9);
const Key k_f10          = mkNormalKey(KEY_F10);
const Key k_f11          = mkNormalKey(KEY_F11);
const Key k_f12          = mkNormalKey(KEY_F12);
const Key k_f13          = mkNormalKey(KEY_F13);
const Key k_f14          = mkNormalKey(KEY_F14);
const Key k_f15          = mkNormalKey(KEY_F15);
const Key k_f16          = mkNormalKey(KEY_F16);
const Key k_f17          = mkNormalKey(KEY_F17);
const Key k_f18          = mkNormalKey(KEY_F18);
const Key k_f19          = mkNormalKey(KEY_F19);
const Key k_f20          = mkNormalKey(KEY_F20);
const Key k_f21          = mkNormalKey(KEY_F21);
const Key k_f22          = mkNormalKey(KEY_F22);
const Key k_f23          = mkNormalKey(KEY_F23);
const Key k_f24          = mkNormalKey(KEY_F24);


const Key c_layer_lock = mkCommandKey(CMD_LOCK_LAYER);

const Key m_click_1 = mkCommandKey(CMD_MOUSE_CLICK_1);
const Key m_click_2 = mkCommandKey(CMD_MOUSE_CLICK_2);
const Key m_click_3 = mkCommandKey(CMD_MOUSE_CLICK_3);
const Key m_click_4 = mkCommandKey(CMD_MOUSE_CLICK_4);
const Key m_click_5 = mkCommandKey(CMD_MOUSE_CLICK_5);


Key char2key(char c)
{
    switch(c)
    {
        case 'a':
            return k_a;
        case 'b':
            return k_b;
        case 'c':
            return k_c;
        case 'd':
            return k_d;
        case 'e':
            return k_e;
        case 'f':
            return k_f;
        case 'g':
            return k_g;
        case 'h':
            return k_h;
        case 'i':
            return k_i;
        case 'j':
            return k_j;
        case 'k':
            return k_k;
        case 'l':
            return k_l;
        case 'm':
            return k_m;
        case 'n':
            return k_n;
        case 'o':
            return k_o;
        case 'p':
            return k_p;
        case 'q':
            return k_q;
        case 'r':
            return k_r;
        case 's':
            return k_s;
        case 't':
            return k_t;
        case 'u':
            return k_u;
        case 'v':
            return k_v;
        case 'w':
            return k_w;
        case 'x':
            return k_x;
        case 'y':
            return k_y;
        case 'z':
            return k_z;


        case 'A':
            return k_A;
        case 'B':
            return k_B;
        case 'C':
            return k_C;
        case 'D':
            return k_D;
        case 'E':
            return k_E;
        case 'F':
            return k_F;
        case 'G':
            return k_G;
        case 'H':
            return k_H;
        case 'I':
            return k_I;
        case 'J':
            return k_J;
        case 'K':
            return k_K;
        case 'L':
            return k_L;
        case 'M':
            return k_M;
        case 'N':
            return k_N;
        case 'O':
            return k_O;
        case 'P':
            return k_P;
        case 'Q':
            return k_Q;
        case 'R':
            return k_R;
        case 'S':
            return k_S;
        case 'T':
            return k_T;
        case 'U':
            return k_U;
        case 'V':
            return k_V;
        case 'W':
            return k_W;
        case 'X':
            return k_X;
        case 'Y':
            return k_Y;
        case 'Z':
            return k_Z;


        case '0':
            return k_0;
        case '1':
            return k_1;
        case '2':
            return k_2;
        case '3':
            return k_3;
        case '4':
            return k_4;
        case '5':
            return k_5;
        case '6':
            return k_6;
        case '7':
            return k_7;
        case '8':
            return k_8;
        case '9':
            return k_9;


        case ' ':
            return k_space;
        case '!':
            return k_bang;
        case '"':
            return k_single_quote;
        case '#':
            return k_hash;
        case '$':
            return k_dollar;
        case '%':
            return k_percent;
        case '&':
            return k_ampersand;
        case '\'':
            return k_single_quote;
        case '(':
            return k_open_paren;
        case ')':
            return k_close_paren;
        case '*':
            return k_asterisk;
        case '+':
            return k_plus;
        case ',':
            return k_comma;
        case '-':
            return k_hyphen;
        case '.':
            return k_dot;
        case '/':
            return k_slash;
        case ':':
            return k_colon;
        case ';':
            return k_semicolon;
        case '<':
            return k_less_than;
        case '=':
            return k_equal;
        case '>':
            return k_greater_than;
        case '?':
            return k_question_mark;
        case '@':
            return k_at;
        case '[':
            return k_open_bracket;
        case '\\':
            return k_backslash;
        case ']':
            return k_close_bracket;
        case '^':
            return k_caret;
        case '_':
            return k_under_score;
        case '`':
            return k_back_quote;
        case '{':
            return k_open_brace;
        case '|':
            return k_pipe;
        case '}':
            return k_close_brace;
        case '~':
            return k_tilde;


        case '\n':
            return k_enter;
        case '\t':
            return k_tab;
        case '\b':
            return k_backspace;

        default:
            break;
    }

    // If no other Key fits, then it's an empty key
    return k_empty;
}
