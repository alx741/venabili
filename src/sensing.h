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


/*
 * This module handles phisical keyboard and mouse state sensing
 */


#ifndef SENSING_H
#define SENSING_H

#include <stdbool.h>

/*************************
 *   KEYBOARD SENSING
 *************************/

#define NROWS 4
#define NCOLS 12
#define NKEYS (NROWS * NCOLS) // 48

#define DEBOUNCE_FACTOR 10

/*
 *
 *         1     2     3     4     5     6          7     8     9    10    11     12
 *      +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+-----+-----+
 *  A   |     |     |     |     |     |     |    |     |     |     |     |     |     |
 *      |     |     |     |     |     |     |    |     |     |     |     |     |     |
 *      +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+-----+-----+
 *  B   |     |     |     |     |     |     |    |     |     |     |     |     |     |
 *      |     |     |     |     |     |     |    |     |     |     |     |     |     |
 *      +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+-----+-----+
 *  C   |     |     |     |     |     |     |    |     |     |     |     |     |     |
 *      |     |     |     |     |     |     |    |     |     |     |     |     |     |
 *      +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+-----+-----+
 *  D   |     |     |     |     |     |     |    |     |     |     |     |     |     |
 *      |     |     |     |     |     |     |    |     |     |     |     |     |     |
 *      +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+-----+-----+
 *
 */

/* Phisical coordinate of a key in the matrix
 */
typedef struct
{
    int8_t i, j;
} Key_coordinate;

/* A NULL COORDINATE indicates the end of an array of pressed keys
 *
 * e.g.  Key_coordinate* k = &PRESSED_KEYS[0];
 *       while (! isNullCoordinate(*k)) { k++; }
 */
bool isNullCoordinate(Key_coordinate kc);


/* Keys status will be stored in these
 *
 * Use the 'sense_keys()' function to populate them
 */
extern int N_PRESSED; // Number of keys currently pressed
extern Key_coordinate PRESSED_KEYS[NKEYS]; // Coordinates of currently pressed keys

extern int N_PREV_PRESSED; // Number of keys previously pressed
extern Key_coordinate PRESSED_PREV_KEYS[NKEYS]; // Coordinates of previous pressed keys


/* Initialize Keyboard matrix sensing
 */
void keyboard_sensing_init(void);


/* Stores keys state in 'KMAT_STATE'
 * Moves previous keys state to 'KMAT_PREV_STATE'
 *
 * Returns the number of active keys
 */
int sense_keys(void);


/* Tell if a particular key is/was pressed
 */
bool currently_pressed(int i, int j);
bool previously_pressed(int i, int j);


/* Tell if only this and no other key is/was pressed
 */
bool currently_pressed_alone(int i, int j);
bool previously_pressed_alone(int i, int j);


/* Tell if a key was tapped (pressed and released)
 */
bool tapped(int i, int j);



/*************************
 *    MOUSE SENSING
 *************************/


#endif // SENSING_H
