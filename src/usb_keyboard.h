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

#include <stdint.h>

/* Keys reporting
 */
void report_key(uint8_t modifiers, uint8_t keycode);
void report_6_keys(uint8_t modifiers, uint8_t keycodes[6]);

/* Report key down, immediately followed by key release
 */
void report_keypress(uint8_t modifiers, uint8_t keycode);
void report_6_keypress(uint8_t modifiers, uint8_t keycodes[6]);

/* Type a null-terminated string
 */
void type_string(const char *s);

/* Type a single ASCII character
 */
void type_char(char c);
