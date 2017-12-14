#ifndef KEYBOARD_H
#define KEYBOARD_H

#define NLAYERS 4
#define ENABLE_DOUBLE_SHIFT_CAPS_LOCK

void keyboard_init(void);

void add_layer(const Key layer[NROWS][NCOLS]);

/* Selects a layer based on user commands
 */
void select_layer(void);

/* Fill KEYS with the currently pressed keys in the current layer
 */
int map_layer(Key keys[NKEYS]);

/* Apply pressed modifiers to normal keys in KEYS array
 * of N pressed keys
 */
void apply_modifiers(Key keys[NKEYS], int n);

/* Execute key pulsations in current layer
 */
void execute(const Key keys[NKEYS], int n);


#endif // KEYBOARD_H
