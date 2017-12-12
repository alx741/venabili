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

void report_mouse_movement(MouseMovement m, uint8_t speed)
{
    mouse_report_t mr = {0};
    mr.report_id = MOUSE_REPORT_ID;
    mr.buttons = 0;

    switch (m)
    {
        case UP:
            mr.y_axis = -1 * speed; // FIXME: use proper value here
            break;
        case DOWN:
            mr.y_axis = 1 * speed;
            break;
        case RIGHT:
            mr.x_axis = 1 * speed;
            break;
        case LEFT:
            mr.x_axis = -1 * speed;
            break;
        case WHEELUP:
            mr.wheel = 1 * speed;
            break;
        case WHEELDOWN:
            mr.wheel = -1 * speed;
            break;
    }
    while(usbd_ep_write_packet(usbd_dev, 0x81, &mr, 5) != 5);
}
