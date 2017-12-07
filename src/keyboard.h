#ifndef KEYBOARD_H
#define KEYBOARD_H

#define NLAYERS 4

void execute(const Key keys[NKEYS]);

/* Selects a layer based on user commands
 */
void select_layer(const Key layers[NLAYERS][NROWS][NCOLS]);

/* Fill KEYS with the currently pressed keys in the current layer
 */
void map_layer(const Key layers[NLAYERS][NROWS][NCOLS], Key keys[NKEYS]);

/* Apply pressed modifiers to normal keys in KEYS array
 * of N pressed keys
 */
void apply_modifiers(Key keys[NKEYS]);

#endif // KEYBOARD_H
