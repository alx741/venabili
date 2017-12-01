#include <stdlib.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.c"
#include "keyboard.h"
#include "keys.h"

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
    }
}

// Send keyboard signal
void sys_tick_handler(void)
{
    static int x = 0;

    if (x == 0)
    {
        x = 1;
        report_key(usbd_dev, MOD_LEFT_SHIFT, KEY_A);
    }
    else
    {
        x = 0;
        report_key(usbd_dev, MOD_NONE, KEY_NONE);
    }
}

// USB ISR handlers
void usb_hp_can_tx_isr(void) { usbd_poll(usbd_dev); }
void usb_lp_can_rx0_isr(void) { usbd_poll(usbd_dev); }

