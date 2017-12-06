#include "usb_keys.h"
#include "keys.h"

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

const Key k_empty = {KEY_NONE, MOD_NONE, CMD_NONE};
const Key k_a = {KEY_A, MOD_NONE, CMD_NONE};
const Key k_A = {KEY_A, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_b = {KEY_B, MOD_NONE, CMD_NONE};
const Key k_B = {KEY_B, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_c = {KEY_C, MOD_NONE, CMD_NONE};
const Key k_C = {KEY_C, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_d = {KEY_D, MOD_NONE, CMD_NONE};
const Key k_D = {KEY_D, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_at = {KEY_2, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_space = {KEY_SPACEBAR, MOD_NONE, CMD_NONE};
const Key k_lctrl = {KEY_NONE, MOD_LEFT_CTRL, CMD_NONE};
const Key k_rshift = {KEY_NONE, MOD_RIGHT_SHIFT, CMD_NONE};
// ...

extern const Key c_layer_lock = {KEY_NONE, MOD_NONE, CMD_LOCK_LAYER};
