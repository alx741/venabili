#ifndef SENSING_H
#define SENSING_H

#define NKEYS 48
/*   4rows x 12cols = 48 keys
 *
 *   -------------------------------------------------
 *   |A 1|A 2|A 3|A 4|A 5|A 6|A 7|A 8|A 9|A10|A11|A12|
 *   -------------------------------------------------
 *   |B 1|B 2|B 3|B 4|B 5|B 6|B 7|B 8|B 9|B10|B11|B12|
 *   -------------------------------------------------
 *   |C 1|B 2|B 3|B 4|B 5|B 6|B 7|B 8|B 9|B10|B11|B12|
 *   -------------------------------------------------
 *   |D 1|D 2|D 3|D 4|D 5|D 6|D 7|D 8|D 9|D10|D11|D12|
 *   -------------------------------------------------
 */

typedef enum
{
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12,
    B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12,
    C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12,
    D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12
} Mat_keys;

/* Pressed keys will be stored here
 *
 * Use the 'sense_keys()' function to populate this
 */
static Mat_keys pressed_keys[NKEYS];

/* Store pressed keys in the 'pressed_keys' array
 *
 * Returns the number of sensed keys
 */
int sense_keys(void);

#endif // SENSING_H
