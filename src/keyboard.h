#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef struct _keyboard_report_t
{
    uint8_t report_id;
    uint8_t modifier;
    uint8_t _reserved;
    uint8_t keycodes[6];
} keyboard_report_t;

void report_key(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycode);
void report_keys(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycodes[6]);
void report_keypress(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycode);
void report_character(usbd_device* usbd_dev, char c);
/* void type(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycode); */

#endif // KEYBOARD_H
