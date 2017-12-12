#ifndef USB_MOUSE_H
#define USB_MOUSE_H

typedef enum _mouse_axis {UP, DOWN, LEFT, RIGHT, WHEELUP, WHEELDOWN} MouseMovement;

void report_mouse_movement(MouseMovement m, uint8_t speed);
void report_mouse_click(uint8_t button);

#endif // USB_MOUSE_H

