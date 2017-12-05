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


/* Keys status will be stored in these two matrices
 *
 * Use the 'sense_keys()' function to populate them
 */
extern bool KMAT_PREV_STATE[NROWS][NCOLS];
extern bool KMAT_STATE[NROWS][NCOLS];


/* Initialize Keyboard matrix sensing
 */
void keyboard_sensing_init(void);


/* Stores keys state in 'KMAT_STATE'
 * Moves previous keys state to 'KMAT_PREV_STATE'
 *
 * Returns the number of active keys
 */
int sense_keys(void);


/* Tell if a particular key is currently pressed
 */
bool isPressed(bool state[NROWS][NCOLS], int i, int j);


/* Tell if only this and no other key is currently pressed
 */
bool isPressed_alone(bool state[NROWS][NCOLS], int i, int j);


/* Tell if a key was tapped (pressed and released) alone
 */
bool tapped_alone(bool state[NROWS][NCOLS], int i, int j);

#endif // SENSING_H
