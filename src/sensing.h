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


// Easy matrix access
#define     A1      keys_matrix[0][0]
#define     PA1     keys_matrix_previous[0][0]
#define     A2      keys_matrix[0][1]
#define     PA2     keys_matrix_previous[0][1]
#define     A3      keys_matrix[0][2]
#define     PA3     keys_matrix_previous[0][2]
#define     A4      keys_matrix[0][3]
#define     PA4     keys_matrix_previous[0][3]
#define     A5      keys_matrix[0][4]
#define     PA5     keys_matrix_previous[0][4]
#define     A6      keys_matrix[0][5]
#define     PA6     keys_matrix_previous[0][5]
#define     A7      keys_matrix[0][6]
#define     PA7     keys_matrix_previous[0][6]
#define     A8      keys_matrix[0][7]
#define     PA8     keys_matrix_previous[0][7]
#define     A9      keys_matrix[0][8]
#define     PA9     keys_matrix_previous[0][8]
#define     A10     keys_matrix[0][9]
#define     PA10    keys_matrix_previous[0][9]
#define     A11     keys_matrix[0][10]
#define     PA11    keys_matrix_previous[0][10]
#define     A12     keys_matrix[0][11]
#define     PA12    keys_matrix_previous[0][11]

#define     B1      keys_matrix[1][0]
#define     PB1     keys_matrix_previous[1][0]
#define     B2      keys_matrix[1][1]
#define     PB2     keys_matrix_previous[1][1]
#define     B3      keys_matrix[1][2]
#define     PB3     keys_matrix_previous[1][2]
#define     B4      keys_matrix[1][3]
#define     PB4     keys_matrix_previous[1][3]
#define     B5      keys_matrix[1][4]
#define     PB5     keys_matrix_previous[1][4]
#define     B6      keys_matrix[1][5]
#define     PB6     keys_matrix_previous[1][5]
#define     B7      keys_matrix[1][6]
#define     PB7     keys_matrix_previous[1][6]
#define     B8      keys_matrix[1][7]
#define     PB8     keys_matrix_previous[1][7]
#define     B9      keys_matrix[1][8]
#define     PB9     keys_matrix_previous[1][8]
#define     B10     keys_matrix[1][9]
#define     PB10    keys_matrix_previous[1][9]
#define     B11     keys_matrix[1][10]
#define     PB11    keys_matrix_previous[1][10]
#define     B12     keys_matrix[1][11]
#define     PB12    keys_matrix_previous[1][11]

#define     C1      keys_matrix[2][0]
#define     PC1     keys_matrix_previous[2][0]
#define     C2      keys_matrix[2][1]
#define     PC2     keys_matrix_previous[2][1]
#define     C3      keys_matrix[2][2]
#define     PC3     keys_matrix_previous[2][2]
#define     C4      keys_matrix[2][3]
#define     PC4     keys_matrix_previous[2][3]
#define     C5      keys_matrix[2][4]
#define     PC5     keys_matrix_previous[2][4]
#define     C6      keys_matrix[2][5]
#define     PC6     keys_matrix_previous[2][5]
#define     C7      keys_matrix[2][6]
#define     PC7     keys_matrix_previous[2][6]
#define     C8      keys_matrix[2][7]
#define     PC8     keys_matrix_previous[2][7]
#define     C9      keys_matrix[2][8]
#define     PC9     keys_matrix_previous[2][8]
#define     C10     keys_matrix[2][9]
#define     PC10    keys_matrix_previous[2][9]
#define     C11     keys_matrix[2][10]
#define     PC11    keys_matrix_previous[2][10]
#define     C12     keys_matrix[2][11]
#define     PC12    keys_matrix_previous[2][11]

#define     D1      keys_matrix[3][0]
#define     PD1     keys_matrix_previous[3][0]
#define     D2      keys_matrix[3][1]
#define     PD2     keys_matrix_previous[3][1]
#define     D3      keys_matrix[3][2]
#define     PD3     keys_matrix_previous[3][2]
#define     D4      keys_matrix[3][3]
#define     PD4     keys_matrix_previous[3][3]
#define     D5      keys_matrix[3][4]
#define     PD5     keys_matrix_previous[3][4]
#define     D6      keys_matrix[3][5]
#define     PD6     keys_matrix_previous[3][5]
#define     D7      keys_matrix[3][6]
#define     PD7     keys_matrix_previous[3][6]
#define     D8      keys_matrix[3][7]
#define     PD8     keys_matrix_previous[3][7]
#define     D9      keys_matrix[3][8]
#define     PD9     keys_matrix_previous[3][8]
#define     D10     keys_matrix[3][9]
#define     PD10    keys_matrix_previous[3][9]
#define     D11     keys_matrix[3][10]
#define     PD11    keys_matrix_previous[3][10]
#define     D12     keys_matrix[3][11]
#define     PD12    keys_matrix_previous[3][11]

#endif // SENSING_H
