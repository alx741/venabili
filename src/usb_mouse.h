#ifndef USB_MOUSE_H
#define USB_MOUSE_H

typedef enum _mouse_axis {UP, DOWN, LEFT, RIGHT, WHEELUP WHEELDOWN} MouseMovement;

/* Report mouse movement
 */
void report_mouse_movement(MouseMovement m);

#endif // USB_MOUSE_H

