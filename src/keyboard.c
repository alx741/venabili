#include <stdint.h>
#include "sensing.h"
#include "usb_keys.h"
#include "usb_keyboard.h"
#include "keys.h"
#include "keyboard.h"

void execute(const Key keys[NKEYS])
{
    for (int i = 0; i < N_PRESSED; i++)
    {
        Key k = keys[i];
        if (isNormalKey(k))
        {
            // FIXME: Use USB 6KRO
            report_keypress(k.modifiers, k.usb_keycode);
        }
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

void map_layer(const Key layer[NROWS][NCOLS], Key keys[NKEYS])
{
    int i = 0;
    Key_coordinate* k = &PRESSED_KEYS[0];

    while (! isNullCoordinate(*k))
    {
        keys[i++] = layer[k->i][k->j];
        k++;
    }
}


uint8_t retrieve_modifiers(Key keys[NKEYS])
{
    uint8_t mods = MOD_NONE;
    for (int i = 0; i < N_PRESSED; i++)
    {
        if (isModifierKey(keys[i]))
        {
            mods |= keys[i].modifiers;
        }
    }
    return mods;
}


void apply_modifiers(Key keys[NKEYS])
{
    uint8_t mods = retrieve_modifiers(keys);
    for (int i = 0; i < N_PRESSED; i++)
    {
        if (isNormalKey(keys[i]))
        {
            keys[i].modifiers |= mods;
        }
    }
}
