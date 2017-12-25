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

#define N_MOUSE_BTNS 5

typedef enum _mouse_axis {UP, DOWN, LEFT, RIGHT, WHEELUP, WHEELDOWN} MouseMovement;

typedef enum _mouse_btns {BTN1 = 1, BTN2, BTN3, BTN4, BTN5} MouseButton;

/* Report mouse movement in direction M and some SPEED
 */
void report_mouse_movement(MouseMovement m, uint8_t speed);

/* Report the state of mouse buttons
 */
void report_mouse_buttons(MouseButton bs[N_MOUSE_BTNS]);

/* Report a click down, immediately followed by a click release
 */
void report_mouse_click(MouseButton b);
