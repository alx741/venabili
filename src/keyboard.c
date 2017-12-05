#include <stdint.h>
#include "sensing.h"
#include "usb_keys.h"
#include "usb_keyboard.h"
#include "keys.h"
#include "keyboard.h"

void execute(Key k)
{
    if (isNormalKey(k))
    {
        report_keypress( k.modifiers, k.usb_keycode);
    }
}


int get_layer_selection(uint16_t current_layer, const Key layers[NLAYERS][NROWS][NCOLS])
{
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            Key k = layers[current_layer][i][j];
            if (isLayerSelectionKey(k) && isPressed(KMAT_STATE, i, j))
            {
                return get_layer_selection(k.command - 0x00FF - 1, layers);
            }
        }
    }

    // If no layer selection key is pressed, the layer remains the same
    return current_layer;
}

uint8_t get_modifiers(const Key layer[NROWS][NCOLS])
{
    uint8_t mods = MOD_NONE;

    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            Key k = layer[i][j];
            if (isModifierKey(k) && isPressed(KMAT_STATE, i, j))
            {
                mods |= k.modifiers;
            }
        }
    }

    return mods;
}


void infect_with_modifiers(uint16_t mods, Key layer[NROWS][NCOLS])
{
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            Key k = layer[i][j];
            if (isNormalKey(k) && !isModifierKey(k) && isPressed(KMAT_STATE, i, j))
            {
                k.modifiers |= mods;
            }
        }
    }
}
