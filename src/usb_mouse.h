#ifndef USB_MOUSE_H
#define USB_MOUSE_H

typedef enum _mouse_axis {X, Y, Z} MouseAxis;
typedef enum _mouse_dir {UP, DOWN} MouseDir;

/* Report mouse movement
 */
void report_mouse_movement(MouseAxis axis, MouseDir dir);

#endif // USB_MOUSE_H

