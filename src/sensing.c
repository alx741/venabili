#include <string.h>
#include <libopencm3/stm32/gpio.h>
#include "sensing.h"
#include "keys.h"

bool keys_matrix[NROWS][NCOLS] = {0};

void wipe_keys_matrix(void);

int sense_keys(void)
{
    int n = 0;
    wipe_keys_matrix();

    // Row 1
    gpio_set(GPIOB, GPIO0);
    /* for (int i = 0; i < NCOLS; i++) */
    /* { */
        if (gpio_get(GPIOA, GPIO0))
        {
            keys_matrix[0][0] = true;
        }
    /* } */
    gpio_clear(GPIOB, GPIO0);

        /* if (keys_matrix[0][0]) */
        /* { */
        /*     gpio_set(GPIOB, GPIO2); */
        /*     /1* report_key(usbd_dev, MOD_NONE, KEY_A); *1/ */
        /* } */
        /* else */
        /* { */
        /*     // Will only report the 6 out of 48 possible simultanious keys */
        /*     // Becouse of USB 6KRO limitation */
        /*     gpio_clear(GPIOB, GPIO2); */
        /*     /1* report_key(usbd_dev, MOD_NONE, KEY_NONE); *1/ */
        /* } */




    /* gpio_set(GPIOB, GPIO1); */
    /*     if (gpio_get(GPIOA, GPIO1)) */
    /*     { */
    /*         pressed_keys[n++] = B1; */
    /*     } */
    /* gpio_clear(GPIOB, GPIO1); */

    return n;
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
