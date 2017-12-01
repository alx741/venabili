#include <libopencm3/stm32/gpio.h>
#include "sensing.h"

static Mat_keys pressed_keys[NKEYS] = {0};

int sense_keys(void)
{
    pressed_keys[0] = A1;
    return 1;
}
