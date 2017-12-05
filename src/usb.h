#ifndef USB_H
#define USB_H

#include <libopencm3/usb/usbd.h>

extern usbd_device *usbd_dev;

void usb_init(void);

#endif // USB_H
