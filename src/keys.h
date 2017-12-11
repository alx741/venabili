#ifndef KEYS_H
#define KEYS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* A Key might be either a normal keyboard symbol with its applied modifiers
 * or a special command
 */
typedef struct
{
    // Normal Key
    uint8_t usb_keycode;
    uint8_t modifiers;

    // Command key
    uint16_t command;
} Key;

/* Mapkey is used to map keys in layers
 */
typedef struct
{
    Key press; // Key when pressed
    Key hold; // Key when held
} Mapkey;


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


/* Tell if Mapkey has press key functionality
 */
bool hasPressKey(Mapkey mk);

/* Tell if Mapkey has hold key functionality
 */
bool hasHoldKey(Mapkey mk);


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

/* Tell if two keys are equal
 */
bool areKeysEqual(Key k1, Key k2);



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
//                Lower case     Upper case
extern const Key     k_a,           k_A;
extern const Key     k_b,           k_B;
extern const Key     k_c,           k_C;
extern const Key     k_d,           k_D;
extern const Key     k_e,           k_E;
extern const Key     k_f,           k_F;
extern const Key     k_g,           k_G;
extern const Key     k_h,           k_H;
extern const Key     k_i,           k_I;
extern const Key     k_j,           k_J;
extern const Key     k_k,           k_K;
extern const Key     k_l,           k_L;
extern const Key     k_m,           k_M;
extern const Key     k_n,           k_N;
extern const Key     k_o,           k_O;
extern const Key     k_p,           k_P;
extern const Key     k_q,           k_Q;
extern const Key     k_r,           k_R;
extern const Key     k_s,           k_S;
extern const Key     k_t,           k_T;
extern const Key     k_u,           k_U;
extern const Key     k_v,           k_V;
extern const Key     k_w,           k_W;
extern const Key     k_x,           k_X;
extern const Key     k_y,           k_Y;
extern const Key     k_z,           k_Z;


/* Numbers */
extern const Key     k_0;
extern const Key     k_1;
extern const Key     k_2;
extern const Key     k_3;
extern const Key     k_4;
extern const Key     k_5;
extern const Key     k_6;
extern const Key     k_7;
extern const Key     k_8;
extern const Key     k_9;


/* Modifiers */
extern const Key     k_lctrl;
extern const Key     k_lshift;
extern const Key     k_lalt;
extern const Key     k_lsuper;
extern const Key     k_rctrl;
extern const Key     k_rshift;
extern const Key     k_ralt;
extern const Key     k_rsuper;


/* Symbols */
extern const Key     k_at;


/* Non-printables */
extern const Key     k_enter;
extern const Key     k_escape;
extern const Key     k_backspace;
extern const Key     k_tab;
extern const Key     k_space;

extern const Key     k_print_screen;
extern const Key     k_scroll_lock;
extern const Key     k_pause;
extern const Key     k_insert;
extern const Key     k_delete;
extern const Key     k_home;
extern const Key     k_end;
extern const Key     k_pageup;
extern const Key     k_pagedown;
extern const Key     k_arrow_up;
extern const Key     k_arrow_down;
extern const Key     k_arrow_left;
extern const Key     k_arrow_right;

extern const Key     k_f1;
extern const Key     k_f2;
extern const Key     k_f3;
extern const Key     k_f4;
extern const Key     k_f5;
extern const Key     k_f6;
extern const Key     k_f7;
extern const Key     k_f8;
extern const Key     k_f9;
extern const Key     k_f10;
extern const Key     k_f11;
extern const Key     k_f12;


/***********
 * Commands
 ***********/

/* Layers */
// For layer selection use the LS(n) macro
extern const Key    c_layer_lock;


#endif // KEYS_H
