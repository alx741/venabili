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


const Key k_at = {KEY_2, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_space = {KEY_SPACEBAR, MOD_NONE, CMD_NONE};


const Key k_lctrl = {KEY_NONE, MOD_LEFT_CTRL, CMD_NONE};
const Key k_lshift = {KEY_NONE, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_lalt = {KEY_NONE, MOD_LEFT_ALT, CMD_NONE};
const Key k_lsuper = {KEY_NONE, MOD_LEFT_SUPER, CMD_NONE};
const Key k_rctrl = {KEY_NONE, MOD_RIGHT_CTRL, CMD_NONE};
const Key k_rshift = {KEY_NONE, MOD_RIGHT_SHIFT, CMD_NONE};
const Key k_ralt = {KEY_NONE, MOD_RIGHT_ALT, CMD_NONE};
const Key k_rsuper = {KEY_NONE, MOD_RIGHT_SUPER, CMD_NONE};


const Key c_layer_lock = {KEY_NONE, MOD_NONE, CMD_LOCK_LAYER};
