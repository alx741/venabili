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


/*****************
 * Configuration
 *****************/

// How many layers are you going to have?
#define N_LAYERS 4

// How many macros are you going to have?
#define N_MACROS 10

// What is the maximum length of your macros?
#define MAX_MACRO_LENGTH 20

// If you hold a double-function key longer than this (in milliseconds),
// then the key press will be discarded
#define TAP_TIMEOUT_MS  250

// Pressing two shift keys simultaneously triggers CapsLock
//#define ENABLE_DOUBLE_SHIFT_CAPS_LOCK
