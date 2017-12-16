/*
 *  Copyright 2017 Daniel Campoverde C. <alx@sillybytes.net>
 *
 *  This file is part of Venabili.
 *
 *  Venabili is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Venabili is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Venabili.  If not, see <http://www.gnu.org/licenses/>.
 */


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
            mr.y_axis = -1 * speed;
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
