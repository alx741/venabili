#ifndef KEYS_H
#define KEYS_H

/* A KEY might be either a normal keyboard symbol with its applied modifiers
 * or a special command
 */
typedef struct
{
    uint8_t usb_keycode;
    uint8_t modifiers;
    uint16_t command;
} Key;



/* Posible special commands
 */
#define CMD_NONE           0x0000
#define CMD_MOUSE_CLICK_1  0x0001
// ...
// #define  CMD_something  0x00FF

// Use the LS(n) macro for Layer Selection
#define _LS_FIRST 0x0100
#define _LS_LAST  0xFF00

/* Layer selection macro command
 *
 * LS(0) is the first (main) layer
 *
 * Up to 64 layers (0 - 63)
 */
#define LS(n) {KEY_NONE, MOD_NONE, _LS_FIRST + n}




bool isNormalKey(Key k);
bool isCommandKey(Key k);
bool isLayerSelectionKey(Key k);
bool isModifierKey(Key k);
bool isHoleKey(Key k);


/* Predefined keys
 */
const Key k_hole = {KEY_NONE, MOD_NONE, CMD_NONE};
const Key k_a = {KEY_A, MOD_NONE, CMD_NONE};
const Key k_A = {KEY_A, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_c = {KEY_C, MOD_NONE, CMD_NONE};
const Key k_at = {KEY_2, MOD_LEFT_SHIFT, CMD_NONE};
const Key k_space = {KEY_SPACEBAR, MOD_NONE, CMD_NONE};
const Key k_lctrl = {KEY_NONE, MOD_LEFT_CTRL, CMD_NONE};
const Key k_rshift = {KEY_NONE, MOD_RIGHT_SHIFT, CMD_NONE};
// ...

#endif // KEYS_H
