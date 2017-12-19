/*
 *  Copyright 2017 Daniel Campoverde C. <alx@sillybytes.net>
 *
 *  This file is part of Venabili.
 *
 *  Venabili is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Venabili is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Venabili.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stddef.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/usb/hid.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.h"

#define INCLUDE_DFU_INTERFACE

#ifdef INCLUDE_DFU_INTERFACE
#include <libopencm3/cm3/scb.h>
#include <libopencm3/usb/dfu.h>
#endif


usbd_device *usbd_dev;
uint8_t usbd_control_buffer[128];


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
    0x29, 0x05, /*     USAGE_MAXIMUM (Button 5)         */
    0x15, 0x00, /*     LOGICAL_MINIMUM (0)              */
    0x25, 0x01, /*     LOGICAL_MAXIMUM (1)              */
    0x95, 0x05, /*     REPORT_COUNT (5)                 */
    0x75, 0x01, /*     REPORT_SIZE (1)                  */
    0x81, 0x02, /*     INPUT (Data,Var,Abs)             */
    0x95, 0x01, /*     REPORT_COUNT (1)                 */
    0x75, 0x03, /*     REPORT_SIZE (3)                  */
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

static const struct {
    struct usb_hid_descriptor hid_descriptor;
    struct {
        uint8_t bReportDescriptorType;
        uint16_t wDescriptorLength;
    } __attribute__((packed)) hid_report;
} __attribute__((packed)) hid_function = {
    .hid_descriptor = {
        .bLength = sizeof(hid_function),
        .bDescriptorType = USB_DT_HID,
        .bcdHID = 0x0101,
        .bCountryCode = 0,
        .bNumDescriptors = 1,
    },
    .hid_report = {
        .bReportDescriptorType = USB_DT_REPORT,
        .wDescriptorLength = sizeof(hid_report_descriptor),
    }
};

const struct usb_endpoint_descriptor hid_endpoint = {
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = 0x81,
    .bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
    .wMaxPacketSize = 0x0F,
    .bInterval = 0x0A, // 10ms polling interval
};

const struct usb_interface_descriptor hid_iface = {
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = 0,
    .bAlternateSetting = 0,
    .bNumEndpoints = 1,
    .bInterfaceClass = USB_CLASS_HID,
    .bInterfaceSubClass = 1, // boot device
    .bInterfaceProtocol = 1, // keyboard boot device
    .iInterface = 0,
    .endpoint = &hid_endpoint,
    .extra = &hid_function,
    .extralen = sizeof(hid_function),
};

#ifdef INCLUDE_DFU_INTERFACE
const struct usb_dfu_descriptor dfu_function = {
    .bLength = sizeof(struct usb_dfu_descriptor),
    .bDescriptorType = DFU_FUNCTIONAL,
    .bmAttributes = USB_DFU_CAN_DOWNLOAD | USB_DFU_WILL_DETACH,
    .wDetachTimeout = 255,
    .wTransferSize = 1024,
    .bcdDFUVersion = 0x011A,
};

const struct usb_interface_descriptor dfu_iface = {
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = 1,
    .bAlternateSetting = 0,
    .bNumEndpoints = 0,
    .bInterfaceClass = 0xFE,
    .bInterfaceSubClass = 1,
    .bInterfaceProtocol = 1,
    .iInterface = 0,

    .extra = &dfu_function,
    .extralen = sizeof(dfu_function),
};
#endif

const struct usb_interface ifaces[] = {{
    .num_altsetting = 1,
    .altsetting = &hid_iface,
#ifdef INCLUDE_DFU_INTERFACE
}, {
    .num_altsetting = 1,
    .altsetting = &dfu_iface,
#endif
}};

const struct usb_config_descriptor config = {
    .bLength = USB_DT_CONFIGURATION_SIZE,
    .bDescriptorType = USB_DT_CONFIGURATION,
    .wTotalLength = 0,
#ifdef INCLUDE_DFU_INTERFACE
    .bNumInterfaces = 2,
#else
    .bNumInterfaces = 1,
#endif
    .bConfigurationValue = 1,
    .iConfiguration = 0,
    .bmAttributes = 0xC0,
    .bMaxPower = 0x32, // TODO: Is this enough power for the LCD display?

    .interface = ifaces,
};

static const char *usb_strings[] = {
    "Daniel Campoverde",
    "Venabili Keyboard",
    "0000-0000-0000-0001",
};

static int hid_control_request(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
            void (**complete)(usbd_device *, struct usb_setup_data *))
{
    (void)complete;
    (void)dev;

    if((req->bmRequestType != 0x81) ||
       (req->bRequest != USB_REQ_GET_DESCRIPTOR) ||
       (req->wValue != 0x2200))
        return 0;

    /* Handle the HID report descriptor. */
    *buf = (uint8_t *)hid_report_descriptor;
    *len = sizeof(hid_report_descriptor);

    return 1;
}

#ifdef INCLUDE_DFU_INTERFACE
static void dfu_detach_complete(usbd_device *dev, struct usb_setup_data *req)
{
    (void)req;
    (void)dev;

    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ,
              GPIO_CNF_OUTPUT_PUSHPULL, GPIO10);
    gpio_set(GPIOA, GPIO10);
    scb_reset_core();
}

static int dfu_control_request(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
            void (**complete)(usbd_device *, struct usb_setup_data *))
{
    (void)buf;
    (void)len;
    (void)dev;

    if ((req->bmRequestType != 0x21) || (req->bRequest != DFU_DETACH))
        return 0; /* Only accept class request. */

    *complete = dfu_detach_complete;

    return 1;
}
#endif

static void hid_set_config(usbd_device *dev, uint16_t wValue)
{
    (void)wValue;
    (void)dev;

    usbd_ep_setup(dev, 0x81, USB_ENDPOINT_ATTR_INTERRUPT, 4, NULL);

    usbd_register_control_callback(
                dev,
                USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
                USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
                hid_control_request);
#ifdef INCLUDE_DFU_INTERFACE
    usbd_register_control_callback(
                dev,
                USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
                USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
                dfu_control_request);
#endif

    // Systick pulse 18 times per second
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
    systick_set_reload(500000);
    systick_interrupt_enable();
    systick_counter_enable();
}

void usb_reenumerate(void)
{
    // Pull down D+ a little bit
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
    gpio_clear(GPIOA, GPIO12);
    for (unsigned i = 0; i < 800000; i++) { __asm__("nop"); }
}

void usb_init()
{
    usbd_device *dev;

    usb_reenumerate();
    dev = usbd_init(&st_usbfs_v1_usb_driver, &dev_descr, &config, usb_strings, 3, usbd_control_buffer, sizeof(usbd_control_buffer));

    usbd_register_set_config_callback(dev, hid_set_config);

    nvic_enable_irq(NVIC_USB_HP_CAN_TX_IRQ);
    nvic_enable_irq(NVIC_USB_LP_CAN_RX0_IRQ);

    usbd_dev = dev;
}
