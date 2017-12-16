#ifndef KEYS_H
#define KEYS_H

#include "keys_internal.h"

/* Layer selection macro command
 *
 * LS(0) is the first (main) layer
 *
 * Up to 256 layers. From 1 to 256
 */
#define LS(n) {KEY_NONE, MOD_NONE, MOD_NONE, LS_FIRST + n}


/* Mouse movement macros
 *
 * Valid speeds are between 0 and 15
 */
#define MU(speed)  { KEY_NONE, MOD_NONE, MOD_NONE, CMD_MOUSE_UP + speed }
#define MD(speed)  { KEY_NONE, MOD_NONE, MOD_NONE, CMD_MOUSE_DOWN + speed }
#define MR(speed)  { KEY_NONE, MOD_NONE, MOD_NONE, CMD_MOUSE_RIGHT + speed }
#define ML(speed)  { KEY_NONE, MOD_NONE, MOD_NONE, CMD_MOUSE_LEFT + speed }
#define MWU(speed) { KEY_NONE, MOD_NONE, MOD_NONE, CMD_MOUSE_WHEELUP + speed }
#define MWD(speed) { KEY_NONE, MOD_NONE, MOD_NONE, CMD_MOUSE_WHEELDOWN + speed }


/* Macro macros ¯\_(ツ)_/¯
 *
 * Up to 27 macros. Valid ids are between 0 and 26
 */
#define MACRO(id) { KEY_NONE, MOD_NONE, MOD_NONE, CMD_MACRO_FIRST + id}


/* Apply modifiers to a key
 *
 * e.g.   Rctrl(Lshift(k_a)) = CTRL + SHIFT + a
 */
Key Lctrl(Key k);       Key Rctrl(Key k);
Key Lshift(Key k);      Key Rshift(Key k);
Key Lalt(Key k);        Key Ralt(Key k);
Key Lsuper(Key k);      Key Rsuper(Key k);


/* Make a key behave like a modifier when held
 *
 * e.g.  HRshift(k_a) = 'a' when tapped, RShift when held
 */
Key HLctrl(Key k);       Key HRctrl(Key k);
Key HLshift(Key k);      Key HRshift(Key k);
Key HLalt(Key k);        Key HRalt(Key k);
Key HLsuper(Key k);      Key HRsuper(Key k);



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
extern const Key     k_back_quote,           k_semicolon;
extern const Key     k_double_quote,         k_colon;
extern const Key     k_single_quote,         k_dot;
extern const Key     k_tilde,                k_comma;
extern const Key     k_bang,                 k_slash;
extern const Key     k_at,                   k_question_mark;
extern const Key     k_hash,                 k_backslash;
extern const Key     k_dollar,               k_pipe;
extern const Key     k_percent,              k_greater_than;
extern const Key     k_caret,                k_less_than;
extern const Key     k_ampersand,            k_open_paren;
extern const Key     k_asterisk,             k_close_paren;
extern const Key     k_hyphen,               k_open_bracket;
extern const Key     k_under_score,          k_close_bracket;
extern const Key     k_equal,                k_open_brace;
extern const Key     k_plus,                 k_close_brace;


/* Non-printables */
extern const Key     k_print_screen,         k_f1,         k_enter;
extern const Key     k_scroll_lock,          k_f2,         k_escape;
extern const Key     k_pause,                k_f3,         k_backspace;
extern const Key     k_insert,               k_f4,         k_tab;
extern const Key     k_delete,               k_f5,         k_space;
extern const Key     k_home,                 k_f6,         k_caps;
extern const Key     k_end,                  k_f7;
extern const Key     k_pageup,               k_f8;
extern const Key     k_pagedown,             k_f9;
extern const Key     k_arrow_up,             k_f10;
extern const Key     k_arrow_down,           k_f11;
extern const Key     k_arrow_left,           k_f12;
extern const Key     k_arrow_right;


/***********
 * Commands
 ***********/

/* Layers */
// For layer selection use the LS(n) macro
extern const Key    c_layer_lock;


/* Mouse */
// For mouse movement use the MU, MD, MR, ML, MWU and MWD macros
extern const Key    m_click_1,  m_click_2,  m_click_3,  m_click_4,  m_click_5;

#endif // KEYS_H
