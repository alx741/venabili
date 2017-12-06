#ifndef KEYBOARD_H
#define KEYBOARD_H

#define NLAYERS 4

void execute(const Key keys[NKEYS], int n);

/* Should be given the default layer or the currently toggled layer
 *
 * Returns the selected layer number
 */
int get_layer_selection(uint16_t current_layer, const Key layers[NLAYERS][NROWS][NCOLS]);

/* Fill KEYS with the currently pressed keys in the LAYER
 */
void map_layer(const Key layer[NROWS][NCOLS], Key keys[NKEYS]);

/* Apply pressed modifiers to normal keys in KEYS array
 * of N pressed keys
 */
void apply_modifiers(Key keys[NKEYS], int n);

#endif // KEYBOARD_H
