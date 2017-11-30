#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/hid.h>

static const uint8_t hid_report_descriptor[] =
{
    // Mouse
    0x05, 0x01, /* USAGE_PAGE (Generic Desktop)         */
    0x09, 0x02, /* USAGE (Mouse)                        */
    0xa1, 0x01, /* COLLECTION (Application)             */
    0x85, 0x01, /*   REPORT_ID (1)                      */
    0x09, 0x01, /*   USAGE (Pointer)                    */
    0xa1, 0x00, /*   COLLECTION (Physical)              */
    0x05, 0x09, /*     USAGE_PAGE (Button)              */
    0x19, 0x01, /*     USAGE_MINIMUM (Button 1)         */
    0x29, 0x03, /*     USAGE_MAXIMUM (Button 3)         */
    0x15, 0x00, /*     LOGICAL_MINIMUM (0)              */
    0x25, 0x01, /*     LOGICAL_MAXIMUM (1)              */
    0x95, 0x03, /*     REPORT_COUNT (3)                 */
    0x75, 0x01, /*     REPORT_SIZE (1)                  */
    0x81, 0x02, /*     INPUT (Data,Var,Abs)             */
    0x95, 0x01, /*     REPORT_COUNT (1)                 */
    0x75, 0x05, /*     REPORT_SIZE (5)                  */
    0x81, 0x01, /*     INPUT (Cnst,Ary,Abs)             */
    0x05, 0x01, /*     USAGE_PAGE (Generic Desktop)     */
    0x09, 0x30, /*     USAGE (X)                        */
    0x09, 0x31, /*     USAGE (Y)                        */
    0x09, 0x38, /*     USAGE (Wheel)                    */
    0x15, 0x81, /*     LOGICAL_MINIMUM (-127)           */
    0x25, 0x7f, /*     LOGICAL_MAXIMUM (127)            */
    0x75, 0x08, /*     REPORT_SIZE (8)                  */
    0x95, 0x03, /*     REPORT_COUNT (3)                 */
    0x81, 0x06, /*     INPUT (Data,Var,Rel)             */
    0xc0,       /*   END_COLLECTION                     */


    // Keyboard
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x06, // USAGE (Keyboard)
    0xa1, 0x01, // COLLECTION (Application)
    0x85, 0x02, //   REPORT_ID (2)
    0x05, 0x07, //     USAGE_PAGE (Key Codes)
    0x19, 0xE0, //     USAGE_MINIMUM (224)
    0x29, 0xE7, //     USAGE_MAXIMUM (231)
    0x15, 0x00, //     LOGICAL_MINIMUM (0)
    0x25, 0x01, //     LOGICAL_MAXIMUM (1)
    0x75, 0x01, //     REPORT_SIZE (1)
    0x95, 0x08, //     REPORT_COUNT (8)
    0x81, 0x02, //     INPUT (Data,Var,Abs)
    0x95, 0x01, //     REPORT_COUNT (1)
    0x75, 0x08, //     REPORT_SIZE (8)
    0x81, 0x01, //     INPUT (Cnst)
    0x95, 0x05, //     REPORT_COUNT (5)
    0x75, 0x01, //     REPORT_SIZE (1)
    0x05, 0x08, //     USAGE_PAGE (LEDS)
    0x19, 0x01, //     USAGE_MINIMUM (1)
    0x29, 0x05, //     USAGE_MAXIMUM (5)
    0x91, 0x02, //     OUTPUT(Data,Var,Abs)
    0x95, 0x01, //     REPORT_COUNT (1)
    0x75, 0x03, //     REPORT_SIZE (3)
    0x91, 0x01, //     OUTPUT(Cnst)
    0x95, 0x06, //     REPORT_COUNT (6)
    0x75, 0x08, //     REPORT_SIZE (8)
    0x15, 0x00, //     LOGICAL_MINIMUM (0)
    0x25, 0x65, //     LOGICAL_MAXIMUM (101)
    0x05, 0x07, //     USAGE_PAGE (Key Codes)
    0x19, 0x00, //     USAGE_MINIMUM (0)
    0x29, 0x65, //     USAGE_MAXIMUM (101)
    0x81, 0x00, //     INPUT (Data, Array)
    0xc0,       //   END_COLLECTION



    0x09, 0x3c, /*   USAGE (Motion Wakeup)              */
    0x05, 0xff, /*   USAGE_PAGE (Vendor Defined Page 1) */
    0x09, 0x01, /*   USAGE (Vendor Usage 1)             */
    0x15, 0x00, /*   LOGICAL_MINIMUM (0)                */
    0x25, 0x01, /*   LOGICAL_MAXIMUM (1)                */
    0x75, 0x01, /*   REPORT_SIZE (1)                    */
    0x95, 0x02, /*   REPORT_COUNT (2)                   */
    0xb1, 0x22, /*   FEATURE (Data,Var,Abs,NPrf)        */
    0x75, 0x06, /*   REPORT_SIZE (6)                    */
    0x95, 0x01, /*   REPORT_COUNT (1)                   */
    0xb1, 0x01, /*   FEATURE (Cnst,Ary,Abs)             */
    0xc0        /* END_COLLECTION                       */
};

const struct usb_device_descriptor dev_descr =
{
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 64,
    .idVendor = 0x0483,
    .idProduct = 0x5710,
    .bcdDevice = 0x0200,
    .iManufacturer = 1,
    .iProduct = 2,
    .iSerialNumber = 3,
    .bNumConfigurations = 1,
};
