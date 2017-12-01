#include "sensing.h"

static Mat_keys pressed_keys[48] = {0};

int sense_keys(void)
{
    pressed_keys[0] = A1;
    return 1;
}
