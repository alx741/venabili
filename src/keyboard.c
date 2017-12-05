#define NLAYERS 4

void execute(Key k)
{
    if (isNormalKey(k))
    {
        report_keypress(usbd_dev, k.modifiers, k.usb_keycode);
    }
}


/* Should be given the default layer or the currently toggled layer
 *
 * Returns the selected layer number
 */
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

/* Get pressed modifiers in LAYER
 */
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


/* Infect keys in given LAYER with MODS
 */
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


#ifdef DEBUG
void report_layer(layer)
{
    if (layer == 0)
    {
        report_keypress(usbd_dev, MOD_NONE, KEY_0);
    }
    else if (layer == 1)
    {
        report_keypress(usbd_dev, MOD_NONE, KEY_1);
    }
    else if (layer == 2)
    {
        report_keypress(usbd_dev, MOD_NONE, KEY_2);
    }
    else if (layer == 3)
    {
        report_keypress(usbd_dev, MOD_NONE, KEY_3);
    }

}
#endif


