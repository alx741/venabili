#include <string.h>
#include <stdint.h>
#include <libopencm3/usb/usbd.h>
#include "usb_keyboard.h"
#include "usb_keys.h"

#include "usb.h"

typedef struct _keyboard_report_t
{
    uint8_t report_id;
    uint8_t modifiers;
    uint8_t _reserved;
    uint8_t keycodes[6];
} keyboard_report_t;

void report_key(uint8_t modifiers, uint8_t keycode)
{
    keyboard_report_t kr = {0};
    kr.report_id = 0x02;
    kr._reserved = 0x00;
    kr.modifiers = modifiers;
    kr.keycodes[0] = keycode;
    while(usbd_ep_write_packet(usbd_dev, 0x81, &kr, 9) != 9);
}

void report_keys(uint8_t modifiers, uint8_t keycodes[6])
{
    keyboard_report_t kr = {0};
    kr.report_id = 0x02;
    kr._reserved = 0x00;
    kr.modifiers = modifiers;
    memcpy(kr.keycodes, keycodes, 6);
    while(usbd_ep_write_packet(usbd_dev, 0x81, &kr, 9) != 9);
}

void report_keypress(uint8_t modifiers, uint8_t keycode)
{
    report_key(modifiers, keycode);
    report_key(MOD_NONE, KEY_NONE);
}

/* void report_character(usbd_device* usbd_dev, char c) */
/* { */
/*     switch(c) */
/*     { */
/*         case ' ': */
/*             report_keypress(usbd_dev, MOD_NONE, KEY_SPACEBAR); */
/*             break; */

/*         case '!': */
/*             report_keypress(usbd_dev, MOD_NONE, KEY_SPACEBAR); */
/*             break; */

/*         case '"': */
/*             report_keypress(usbd_dev, MOD_NONE, KEY_SPACEBAR); */
/*             break; */

/*         default: */
/*             // code */
/*             break; */
/*     } */
/* } */
