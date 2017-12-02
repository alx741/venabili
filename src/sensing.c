#include <string.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include "sensing.h"
#include "keys.h"

bool keys_matrix[NROWS][NCOLS] = {0};

void keyboard_sensing_init(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

    // PORTA (0-11) as matrix inputs
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7
            | GPIO8 | GPIO9 | GPIO10 | GPIO11);

    // PORTB (0-3) as matrix outputs
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
            GPIO0 | GPIO1 | GPIO2 | GPIO3);
	gpio_clear(GPIOB, GPIO0 | GPIO1 | GPIO2 | GPIO3);
}

void wipe_keys_matrix(void)
{
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            keys_matrix[i][j] = false;
        }
    }
}

int sense_keys(void)
{
    int n = 0;
    wipe_keys_matrix();

    // Row 1
    for (int r = 0; r < NROWS; r++)
    {
        gpio_set(GPIOB, 1 << r);
        for (int c = 0; c < NCOLS; c++)
        {
            if (gpio_get(GPIOA, 1 << c))
            {
                keys_matrix[r][c] = true;
                n++;
            }
        }
        gpio_clear(GPIOB, 1 << r);
    }
    return n;
}

/* void mapping(void) */
/* { */
/*     for (int i = 0; i < NKEYS; i++) */
/*     { */
/*         if (pressed_keys[i] == A1) */
/*         { */
/*             pressed_keys[i] = KEY_A; */
/*         } */
/*         else if (pressed_keys[i] == A2) */
/*         { */
/*             pressed_keys[i] = KEY_B; */
/*         } */
/*     } */
/* } */
