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
#define CMD_NONE               0x0000

// Layers
#define CMD_LOCK_LAYER         0x0001
// Reserved 0x0002 - 0x000F

// Mouse
#define CMD_MOUSE_UP_1           0x0010
#define CMD_MOUSE_UP_2           0x0011
#define CMD_MOUSE_UP_3           0x0012
#define CMD_MOUSE_UP_4           0x0013
#define CMD_MOUSE_UP_5           0x0014
#define CMD_MOUSE_UP_6           0x0015
#define CMD_MOUSE_UP_7           0x0016
#define CMD_MOUSE_UP_8           0x0017
#define CMD_MOUSE_UP_9           0x0018
#define CMD_MOUSE_UP_10          0x0019
#define CMD_MOUSE_UP_15          0x001A
#define CMD_MOUSE_UP_20          0x001B
#define CMD_MOUSE_UP_25          0x001C
#define CMD_MOUSE_UP_30          0x001D
#define CMD_MOUSE_UP_35          0x001E
#define CMD_MOUSE_UP_40          0x001F

#define CMD_MOUSE_DOWN_1         0x0020
#define CMD_MOUSE_DOWN_2         0x0021
#define CMD_MOUSE_DOWN_3         0x0022
#define CMD_MOUSE_DOWN_4         0x0023
#define CMD_MOUSE_DOWN_5         0x0024
#define CMD_MOUSE_DOWN_6         0x0025
#define CMD_MOUSE_DOWN_7         0x0026
#define CMD_MOUSE_DOWN_8         0x0027
#define CMD_MOUSE_DOWN_9         0x0028
#define CMD_MOUSE_DOWN_10        0x0029
#define CMD_MOUSE_DOWN_15        0x002A
#define CMD_MOUSE_DOWN_20        0x002B
#define CMD_MOUSE_DOWN_25        0x002C
#define CMD_MOUSE_DOWN_30        0x002D
#define CMD_MOUSE_DOWN_35        0x002E
#define CMD_MOUSE_DOWN_40        0x002F

#define CMD_MOUSE_LEFT_1         0x0030
#define CMD_MOUSE_LEFT_2         0x0031
#define CMD_MOUSE_LEFT_3         0x0032
#define CMD_MOUSE_LEFT_4         0x0033
#define CMD_MOUSE_LEFT_5         0x0034
#define CMD_MOUSE_LEFT_6         0x0035
#define CMD_MOUSE_LEFT_7         0x0036
#define CMD_MOUSE_LEFT_8         0x0037
#define CMD_MOUSE_LEFT_9         0x0038
#define CMD_MOUSE_LEFT_10        0x0039
#define CMD_MOUSE_LEFT_15        0x003A
#define CMD_MOUSE_LEFT_20        0x003B
#define CMD_MOUSE_LEFT_25        0x003C
#define CMD_MOUSE_LEFT_30        0x003D
#define CMD_MOUSE_LEFT_35        0x003E
#define CMD_MOUSE_LEFT_40        0x003F

#define CMD_MOUSE_RIGHT_1        0x0040
#define CMD_MOUSE_RIGHT_2        0x0041
#define CMD_MOUSE_RIGHT_3        0x0042
#define CMD_MOUSE_RIGHT_4        0x0043
#define CMD_MOUSE_RIGHT_5        0x0044
#define CMD_MOUSE_RIGHT_6        0x0045
#define CMD_MOUSE_RIGHT_7        0x0046
#define CMD_MOUSE_RIGHT_8        0x0047
#define CMD_MOUSE_RIGHT_9        0x0048
#define CMD_MOUSE_RIGHT_10       0x0049
#define CMD_MOUSE_RIGHT_15       0x004A
#define CMD_MOUSE_RIGHT_20       0x004B
#define CMD_MOUSE_RIGHT_25       0x004C
#define CMD_MOUSE_RIGHT_30       0x004D
#define CMD_MOUSE_RIGHT_35       0x004E
#define CMD_MOUSE_RIGHT_40       0x004F

#define CMD_MOUSE_WHEELUP_1      0x0050
#define CMD_MOUSE_WHEELUP_2      0x0051
#define CMD_MOUSE_WHEELUP_3      0x0052
#define CMD_MOUSE_WHEELUP_4      0x0053
#define CMD_MOUSE_WHEELUP_5      0x0054
#define CMD_MOUSE_WHEELUP_6      0x0055
#define CMD_MOUSE_WHEELUP_7      0x0056
#define CMD_MOUSE_WHEELUP_8      0x0057
#define CMD_MOUSE_WHEELUP_9      0x0058
#define CMD_MOUSE_WHEELUP_10     0x0059
#define CMD_MOUSE_WHEELUP_15     0x005A
#define CMD_MOUSE_WHEELUP_20     0x005B
#define CMD_MOUSE_WHEELUP_25     0x005C
#define CMD_MOUSE_WHEELUP_30     0x005D
#define CMD_MOUSE_WHEELUP_35     0x005E
#define CMD_MOUSE_WHEELUP_40     0x005F

