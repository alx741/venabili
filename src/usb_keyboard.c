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

void report_6_keys(uint8_t modifiers, uint8_t keycodes[6])
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

void report_6_keypress(uint8_t modifiers, uint8_t keycodes[6])
{
    report_6_keys(modifiers, keycodes);
    report_key(MOD_NONE, KEY_NONE);
}

void report_char(char c)
{
    switch(c)
    {
        case 'a':
            report_keypress(MOD_NONE, KEY_A); break;
        case 'b':
            report_keypress(MOD_NONE, KEY_B); break;
        case 'c':
            report_keypress(MOD_NONE, KEY_C); break;
        case 'd':
            report_keypress(MOD_NONE, KEY_D); break;
        case 'e':
            report_keypress(MOD_NONE, KEY_E); break;
        case 'f':
            report_keypress(MOD_NONE, KEY_F); break;
        case 'g':
            report_keypress(MOD_NONE, KEY_G); break;
        case 'h':
            report_keypress(MOD_NONE, KEY_H); break;
        case 'i':
            report_keypress(MOD_NONE, KEY_I); break;
        case 'j':
            report_keypress(MOD_NONE, KEY_J); break;
        case 'k':
            report_keypress(MOD_NONE, KEY_K); break;
        case 'l':
            report_keypress(MOD_NONE, KEY_L); break;
        case 'm':
            report_keypress(MOD_NONE, KEY_M); break;
        case 'n':
            report_keypress(MOD_NONE, KEY_N); break;
        case 'o':
            report_keypress(MOD_NONE, KEY_O); break;
        case 'p':
            report_keypress(MOD_NONE, KEY_P); break;
        case 'q':
            report_keypress(MOD_NONE, KEY_Q); break;
        case 'r':
            report_keypress(MOD_NONE, KEY_R); break;
        case 's':
            report_keypress(MOD_NONE, KEY_S); break;
        case 't':
            report_keypress(MOD_NONE, KEY_T); break;
        case 'u':
            report_keypress(MOD_NONE, KEY_U); break;
        case 'v':
            report_keypress(MOD_NONE, KEY_V); break;
        case 'w':
            report_keypress(MOD_NONE, KEY_W); break;
        case 'x':
            report_keypress(MOD_NONE, KEY_X); break;
        case 'y':
            report_keypress(MOD_NONE, KEY_Y); break;
        case 'z':
            report_keypress(MOD_NONE, KEY_Z); break;


        case 'A':
            report_keypress(MOD_LEFT_SHIFT, KEY_A); break;
        case 'B':
            report_keypress(MOD_LEFT_SHIFT, KEY_B); break;
        case 'C':
            report_keypress(MOD_LEFT_SHIFT, KEY_C); break;
        case 'D':
            report_keypress(MOD_LEFT_SHIFT, KEY_D); break;
        case 'E':
            report_keypress(MOD_LEFT_SHIFT, KEY_E); break;
        case 'F':
            report_keypress(MOD_LEFT_SHIFT, KEY_F); break;
        case 'G':
            report_keypress(MOD_LEFT_SHIFT, KEY_G); break;
        case 'H':
            report_keypress(MOD_LEFT_SHIFT, KEY_H); break;
        case 'I':
            report_keypress(MOD_LEFT_SHIFT, KEY_I); break;
        case 'J':
            report_keypress(MOD_LEFT_SHIFT, KEY_J); break;
        case 'K':
            report_keypress(MOD_LEFT_SHIFT, KEY_K); break;
        case 'L':
            report_keypress(MOD_LEFT_SHIFT, KEY_L); break;
        case 'M':
            report_keypress(MOD_LEFT_SHIFT, KEY_M); break;
        case 'N':
            report_keypress(MOD_LEFT_SHIFT, KEY_N); break;
        case 'O':
            report_keypress(MOD_LEFT_SHIFT, KEY_O); break;
        case 'P':
            report_keypress(MOD_LEFT_SHIFT, KEY_P); break;
        case 'Q':
            report_keypress(MOD_LEFT_SHIFT, KEY_Q); break;
        case 'R':
            report_keypress(MOD_LEFT_SHIFT, KEY_R); break;
        case 'S':
            report_keypress(MOD_LEFT_SHIFT, KEY_S); break;
        case 'T':
            report_keypress(MOD_LEFT_SHIFT, KEY_T); break;
        case 'U':
            report_keypress(MOD_LEFT_SHIFT, KEY_U); break;
        case 'V':
            report_keypress(MOD_LEFT_SHIFT, KEY_V); break;
        case 'W':
            report_keypress(MOD_LEFT_SHIFT, KEY_W); break;
        case 'X':
            report_keypress(MOD_LEFT_SHIFT, KEY_X); break;
        case 'Y':
            report_keypress(MOD_LEFT_SHIFT, KEY_Y); break;
        case 'Z':
            report_keypress(MOD_LEFT_SHIFT, KEY_Z); break;


        case '0':
            report_keypress(MOD_NONE, KEY_0); break;
        case '1':
            report_keypress(MOD_NONE, KEY_1); break;
        case '2':
            report_keypress(MOD_NONE, KEY_2); break;
        case '3':
            report_keypress(MOD_NONE, KEY_3); break;
        case '4':
            report_keypress(MOD_NONE, KEY_4); break;
        case '5':
            report_keypress(MOD_NONE, KEY_5); break;
        case '6':
            report_keypress(MOD_NONE, KEY_6); break;
        case '7':
            report_keypress(MOD_NONE, KEY_7); break;
        case '8':
            report_keypress(MOD_NONE, KEY_8); break;
        case '9':
            report_keypress(MOD_NONE, KEY_9); break;


        case ' ':
            report_keypress(MOD_NONE, KEY_SPACEBAR); break;
        case '!':
            report_keypress(MOD_LEFT_SHIFT, KEY_1); break;
        case '"':
            report_keypress(MOD_LEFT_SHIFT, KEY_SINGLE_QUOTE); break;
        case '#':
            report_keypress(MOD_LEFT_SHIFT, KEY_3); break;
        case '$':
            report_keypress(MOD_LEFT_SHIFT, KEY_4); break;
        case '%':
            report_keypress(MOD_LEFT_SHIFT, KEY_5); break;
        case '&':
            report_keypress(MOD_LEFT_SHIFT, KEY_7); break;
        case '\'':
            report_keypress(MOD_NONE, KEY_SINGLE_QUOTE); break;
        case '(':
            report_keypress(MOD_LEFT_SHIFT, KEY_9); break;
        case ')':
            report_keypress(MOD_LEFT_SHIFT, KEY_0); break;
        case '*':
            report_keypress(MOD_LEFT_SHIFT, KEY_8); break;
        case '+':
            report_keypress(MOD_NONE, KEY_EQUAL); break;
        case ',':
            report_keypress(MOD_NONE, KEY_COMMA); break;
        case '-':
            report_keypress(MOD_NONE, KEY_HYPHEN); break;
        case '.':
            report_keypress(MOD_NONE, KEY_DOT); break;
        case '/':
            report_keypress(MOD_NONE, KEY_SLASH); break;
        case ':':
            report_keypress(MOD_LEFT_SHIFT, KEY_SEMICOLON); break;
        case ';':
            report_keypress(MOD_NONE, KEY_SEMICOLON); break;
        case '<':
            report_keypress(MOD_LEFT_SHIFT, KEY_COMMA); break;
        case '=':
            report_keypress(MOD_NONE, KEY_EQUAL); break;
        case '>':
            report_keypress(MOD_LEFT_SHIFT, KEY_DOT); break;
        case '?':
            report_keypress(MOD_LEFT_SHIFT, KEY_SLASH); break;
        case '@':
            report_keypress(MOD_LEFT_SHIFT, KEY_2); break;
        case '[':
            report_keypress(MOD_NONE, KEY_OPEN_BRACKET); break;
        case '\\':
            report_keypress(MOD_NONE, KEY_BACKSLASH); break;
        case ']':
            report_keypress(MOD_NONE, KEY_CLOSE_BRACKET); break;
        case '^':
            report_keypress(MOD_LEFT_SHIFT, KEY_6); break;
        case '_':
            report_keypress(MOD_LEFT_SHIFT, KEY_HYPHEN); break;
        case '`':
            report_keypress(MOD_NONE, KEY_ACUTE); break;
        case '{':
            report_keypress(MOD_LEFT_SHIFT, KEY_OPEN_BRACKET); break;
        case '|':
            report_keypress(MOD_LEFT_SHIFT, KEY_BACKSLASH); break;
        case '}':
            report_keypress(MOD_LEFT_SHIFT, KEY_CLOSE_BRACKET); break;
        case '~':
            report_keypress(MOD_LEFT_SHIFT, KEY_GRAVE_ACCENT); break;

        default:
            break;
    }
}
