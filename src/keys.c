#include "usb_keys.h"
#include "keys.h"

bool hasPressKey(Mapkey mk)
{
    return (! isEmptyKey(mk.press));
}

bool hasHoldKey(Mapkey mk)
{
    return (! isEmptyKey(mk.hold));
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


// Mouse commands identification
bool isMouseUpKey(Key k)
{
    return isCommandKey(k)
        && k.command >= 0x0010
        && k.command <= 0x001F;
}

bool isMouseDownKey(Key k)
{
    return isCommandKey(k)
        && k.command >= 0x0020
        && k.command <= 0x002F;
}

bool isMouseRightKey(Key k)
{
    return isCommandKey(k)
        && k.command >= 0x0030
        && k.command <= 0x003F;
}

bool isMouseLeftKey(Key k)
{
    return isCommandKey(k)
        && k.command >= 0x0040
        && k.command <= 0x004F;
}

bool isMouseWheelUpKey(Key k)
{
    return isCommandKey(k)
        && k.command >= 0x0050
        && k.command <= 0x005F;
}

bool isMouseWheelDownKey(Key k)
{
    return isCommandKey(k)
        && k.command >= 0x0060
        && k.command <= 0x006F;
}

bool isMouseCommandKey(Key k)
{
    return isCommandKey(k)
        && k.command >= 0x0010
        && k.command <= 0x007A;
}

Key apply_mod(Key k, uint8_t mod)
{
    Key new;
    new.modifiers = k.modifiers;
    new.modifiers |= mod;
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



/**********
 *  Keys
 *********/

const Key k_empty = {KEY_NONE, MOD_NONE, CMD_NONE};


const Key k_a = {KEY_A, MOD_NONE, CMD_NONE}; const Key k_A = {KEY_A, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_b = {KEY_B, MOD_NONE, CMD_NONE}; const Key k_B = {KEY_B, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_c = {KEY_C, MOD_NONE, CMD_NONE}; const Key k_C = {KEY_C, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_d = {KEY_D, MOD_NONE, CMD_NONE}; const Key k_D = {KEY_D, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_e = {KEY_E, MOD_NONE, CMD_NONE}; const Key k_E = {KEY_E, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_f = {KEY_F, MOD_NONE, CMD_NONE}; const Key k_F = {KEY_F, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_g = {KEY_G, MOD_NONE, CMD_NONE}; const Key k_G = {KEY_G, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_h = {KEY_H, MOD_NONE, CMD_NONE}; const Key k_H = {KEY_H, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_i = {KEY_I, MOD_NONE, CMD_NONE}; const Key k_I = {KEY_I, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_j = {KEY_J, MOD_NONE, CMD_NONE}; const Key k_J = {KEY_J, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_k = {KEY_K, MOD_NONE, CMD_NONE}; const Key k_K = {KEY_K, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_l = {KEY_L, MOD_NONE, CMD_NONE}; const Key k_L = {KEY_L, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_m = {KEY_M, MOD_NONE, CMD_NONE}; const Key k_M = {KEY_M, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_n = {KEY_N, MOD_NONE, CMD_NONE}; const Key k_N = {KEY_N, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_o = {KEY_O, MOD_NONE, CMD_NONE}; const Key k_O = {KEY_O, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_p = {KEY_P, MOD_NONE, CMD_NONE}; const Key k_P = {KEY_P, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_q = {KEY_Q, MOD_NONE, CMD_NONE}; const Key k_Q = {KEY_Q, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_r = {KEY_R, MOD_NONE, CMD_NONE}; const Key k_R = {KEY_R, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_s = {KEY_S, MOD_NONE, CMD_NONE}; const Key k_S = {KEY_S, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_t = {KEY_T, MOD_NONE, CMD_NONE}; const Key k_T = {KEY_T, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_u = {KEY_U, MOD_NONE, CMD_NONE}; const Key k_U = {KEY_U, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_v = {KEY_V, MOD_NONE, CMD_NONE}; const Key k_V = {KEY_V, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_w = {KEY_W, MOD_NONE, CMD_NONE}; const Key k_W = {KEY_W, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_x = {KEY_X, MOD_NONE, CMD_NONE}; const Key k_X = {KEY_X, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_y = {KEY_Y, MOD_NONE, CMD_NONE}; const Key k_Y = {KEY_Y, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_z = {KEY_Z, MOD_NONE, CMD_NONE}; const Key k_Z = {KEY_Z, MOD_LEFT_SHIFT, CMD_NONE};



const Key k_0 = {KEY_0, MOD_NONE, CMD_NONE};
const Key k_1 = {KEY_1, MOD_NONE, CMD_NONE};
const Key k_2 = {KEY_2, MOD_NONE, CMD_NONE};
const Key k_3 = {KEY_3, MOD_NONE, CMD_NONE};
const Key k_4 = {KEY_4, MOD_NONE, CMD_NONE};
const Key k_5 = {KEY_5, MOD_NONE, CMD_NONE};
const Key k_6 = {KEY_6, MOD_NONE, CMD_NONE};
const Key k_7 = {KEY_7, MOD_NONE, CMD_NONE};
const Key k_8 = {KEY_8, MOD_NONE, CMD_NONE};
const Key k_9 = {KEY_9, MOD_NONE, CMD_NONE};



const Key m_lctrl = {KEY_NONE, MOD_LEFT_CTRL, CMD_NONE};
const Key m_lshift = {KEY_NONE, MOD_LEFT_SHIFT, CMD_NONE};
const Key m_lalt = {KEY_NONE, MOD_LEFT_ALT, CMD_NONE};
const Key m_lsuper = {KEY_NONE, MOD_LEFT_SUPER, CMD_NONE};
const Key m_rctrl = {KEY_NONE, MOD_RIGHT_CTRL, CMD_NONE};
const Key m_rshift = {KEY_NONE, MOD_RIGHT_SHIFT, CMD_NONE};
const Key m_ralt = {KEY_NONE, MOD_RIGHT_ALT, CMD_NONE};
const Key m_rsuper = {KEY_NONE, MOD_RIGHT_SUPER, CMD_NONE};



const Key k_back_quote = {KEY_GRAVE_ACCENT, MOD_NONE, CMD_NONE};
const Key k_double_quote = {KEY_SINGLE_QUOTE, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_single_quote = {KEY_SINGLE_QUOTE, MOD_NONE, CMD_NONE};
const Key k_tilde = {KEY_GRAVE_ACCENT, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_bang = {KEY_1, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_at = {KEY_2, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_hash = {KEY_3, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_dollar = {KEY_4, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_percent = {KEY_5, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_caret = {KEY_6, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_ampersand = {KEY_7, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_asterisk = {KEY_8, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_hyphen = {KEY_HYPHEN, MOD_NONE, CMD_NONE};
const Key k_under_score = {KEY_HYPHEN, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_equal = {KEY_EQUAL, MOD_NONE, CMD_NONE};
const Key k_plus = {KEY_EQUAL, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_semicolon = {KEY_SEMICOLON, MOD_NONE, CMD_NONE};
const Key k_colon = {KEY_SEMICOLON, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_dot = {KEY_DOT, MOD_NONE, CMD_NONE};
const Key k_comma = {KEY_DOT, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_slash = {KEY_SLASH, MOD_NONE, CMD_NONE};
const Key k_question_mark = {KEY_SLASH, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_backslash = {KEY_BACKSLASH, MOD_NONE, CMD_NONE};
const Key k_pipe = {KEY_BACKSLASH, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_greater_than = {KEY_DOT, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_less_than = {KEY_COMMA, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_open_paren = {KEY_9, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_close_paren = {KEY_0, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_open_bracket = {KEY_OPEN_BRACKET, MOD_NONE, CMD_NONE};
const Key k_close_bracket = {KEY_CLOSE_BRACKET, MOD_NONE, CMD_NONE};
const Key k_open_brace = {KEY_OPEN_BRACKET, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_close_brace = {KEY_CLOSE_BRACKET, MOD_LEFT_SHIFT, CMD_NONE};



const Key k_enter = {KEY_ENTER, MOD_NONE, CMD_NONE};
const Key k_escape = {KEY_ESCAPE, MOD_NONE, CMD_NONE};
const Key k_backspace = {KEY_BACKSPACE, MOD_NONE, CMD_NONE};
const Key k_tab = {KEY_TAB, MOD_NONE, CMD_NONE};
const Key k_space = {KEY_SPACEBAR, MOD_NONE, CMD_NONE};
const Key k_print_screen = {KEY_PRINT_SCREEN, MOD_NONE, CMD_NONE};
const Key k_scroll_lock = {KEY_SCROLL_LOCK, MOD_NONE, CMD_NONE};
const Key k_pause = {KEY_PAUSE, MOD_NONE, CMD_NONE};
const Key k_insert = {KEY_INSERT, MOD_NONE, CMD_NONE};
const Key k_delete = {KEY_DELETE, MOD_NONE, CMD_NONE};
const Key k_home = {KEY_HOME, MOD_NONE, CMD_NONE};
const Key k_end = {KEY_END, MOD_NONE, CMD_NONE};
const Key k_pageup = {KEY_PAGE_UP, MOD_NONE, CMD_NONE};
const Key k_pagedown = {KEY_PAGE_DOWN, MOD_NONE, CMD_NONE};
const Key k_arrow_up = {KEY_UP_ARROW, MOD_NONE, CMD_NONE};
const Key k_arrow_down = {KEY_DOWN_ARROW, MOD_NONE, CMD_NONE};
const Key k_arrow_left = {KEY_LEFT_ARROW, MOD_NONE, CMD_NONE};
const Key k_arrow_right = {KEY_RIGHT_ARROW, MOD_NONE, CMD_NONE};
const Key k_f1 = {KEY_F1, MOD_NONE, CMD_NONE};
const Key k_f2 = {KEY_F2, MOD_NONE, CMD_NONE};
const Key k_f3 = {KEY_F3, MOD_NONE, CMD_NONE};
const Key k_f4 = {KEY_F4, MOD_NONE, CMD_NONE};
const Key k_f5 = {KEY_F5, MOD_NONE, CMD_NONE};
const Key k_f6 = {KEY_F6, MOD_NONE, CMD_NONE};
const Key k_f7 = {KEY_F7, MOD_NONE, CMD_NONE};
const Key k_f8 = {KEY_F8, MOD_NONE, CMD_NONE};
const Key k_f9 = {KEY_F9, MOD_NONE, CMD_NONE};
const Key k_f10 = {KEY_F10, MOD_NONE, CMD_NONE};
const Key k_f11 = {KEY_F11, MOD_NONE, CMD_NONE};
const Key k_f12 = {KEY_F12, MOD_NONE, CMD_NONE};



const Key c_layer_lock = {KEY_NONE, MOD_NONE, CMD_LOCK_LAYER};



/* Mouse */
const Key m_click_1 = {KEY_NONE, MOD_NONE, CMD_MOUSE_CLICK_1};
const Key m_click_2 = {KEY_NONE, MOD_NONE, CMD_MOUSE_CLICK_2};
const Key m_click_3 = {KEY_NONE, MOD_NONE, CMD_MOUSE_CLICK_3};
const Key m_click_4 = {KEY_NONE, MOD_NONE, CMD_MOUSE_CLICK_4};
const Key m_click_5 = {KEY_NONE, MOD_NONE, CMD_MOUSE_CLICK_5};

/* const Key m_up_1 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_1}; */
/* const Key m_up_2 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_2}; */
/* const Key m_up_3 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_3}; */
/* const Key m_up_4 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_4}; */
/* const Key m_up_5 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_5}; */
/* const Key m_up_6 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_6}; */
/* const Key m_up_7 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_7}; */
/* const Key m_up_8 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_8}; */
/* const Key m_up_9 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_9}; */
/* const Key m_up_10 = {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_10}; */
/* const Key m_up_15 = {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_15}; */
/* const Key m_up_20 = {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_20}; */
/* const Key m_up_25 = {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_25}; */
/* const Key m_up_30 = {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_30}; */
/* const Key m_up_35 = {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_35}; */
/* const Key m_up_40 = {KEY_NONE, MOD_NONE, CMD_MOUSE_UP_40}; */

/* const Key m_down_1 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_1}; */
/* const Key m_down_2 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_2}; */
/* const Key m_down_3 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_3}; */
/* const Key m_down_4 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_4}; */
/* const Key m_down_5 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_5}; */
/* const Key m_down_6 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_6}; */
/* const Key m_down_7 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_7}; */
/* const Key m_down_8 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_8}; */
/* const Key m_down_9 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_9}; */
/* const Key m_down_10 = {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_10}; */
/* const Key m_down_15 = {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_15}; */
/* const Key m_down_20 = {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_20}; */
/* const Key m_down_25 = {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_25}; */
/* const Key m_down_30 = {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_30}; */
/* const Key m_down_35 = {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_35}; */
/* const Key m_down_40 = {KEY_NONE, MOD_NONE, CMD_MOUSE_DOWN_40}; */

/* const Key m_right_1 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_1}; */
/* const Key m_right_2 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_2}; */
/* const Key m_right_3 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_3}; */
/* const Key m_right_4 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_4}; */
/* const Key m_right_5 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_5}; */
/* const Key m_right_6 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_6}; */
/* const Key m_right_7 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_7}; */
/* const Key m_right_8 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_8}; */
/* const Key m_right_9 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_9}; */
/* const Key m_right_10 = {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_10}; */
/* const Key m_right_15 = {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_15}; */
/* const Key m_right_20 = {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_20}; */
/* const Key m_right_25 = {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_25}; */
/* const Key m_right_30 = {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_30}; */
/* const Key m_right_35 = {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_35}; */
/* const Key m_right_40 = {KEY_NONE, MOD_NONE, CMD_MOUSE_RIGHT_40}; */

/* const Key m_left_1 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_1}; */
/* const Key m_left_2 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_2}; */
/* const Key m_left_3 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_3}; */
/* const Key m_left_4 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_4}; */
/* const Key m_left_5 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_5}; */
/* const Key m_left_6 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_6}; */
/* const Key m_left_7 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_7}; */
/* const Key m_left_8 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_8}; */
/* const Key m_left_9 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_9}; */
/* const Key m_left_10 = {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_10}; */
/* const Key m_left_15 = {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_15}; */
/* const Key m_left_20 = {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_20}; */
/* const Key m_left_25 = {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_25}; */
/* const Key m_left_30 = {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_30}; */
/* const Key m_left_35 = {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_35}; */
/* const Key m_left_40 = {KEY_NONE, MOD_NONE, CMD_MOUSE_LEFT_40}; */

/* const Key m_wheelup_1 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_1}; */
/* const Key m_wheelup_2 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_2}; */
/* const Key m_wheelup_3 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_3}; */
/* const Key m_wheelup_4 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_4}; */
/* const Key m_wheelup_5 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_5}; */
/* const Key m_wheelup_6 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_6}; */
/* const Key m_wheelup_7 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_7}; */
/* const Key m_wheelup_8 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_8}; */
/* const Key m_wheelup_9 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_9}; */
/* const Key m_wheelup_10 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_10}; */
/* const Key m_wheelup_15 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_15}; */
/* const Key m_wheelup_20 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_20}; */
/* const Key m_wheelup_25 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_25}; */
/* const Key m_wheelup_30 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_30}; */
/* const Key m_wheelup_35 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_35}; */
/* const Key m_wheelup_40 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELUP_40}; */

/* const Key m_wheeldown_1 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_1}; */
/* const Key m_wheeldown_2 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_2}; */
/* const Key m_wheeldown_3 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_3}; */
/* const Key m_wheeldown_4 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_4}; */
/* const Key m_wheeldown_5 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_5}; */
/* const Key m_wheeldown_6 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_6}; */
/* const Key m_wheeldown_7 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_7}; */
/* const Key m_wheeldown_8 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_8}; */
/* const Key m_wheeldown_9 =  {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_9}; */
/* const Key m_wheeldown_10 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_10}; */
/* const Key m_wheeldown_15 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_15}; */
/* const Key m_wheeldown_20 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_20}; */
/* const Key m_wheeldown_25 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_25}; */
/* const Key m_wheeldown_30 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_30}; */
/* const Key m_wheeldown_35 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_35}; */
/* const Key m_wheeldown_40 = {KEY_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN_40}; */

