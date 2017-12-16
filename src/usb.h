#pragma once

#include <libopencm3/usb/usbd.h>

extern usbd_device *usbd_dev;

/* Initialize USB subsystem
 */
void usb_init(void);
