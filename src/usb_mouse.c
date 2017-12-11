#include <libopencm3/usb/usbd.h>
#include "usb.h"
#include "usb_mouse.h"

#define MOUSE_REPORT_ID 0x01

typedef struct _mouse_report_t
{
    uint8_t report_id;
    uint8_t buttons;
    uint8_t x_axis;
    uint8_t y_axis;
    uint8_t wheel;
} mouse_report_t;

void report_mouse_movement(MouseMovement m)
{
    mouse_report_t mr = {0};
    mr.report_id = MOUSE_REPORT_ID;
    mr.buttons = 0;

    switch (axis)
    {
        case X:
            mr.x_axis = 1; // FIXME: use proper value here
            break;
        case Y:
            mr.y_axis = 1; // FIXME: use proper value here
            break;
        case Z:
            mr.wheel = 1; // FIXME: use proper value here
            break;
    }
    while(usbd_ep_write_packet(usbd_dev, 0x81, &mr, 5) != 5);
}
