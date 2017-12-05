#ifndef USB_KEYBOARD_H
#define USB_KEYBOARD_H

void report_key(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycode);
void report_keys(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycodes[6]);
void report_keypress(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycode);
/* void report_character(usbd_device* usbd_dev, char c); */
/* void type(usbd_device* usbd_dev, uint8_t modifier, uint8_t keycode); */

#endif // USB_KEYBOARD_H