#define CMD_MOUSE_WHEELDOWN_1    0x0060
#define CMD_MOUSE_WHEELDOWN_2    0x0061
#define CMD_MOUSE_WHEELDOWN_3    0x0062
#define CMD_MOUSE_WHEELDOWN_4    0x0063
#define CMD_MOUSE_WHEELDOWN_5    0x0064
#define CMD_MOUSE_WHEELDOWN_6    0x0065
#define CMD_MOUSE_WHEELDOWN_7    0x0066
#define CMD_MOUSE_WHEELDOWN_8    0x0067
#define CMD_MOUSE_WHEELDOWN_9    0x0068
#define CMD_MOUSE_WHEELDOWN_10   0x0069
#define CMD_MOUSE_WHEELDOWN_15   0x006A
#define CMD_MOUSE_WHEELDOWN_20   0x006B
#define CMD_MOUSE_WHEELDOWN_25   0x006C
#define CMD_MOUSE_WHEELDOWN_30   0x006D
#define CMD_MOUSE_WHEELDOWN_35   0x006E
#define CMD_MOUSE_WHEELDOWN_40   0x006F

#define CMD_MOUSE_CLICK_1        0x0016
#define CMD_MOUSE_CLICK_2        0x0017
#define CMD_MOUSE_CLICK_3        0x0018
#define CMD_MOUSE_CLICK_4        0x0019
#define CMD_MOUSE_CLICK_5        0x001A
// ... Up to 0x00FF

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


/* Mouse movement macro
 *
 * M(movement, speed)
 *
 * Posible movements are:
 *      m_up, m_down, m_right, m_left, m_wheel_up, m_wheel_down
 *
 * Posible speeds are:
 *      1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40
 */
#define M(m_command, speed) m_command##_##speed


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


/* Tell if a key is a mouse command key
 */
bool isMouseCommandKey(Key k);


/* Apply modifiers to a key
 *
 * e.g.   Rctrl(Lshift(k_a)) = CTRL + SHIFT + a
 */
Key Lctrl(Key k);       Key Rctrl(Key k);
Key Lshift(Key k);      Key Rshift(Key k);
Key Lalt(Key k);        Key Ralt(Key k);
Key Lsuper(Key k);      Key Rsuper(Key k);






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
 *      |-- Layers
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
extern const Key     m_lctrl;
extern const Key     m_lshift;
extern const Key     m_lalt;
extern const Key     m_lsuper;
extern const Key     m_rctrl;
extern const Key     m_rshift;
extern const Key     m_ralt;
extern const Key     m_rsuper;


/* Symbols */
extern const Key     k_back_quote;
extern const Key     k_double_quote;
extern const Key     k_single_quote;
extern const Key     k_tilde;
extern const Key     k_bang;
extern const Key     k_at;
extern const Key     k_hash;
extern const Key     k_dollar;
extern const Key     k_percent;
extern const Key     k_caret;
extern const Key     k_ampersand;
extern const Key     k_asterisk;
extern const Key     k_hyphen;
extern const Key     k_under_score;
extern const Key     k_equal;
extern const Key     k_plus;
extern const Key     k_semicolon;
extern const Key     k_colon;
extern const Key     k_dot;
extern const Key     k_comma;
extern const Key     k_slash;
extern const Key     k_question_mark;
extern const Key     k_backslash;
extern const Key     k_pipe;
extern const Key     k_greater_than;
extern const Key     k_less_than;
extern const Key     k_open_paren;
extern const Key     k_close_paren;
extern const Key     k_open_bracket;
extern const Key     k_close_bracket;
extern const Key     k_open_brace;
extern const Key     k_close_brace;


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


/* Mouse */
extern const Key    m_click_1,  m_click_2,  m_click_3,  m_click_4,  m_click_5;

// For mouse movement use the M(movement, speed) macro
extern const Key
    m_up_1, m_up_2, m_up_3, m_up_4, m_up_5,
    m_up_6, m_up_7, m_up_8, m_up_9, m_up_10,
    m_up_15, m_up_20, m_up_25, m_up_30, m_up_35, m_up_40;

extern const Key
    m_down_1, m_down_2, m_down_3, m_down_4, m_down_5,
    m_down_6, m_down_7, m_down_8, m_down_9, m_down_10,
    m_down_15, m_down_20, m_down_25, m_down_30, m_down_35, m_down_40;

extern const Key
    m_right_1, m_right_2, m_right_3, m_right_4, m_right_5,
    m_right_6, m_right_7, m_right_8, m_right_9, m_right_10,
    m_right_15, m_right_20, m_right_25, m_right_30, m_right_35, m_right_40;

extern const Key
    m_left_1, m_left_2, m_left_3, m_left_4, m_left_5,
    m_left_6, m_left_7, m_left_8, m_left_9, m_left_10,
    m_left_15, m_left_20, m_left_25, m_left_30, m_left_35, m_left_40;

extern const Key
    m_wheelup_1, m_wheelup_2, m_wheelup_3, m_wheelup_4, m_wheelup_5,
    m_wheelup_6, m_wheelup_7, m_wheelup_8, m_wheelup_9, m_wheelup_10,
    m_wheelup_15, m_wheelup_20, m_wheelup_25, m_wheelup_30, m_wheelup_35, m_wheelup_40;

extern const Key
    m_wheeldown_1, m_wheeldown_2, m_wheeldown_3, m_wheeldown_4, m_wheeldown_5,
    m_wheeldown_6, m_wheeldown_7, m_wheeldown_8, m_wheeldown_9, m_wheeldown_10,
    m_wheeldown_15, m_wheeldown_20, m_wheeldown_25, m_wheeldown_30, m_wheeldown_35, m_wheeldown_40;

#endif // KEYS_H
