#ifndef KEYBOARD_H
#define KEYBOARD_H

#define NLAYERS 4

/* Should be given the default layer or the currently toggled layer
 *
 * Returns the selected layer number
 */
int get_layer_selection(uint16_t current_layer, const Key layers[NLAYERS][NROWS][NCOLS]);

/* Get pressed modifiers in LAYER
 */
uint8_t get_modifiers(const Key layer[NROWS][NCOLS]);

/* Infect keys in given LAYER with MODS
 */
void infect_with_modifiers(uint16_t mods, Key layer[NROWS][NCOLS]);

void report_layer(layer);

#endif // KEYBOARD_H
