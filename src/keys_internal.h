/*
 *  Copyright 2017 Daniel Campoverde C. <alx@sillybytes.net>
 *
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


#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    // Normal Key
    uint8_t usb_keycode;
    uint8_t modifiers;

    // Double functionality hold key
    uint8_t hold_mod;

    // Command key
    uint16_t command;
} Key;


/* Possible special commands
 */
#define CMD_NONE               0x0000

// Layers
#define CMD_LOCK_LAYER         0x0001
// Reserved 0x0002 - 0x000F

// Mouse
#define CMD_MOUSE_UP             0x0010 // - 0x001F
#define CMD_MOUSE_DOWN           0x0020 // - 0x002F
#define CMD_MOUSE_RIGHT          0x0030 // - 0x003F
#define CMD_MOUSE_LEFT           0x0040 // - 0x004F
#define CMD_MOUSE_WHEELUP        0x0050 // - 0x005F
#define CMD_MOUSE_WHEELDOWN      0x0060 // - 0x006F
#define CMD_MOUSE_CLICK_1        0x0070
#define CMD_MOUSE_CLICK_2        0x0071
#define CMD_MOUSE_CLICK_3        0x0072
#define CMD_MOUSE_CLICK_4        0x0073
#define CMD_MOUSE_CLICK_5        0x0074

// Macros
#define CMD_MACRO_FIRST          0x0075
#define CMD_MACRO_LAST           0x0090

#define CMD_FLASH_MODE           0x0091
// ... Up to 0x00FF

// Use the LS(n) macro for Layer Selection
#define LS_FIRST 0x0100
#define LS_LAST  0xFF00


/* Tell if KEY has hold key functionality
 */
bool hasHoldKey(Key k);

/* Tell if KEY has CTRL modifier or CTRL hold-modifier
 */
bool hasCtrl(Key k);

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


/* Identify Macro command keys
 */
bool isMacroCommandkey(Key k);
int getMacroId(Key k);


/* Identify Mouse command keys
 */
bool isMouseCommandKey(Key k);
bool isMouseMovementKey(Key k);
bool isMouseClickKey(Key k);

/* Identify direction of mouse command key
 */
bool isMouseUpKey(Key k);
bool isMouseDownKey(Key k);
bool isMouseRightKey(Key k);
bool isMouseLeftKey(Key k);
bool isMouseWheelUpKey(Key k);
bool isMouseWheelDownKey(Key k);

/* Get mouse attributes from command key
 */
uint8_t getMouseMovementSpeed(Key k);
uint8_t getMouseClickButton(Key k);

/* Convert a char to a suitable Key representation
 */
Key char2key(char c);
