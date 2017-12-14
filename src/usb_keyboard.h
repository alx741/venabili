#ifndef USB_KEYBOARD_H
#define USB_KEYBOARD_H

#include <stdint.h>

/* Keys reporting
 */
void report_key(uint8_t modifiers, uint8_t keycode);
void report_6_keys(uint8_t modifiers, uint8_t keycodes[6]);

/* Report key down, immediately followed by key release
 */
void report_keypress(uint8_t modifiers, uint8_t keycode);
void report_6_keypress(uint8_t modifiers, uint8_t keycodes[6]);

/* Type a null-terminated string
 */
void type_string(const char *s);

/* Type a single ASCII character
 */
void type_char(char c);

#endif // USB_KEYBOARD_H
