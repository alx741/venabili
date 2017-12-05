#include <string.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include "sensing.h"
#include "usb_keys.h"

int N_PRESSED = 0;
int N_PREV_PRESSED = 0;
bool KMAT_PREV_STATE[NROWS][NCOLS] = { { false } };
bool KMAT_STATE[NROWS][NCOLS] = { { false } };
Key_coordinate PRESSED_KEYS[NKEYS] = { {0, 0} };
Key_coordinate PRESSED_PREV_KEYS[NKEYS] = { {0, 0} };

const Key_coordinate NULL_COORDINATE = {-1, -1};

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

void wait(void)
{
	for (unsigned i = 0; i < 900000; i++) { __asm__("nop"); }
}

int sense_keys(void)
{
    int n = 0;
    backup_and_wipe_current_state();

    for (int r = 5; r < (NROWS + 5); r++)
    {
        gpio_set(GPIOB, 1 << r);
        for (int c = 0; c < NCOLS; c++)
        {
            if (gpio_get(GPIOA, 1 << c))
            {
                KMAT_STATE[r-5][c] = true;
                n++;
            }
            else
            {
                KMAT_STATE[r-5][c] = false;
            }
        }
        gpio_clear(GPIOB, 1 << r);
    }
    /* wait(); */
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
