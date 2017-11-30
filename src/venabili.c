#include <stdlib.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/hid.h>

#include "usb.h"

/* Define this to include the DFU APP interface. */
#define INCLUDE_DFU_INTERFACE

#ifdef INCLUDE_DFU_INTERFACE
#include <libopencm3/cm3/scb.h>
#include <libopencm3/usb/dfu.h>
#endif

static usbd_device *usbd_dev;


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
		/* .bcdHID = 0x0100, */
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
	/* .bInterval = 0x20, */
	.bInterval = 0x0A,
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

/* Buffer to be used for control requests. */
uint8_t usbd_control_buffer[128];

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

	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
	/* SysTick interrupt every N clock pulses: set reload to N-1 */
	systick_set_reload(99999);
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

int main(void)
{
	rcc_clock_setup_in_hsi_out_48mhz();

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

    usb_reenumerate();

	usbd_dev = usbd_init(&st_usbfs_v1_usb_driver, &dev_descr, &config, usb_strings, 3, usbd_control_buffer, sizeof(usbd_control_buffer));
	usbd_register_set_config_callback(usbd_dev, hid_set_config);

	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, GPIO11);
	gpio_clear(GPIOB, GPIO11);

    nvic_enable_irq(NVIC_USB_HP_CAN_TX_IRQ);
    nvic_enable_irq(NVIC_USB_LP_CAN_RX0_IRQ);

	while (1)
    {
		/* for (int i = 0; i < 1000; i++) // enough for the enumeration to work */
		/* for (int i = 0; i < 500000; i++) // Enumerations brakes (to much time) */
		/* 	__asm__("nop"); */
        /* gpio_toggle(GPIOB, GPIO11); */
    }
}

void usb_hp_can_tx_isr(void) { usbd_poll(usbd_dev); }
void usb_lp_can_rx0_isr(void) { usbd_poll(usbd_dev); }


// Send mouse signal
/* void sys_tick_handler(void) */
/* { */
/* 	static int x = 0; */
/* 	static int dir = 1; */
/* 	uint8_t buf[5] = {0, 0, 0, 0, 0}; */

/* 	buf[0] = 0x01; */
/* 	buf[2] = dir; */
/* 	buf[3] = dir; */
/* 	x += dir; */
/* 	if (x > 30) */
/* 		dir = -dir; */
/* 	if (x < -30) */
/* 		dir = -dir; */

/* 	usbd_ep_write_packet(usbd_dev, 0x81, buf, 5); */
/* } */


// Send keyboard signal
void sys_tick_handler(void)
{
    static int x = 0;
	uint8_t buf[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	buf[0] = 0x02;

    if (x == 0)
    {
        x = 1;
        // A down
        buf[1] = 0x40;
        buf[3] = 0x04;
        usbd_ep_write_packet(usbd_dev, 0x81, buf, 9);
    }
    else
    {
        x = 0;
        // A up
        buf[1] = 0x40;
        buf[3] = 0x00;
        usbd_ep_write_packet(usbd_dev, 0x81, buf, 9);
    }

}
