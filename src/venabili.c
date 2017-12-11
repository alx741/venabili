#include <stdlib.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.h"
#include "usb_keys.h"
#include "usb_keyboard.h"
#include "sensing.h"

#include "keys.h"
#include "keyboard.h"

int main(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    usb_init();
    keyboard_sensing_init();
    keyboard_init();

    // FIXME: debug only
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	gpio_clear(GPIOB, GPIO13);

    Mapkey layer0[NROWS][NCOLS] =
    {
        { {k_a, k_empty }, {k_empty, m_rshift} },
        { {k_a, k_empty}, {k_open_paren, m_lshift} },
        { {k_space, k_empty}, {k_empty, LS(1)}},
        { {k_empty, k_empty}, {k_close_paren, m_rshift}},
    };

    Mapkey layer1[NROWS][NCOLS] =
    {
        { {m_up, k_empty }, {k_empty, m_rshift} },
        { {m_down, k_empty}, {k_b, m_rshift} },
        { {k_space, k_empty}, {k_empty, k_empty}},
        { {k_empty, k_empty}, {k_empty, m_rshift}},
    };


    add_layer(layer0);
    add_layer(layer1);


    while (1)
    {
    }
}

void sys_tick_handler(void)
{
    Key pressed_keys[NKEYS] = {0};

    sense_keys();
    select_layer();
    int n_pressed_keys = map_layer(pressed_keys);
    apply_modifiers(pressed_keys, n_pressed_keys);
    execute(pressed_keys, n_pressed_keys);
}

/* USB ISR handlers */
void usb_hp_can_tx_isr(void)
{
    usbd_poll(usbd_dev);
}
void usb_lp_can_rx0_isr(void)
{
    usbd_poll(usbd_dev);
}
