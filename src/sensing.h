#ifndef SENSING_H
#define SENSING_H

#define NROWS 4
#define NCOLS 12
#define NKEYS (NROWS * NCOLS) // 48

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


/* Initialize Keyboard matrix sensing
 */
void keyboard_sensing_init(void);


/* Keys status will be stored in these two matrices
 *
 * Use the 'sense_keys()' function to populate them
 */
extern bool keys_matrix_previous[NROWS][NCOLS];
extern bool keys_matrix[NROWS][NCOLS];


/* Stores keys state in 'keys_matrix'
 * Moves previous keys state to 'keys_matrix_previous'
 *
 * Returns the number of active keys
 */
int sense_keys(void);


/* Tell if a particular key is pressed
 */
bool pressed(bool mat[NROWS][NCOLS], int i, int j);


/* Tell if only this and no other key is pressed
 */
bool pressed_alone(bool mat[NROWS][NCOLS], int i, int j);


/* Tell if a key was tapped (pressed and released alone)
 */
bool tapped(bool mat[NROWS][NCOLS], int i, int j);

#endif // SENSING_H
