#include <string.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include "sensing.h"
#include "usb_keys.h"

#define DEBOUNCE_FACTOR 20

int N_PRESSED = 0;
int N_PREV_PRESSED = 0;
bool KMAT_PREV_STATE[NROWS][NCOLS] = { { false } };
bool KMAT_STATE[NROWS][NCOLS] = { { false } };
Key_coordinate PRESSED_KEYS[NKEYS] = { {0, 0} };
Key_coordinate PRESSED_PREV_KEYS[NKEYS] = { {0, 0} };

void keyboard_sensing_init(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

    // PORTA (0-11) as matrix inputs
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7
            | GPIO8 | GPIO9 | GPIO10 | GPIO11);

    // PORTB (5-8) as matrix outputs
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
            GPIO5 | GPIO6 | GPIO7 | GPIO8);
	gpio_clear(GPIOB, GPIO5 | GPIO6 | GPIO7 | GPIO8);
}

void backup_and_wipe_current_state(void)
{
    memcpy(KMAT_PREV_STATE, KMAT_STATE, sizeof(bool) * NROWS * NCOLS);
    memcpy(PRESSED_PREV_KEYS, PRESSED_KEYS, sizeof(Key_coordinate) * NKEYS);
    memset(KMAT_STATE, 0, sizeof(bool) * NROWS * NCOLS);
    memset(PRESSED_KEYS, 0, sizeof(Key_coordinate) * NKEYS);

    N_PREV_PRESSED = N_PRESSED;
    N_PRESSED = 0;
}

int count_pressed(bool state[NROWS][NCOLS])
{
    int n = 0;
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            if (state[i][j]) { n++; }
        }
    }
    return n;
}

int sense_keys(void)
{
    int n = 0;
    int i, j = 0; // Key index
    Key_coordinate coordinate = {0, 0};

    // Debouncing variables
    int debounce_counter = 0;
    bool key_state = false;
    bool key_prev_state = false;

    backup_and_wipe_current_state();

    for (int r = 5; r < (NROWS + 5); r++)
    {
        i = r - 5;
        gpio_set(GPIOB, 1 << r);
        for (int c = 0; c < NCOLS; c++)
        {
            j = c;
            coordinate.i = i;
            coordinate.j = j;

            // Debounce
            debounce_counter = 0;
            while (debounce_counter < DEBOUNCE_FACTOR)
            {
                key_state = gpio_get(GPIOA, 1 << c);
                // Some bouncing going on
                if (key_state != key_prev_state) { debounce_counter = 0; }
                // Seems stable
                else { debounce_counter++; }
                key_prev_state = key_state;
                key_state = false;
            }

            // Read key state
            if (gpio_get(GPIOA, 1 << c))
            {
                KMAT_STATE[i][j] = true;
                PRESSED_KEYS[n++] = coordinate;
            }
            else
            {
                KMAT_STATE[i][j] = false;
            }
        }
        gpio_clear(GPIOB, 1 << r);
    }

    PRESSED_KEYS[n].i = -1;
    PRESSED_KEYS[n].j = -1;
    N_PRESSED = n;
    return n;
}

bool isPressed(bool state[NROWS][NCOLS], int i, int j)
{
    return state[i][j];
}

bool isPressed_alone(bool state[NROWS][NCOLS], int i, int j)
{
    return (isPressed(state, i, j) && count_pressed(state) == 1);
}

bool tapped_alone(int i, int j)
{
    return (isPressed_alone(KMAT_PREV_STATE, i, j)
            && !isPressed(KMAT_STATE, i, j));
}

bool isNullCoordinate(Key_coordinate kc)
{
    return (kc.i == -1 && kc.j == -1);
}
