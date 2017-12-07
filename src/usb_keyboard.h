#ifndef USB_KEYBOARD_H
#define USB_KEYBOARD_H

void report_keypress(uint8_t modifiers, uint8_t keycode);
void report_6_keypress(uint8_t modifiers, uint8_t keycodes[6]);

#endif // USB_KEYBOARD_H
