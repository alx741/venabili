#ifndef KEYS_H
#define KEYS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

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
#define CMD_NONE             0x0000
#define CMD_LOCK_LAYER       0x0001
/* #define CMD_MOUSE_CLICK_1  0x0002 */
// ...
// #define  CMD_something  0x00FF

// Use the LS(n) macro for Layer Selection
#define _LS_FIRST 0x0100
#define _LS_LAST  0xFF00

/* Layer selection macro command
 *
 * LS(0) is the first (main) layer
 *
 * Up to 256 layers
 */
#define LS(n) {KEY_NONE, MOD_NONE, _LS_FIRST + n}



/* Tell if a KEY is normal
 * It's not a command key
 */
bool isNormalKey(Key k);

/* Tell if a KEY is a command
 */
bool isCommandKey(Key k);

/* Tell if a KEY is a layer selection command
 */
bool isLayerSelectionKey(Key k);

/* Tell if a KEY is a modifier key
 */
bool isModifierKey(Key k);

/* Tell if a KEY is a "empty"
 * An "empty" key does nothing
 */
bool isEmptyKey(Key k);



/* ****************************
 *        Predefined keys
 *        ---------------
 *
 *   - Keys (prefix: k_)
 *      |-- Special
 *      |-- Letters
 *      |-- Numbers
 *      |-- Symbols
 *      |-- Non-printables
 *      |-- Modifiers
 *
 *   - Commands (prefix: c_)
 *      |-- Mouse (prefix: m_)
 *
 *
 * ****************************
 */


/**********
 *  Keys
 *********/

/* Special */
extern const Key     k_empty;

/* Letters */
extern const Key     k_a;
extern const Key     k_A;
extern const Key     k_b;
extern const Key     k_B;
extern const Key     k_c;
extern const Key     k_C;
extern const Key     k_d;
extern const Key     k_D;

/* Symbols */
extern const Key     k_at;

/* Non-printables */
extern const Key     k_space;

/* Modifiers */
extern const Key     k_lctrl;
extern const Key     k_rshift;
// ...


/***********
 * Commands
 ***********/

/* Layers */
// For layer selection use the LS(n) macro
extern const Key    c_layer_lock;


#endif // KEYS_H
