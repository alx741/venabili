#include <stdint.h>
#include "sensing.h"
#include "usb_keys.h"
#include "usb_keyboard.h"
#include "keys.h"
#include "keyboard.h"

int CURRENT_LAYER = 0;
int CURRENT_LOCKED_LAYER = 0;
bool LAYER_LOCKED = false;

void handle_6_normal_keys(Key k[6], int n);
void handle_command_keys(Key k);
void lock_layer(void);
void unlock_layer(void);

// USB can handle up to 6KRO
#define XKRO  6

void execute(const Key keys[NKEYS])
{
    Key normal_keys[XKRO] = {0};
    int n_normal_keys = 0;

    for (int i = 0; i < N_PRESSED; i++)
    {
        Key k = keys[i];

        if (isEmptyKey(k))
        {
            // Ignore it
        }
        // Modifiers are already applied to normal keys, so ignore them
        else if (isNormalKey(k) && !isModifierKey(k))
        {
            if (n_normal_keys < XKRO)
            {
                normal_keys[n_normal_keys++] = k;
            }
        }
        else if (isCommandKey(k))
        {
            handle_command_keys(k);
        }
    }

    handle_6_normal_keys(normal_keys, n_normal_keys);
}

void handle_6_normal_keys(Key k[6], int n)
{
    // FIXME: Use USB 6KRO
    uint8_t mods = 0;
    uint8_t keycodes[6] = {0};

    // Combine modifiers
    for (int i = 0; i < n; i++)
    {
        mods |= k[i].modifiers;
        keycodes[i] = k[i].usb_keycode;
    }
    // report_upto_6_keypress(mods, keycodes);

    /* report_keypress(k.modifiers, k.usb_keycode); */
}

void handle_command_keys(Key k)
{
    if (areKeysEqual(k, c_layer_lock))
    {
        // Togle layer locking
        if (LAYER_LOCKED)
        {
            unlock_layer();
        }
        else
        {
            lock_layer();
        }
    }
}


int get_layer_selection(uint16_t current_layer,
                        const Key layers[NLAYERS][NROWS][NCOLS])
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


void select_layer(const Key layers[NLAYERS][NROWS][NCOLS])
{
    if (LAYER_LOCKED)
    {
        CURRENT_LAYER = get_layer_selection(CURRENT_LOCKED_LAYER, layers);
    }
    else
    {
        // Start layer evaluation from layer 0
        CURRENT_LAYER = get_layer_selection(0, layers);
    }
}


void map_layer(const Key layers[NLAYERS][NROWS][NCOLS], Key keys[NKEYS])
{
    int i = 0;
    Key_coordinate *k = &PRESSED_KEYS[0];

    while (! isNullCoordinate(*k))
    {
        keys[i++] = layers[CURRENT_LAYER][k->i][k->j];
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


void lock_layer()
{
    CURRENT_LOCKED_LAYER = CURRENT_LAYER;
    LAYER_LOCKED = true;
}

void unlock_layer()
{
    CURRENT_LOCKED_LAYER = 0;
    LAYER_LOCKED = false;
}
