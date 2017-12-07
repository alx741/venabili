#ifndef KEYBOARD_H
#define KEYBOARD_H

#define NLAYERS 4

void execute(const Key keys[NKEYS]);

void add_layer(const Key layer[NROWS][NCOLS]);

/* Selects a layer based on user commands
 */
void select_layer(void);

/* Fill KEYS with the currently pressed keys in the current layer
 */
void map_layer(Key keys[NKEYS]);

/* Apply pressed modifiers to normal keys in KEYS array
 * of N pressed keys
 */
void apply_modifiers(Key keys[NKEYS]);

#endif // KEYBOARD_H
