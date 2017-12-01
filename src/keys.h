/*
 *  This file is part of Venabili.
 *
 *  Venabili is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Venabili is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Venabili.  If not, see <http://www.gnu.org/licenses/>.
 */


/* This file declares Key Codes for the USB Keyboard/Keypad Page, according to
 * the "HID Usage Tables 1.12" specification file (Table 12).
 */

/* Special Signaling */
#define     SGN_ERROR_ROLL_OVER 0x01
#define     SGN_POST_FAIL       0x02
#define     SGN_ERROR_UNDEFINED 0x03

/* Letters */
#define     KEY_A    0x04
#define     KEY_B    0x05
#define     KEY_C    0x06
#define     KEY_D    0x07
#define     KEY_E    0x08
#define     KEY_F    0x09
#define     KEY_G    0x0A
#define     KEY_H    0x0B
#define     KEY_I    0x0C
#define     KEY_J    0x0D
#define     KEY_K    0x0E
#define     KEY_L    0x0F
#define     KEY_M    0x10
#define     KEY_N    0x11
#define     KEY_O    0x12
#define     KEY_P    0x13
#define     KEY_Q    0x14
#define     KEY_R    0x15
#define     KEY_S    0x16
#define     KEY_T    0x17
#define     KEY_U    0x18
#define     KEY_V    0x19
#define     KEY_W    0x1A
#define     KEY_X    0x1B
#define     KEY_Y    0x1C
#define     KEY_Z    0x1D

/* Numbers */
#define     KEY_1    0x1E
#define     KEY_2    0x1F
#define     KEY_3    0x20
#define     KEY_4    0x21
#define     KEY_5    0x22
#define     KEY_6    0x23
#define     KEY_7    0x24
#define     KEY_8    0x25
#define     KEY_9    0x26
#define     KEY_0    0x27

/* Non-printables */
#define     KEY_ENTER        0x28
#define     KEY_ESCAPE       0x29
#define     KEY_BACKSPACE    0x2A
#define     KEY_TAB          0x2B
#define     KEY_SPACEBAR     0x2C
#define     KEY_LEFT_CTRL    0xE0
#define     KEY_LEFT_SHIFT   0xE1
#define     KEY_LEFT_ALT     0xE2
#define     KEY_LEFT_SUPER   0xE3
#define     KEY_RIGHT_CTRL   0xE4
#define     KEY_RIGHT_SHIFT  0xE5
#define     KEY_RIGHT_ALT    0xE6
#define     KEY_RIGHT_SUPER  0xE7

/* Modifiers */
#define     MOD_NONE         0x00
#define     MOD_LEFT_CTRL    0x01
#define     MOD_LEFT_SHIFT   0x02
#define     MOD_LEFT_ALT     0x04
#define     MOD_LEFT_SUPER   0x08
#define     MOD_RIGHT_CTRL   0x10
#define     MOD_RIGHT_SHIFT  0x20
#define     MOD_RIGHT_ALT    0x40
#define     MOD_RIGHT_SUPER  0x80

//TODO: Sould define these with SHIFT modifier
/* Symbols */
/* #define     KEY_BANG            KEY_1 */
/* #define     KEY_AT              KEY_2 */
/* #define     KEY_HASH            KEY_3 */
/* #define     KEY_DOLLAR          KEY_4 */
/* #define     KEY_PERCENT         KEY_5 */
/* #define     KEY_CARET           KEY_6 */
/* #define     KEY_AMPERSAND       KEY_7 */
/* #define     KEY_ASTERISK        KEY_8 */
/* #define     KEY_OPEN_PAREN      KEY_9 */
/* #define     KEY_CLOSE_PAREN     KEY_0 */
/* #define     KEY_EQUAL           0x2E */
/* #define     KEY_PLUS            KEY_EQUAL */
/* #define     KEY_OPEN_BRACKET    0x2F */
/* #define     KEY_OPEN_BRACE      KEY_OPEN_BRACKET */
