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

#include "keys_internal.h"
#include "sensing.h"

#define NLAYERS 4
#define TAP_TIMEOUT_MS  1500
#define ENABLE_DOUBLE_SHIFT_CAPS_LOCK


/**
 * Initialize keyboard
 */
void keyboard_init(void);

/**
 * Add a new layer to the keyboard
 */
void add_layer(const Key layer[NROWS][NCOLS]);

/**
 * Selects a layer based on user commands
 */
void select_layer(void);

/**
 * Fill KEYS with the currently pressed keys in the current layer
 */
int map_layer(Key keys[NKEYS]);

/**
 * Apply pressed modifiers to normal keys in KEYS array
 * of N pressed keys
 */
void apply_modifiers(Key keys[NKEYS], int n);

/**
 * Execute key pulsations in current layer
 */
void execute(const Key keys[NKEYS], int n);
