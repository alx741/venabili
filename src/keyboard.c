#include <string.h>
#include <libopencm3/usb/usbd.h>
#include "keyboard.h"

void report_key(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycode)
{
    keyboard_report_t kr = {0};
    kr.report_id = 0x02;
    kr._reserved = 0x00;
    kr.modifier = modifier;
    kr.keycodes[0] = keycode;
    usbd_ep_write_packet(usbd_dev, 0x81, &kr, 9);
}

void report_keys(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycodes[6])
{
    keyboard_report_t kr = {0};
    kr.report_id = 0x02;
    kr._reserved = 0x00;
    kr.modifier = modifier;
    memcpy(kr.keycodes, keycodes, 6);
    usbd_ep_write_packet(usbd_dev, 0x81, &kr, 9);
}

