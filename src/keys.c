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
bool isMouseCommandKey(Key k)
{
    return isCommandKey(k)
        && k.command >= 0x0010
        && k.command <= 0x0074;
}

bool isMouseMovementKey(Key k)
{
    return isMouseCommandKey(k)
        && k.command >= 0x0010
        && k.command <= 0x006F;
}

bool isMouseClickKey(Key k)
{
    return isMouseCommandKey(k)
        && k.command >= 0x0070
        && k.command <= 0x0074;
}

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

uint8_t getMouseMovementSpeed(Key k)
{
    // Movement speed is in the first nibble
    return k.command & 0x000F;
}

uint8_t getMouseClickButton(Key k)
{
    // Click button is in the first nibble
    return k.command & 0x000F;
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


#define mkNormalKey(keycode) {keycode, MOD_NONE, MOD_NONE, CMD_NONE}
#define mkNormalShiftedKey(keycode) {keycode, MOD_LEFT_SHIFT, MOD_NONE, CMD_NONE}
#define mkCommandKey(command) {KEY_NONE, MOD_NONE, MOD_NONE, command}


/**********
 *  Keys
 *********/

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


const Key c_layer_lock = mkCommandKey(CMD_LOCK_LAYER);

const Key m_click_1 = mkCommandKey(CMD_MOUSE_CLICK_1);
const Key m_click_2 = mkCommandKey(CMD_MOUSE_CLICK_2);
const Key m_click_3 = mkCommandKey(CMD_MOUSE_CLICK_3);
const Key m_click_4 = mkCommandKey(CMD_MOUSE_CLICK_4);
const Key m_click_5 = mkCommandKey(CMD_MOUSE_CLICK_5);
