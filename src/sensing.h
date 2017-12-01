#ifndef SENSING_H
#define SENSING_H

#define NROWS 4
#define NCOLS 12
#define NKEYS (NROWS * NCOLS)
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

/* Keys status will be stored here
 *
 * Use the 'sense_keys()' function to populate this matrix
 */
extern bool keys_matrix[NROWS][NCOLS];

/* Store keys state in the 'keys_matrix' array
 *
 * Returns the number of active keys
 */
int sense_keys(void);
/* void mapping(void); */

#endif // SENSING_H
