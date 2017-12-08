#include <stdint.h>
#include "sensing.h"
#include "usb_keys.h"
#include "usb_keyboard.h"
#include "keys.h"
#include "keyboard.h"

static Key LAYERS[NLAYERS][NROWS][NCOLS];
static int N_LAYERS = 0;

static int CURRENT_LAYER = 0;
static int CURRENT_LOCKED_LAYER = 0;
static bool LAYER_LOCKED = false;

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
    uint8_t mods = 0;
    uint8_t keycodes[6] = {0};

    // Combine modifiers
    for (int i = 0; i < n; i++)
    {
        mods |= k[i].modifiers;
        keycodes[i] = k[i].usb_keycode;
    }
    report_6_keys(mods, keycodes);
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


void add_layer(const Key layer[NROWS][NCOLS])
{
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            LAYERS[N_LAYERS][i][j] = layer[i][j];
        }
    }
    N_LAYERS++;
}

int get_layer_selection(uint16_t current_layer,
                        const Key layers[NLAYERS][NROWS][NCOLS])
{
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            Key k = layers[current_layer][i][j];
            if (isLayerSelectionKey(k) && currently_pressed(i, j))
            {
                return get_layer_selection(k.command - 0x00FF - 1, layers);
            }
        }
    }

    // If no layer selection key is pressed, the layer remains the same
    return current_layer;
}


void select_layer()
{
    if (LAYER_LOCKED)
    {
        CURRENT_LAYER = get_layer_selection(CURRENT_LOCKED_LAYER, LAYERS);
    }
    else
    {
        // Start layer evaluation from layer 0
        CURRENT_LAYER = get_layer_selection(0, LAYERS);
    }
}


void map_layer(Key keys[NKEYS])
{
    int i = 0;
    Key_coordinate *k = &PRESSED_KEYS[0];

    while (! isNullCoordinate(*k))
    {
        keys[i++] = LAYERS[CURRENT_LAYER][k->i][k->j];
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
