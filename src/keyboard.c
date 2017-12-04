#include <string.h>
#include <libopencm3/usb/usbd.h>
#include "keyboard.h"
#include "usb_keys.h"

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

void report_keypress(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycode)
{
    report_key(usbd_dev, modifier, keycode);
    for (unsigned i = 0; i < 10; i++) { __asm__("nop"); }
    report_key(usbd_dev, MOD_NONE, KEY_NONE);
}

void report_character(usbd_device* usbd_dev, char c)
{
    switch(c)
    {
        case ' ':
            report_keypress(usbd_dev, MOD_NONE, KEY_SPACEBAR);
            break;

        case '!':
            report_keypress(usbd_dev, MOD_NONE, KEY_SPACEBAR);
            break;

        case '"':
            report_keypress(usbd_dev, MOD_NONE, KEY_SPACEBAR);
            break;

        default:
            // code
            break;
    }
}
