#include <stdlib.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.c"

static usbd_device *usbd_dev;
uint8_t usbd_control_buffer[128];

int main(void)
{
	rcc_clock_setup_in_hsi_out_48mhz();

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
    usbd_dev = usb_init(usbd_control_buffer);

	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, GPIO11);
	gpio_clear(GPIOB, GPIO11);

    nvic_enable_irq(NVIC_USB_HP_CAN_TX_IRQ);
    nvic_enable_irq(NVIC_USB_LP_CAN_RX0_IRQ);

	while (1)
    {
        // halt
    }
}

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

// USB ISR handlers
void usb_hp_can_tx_isr(void) { usbd_poll(usbd_dev); }
void usb_lp_can_rx0_isr(void) { usbd_poll(usbd_dev); }

