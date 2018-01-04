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
#include "config.h"


extern Key MACROS[N_MACROS][MAX_MACRO_LENGTH];

/* Add a macro
 *
 * Macros end with an empty key 'k_empty'
 */
void add_macro(const Key macro[MAX_MACRO_LENGTH]);

/* Add a string macro
 *
 * String macros end with a null character '\0'
 */
void add_string_macro(const char macro[MAX_MACRO_LENGTH]);

/* Report a macro to the host
 */
void report_macro(int id);
