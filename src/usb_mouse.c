#include <libopencm3/usb/usbd.h>
#include "usb_mouse.h"

typedef struct _mouse_report_t
{
    uint8_t report_id;
    uint8_t buttons;
    uint8_t x_axis;
    uint8_t y_axis;
    uint8_t wheel;
} mouse_report_t;