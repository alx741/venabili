#include <libopencm3/stm32/rtc.h>
#include <libopencm3/cm3/nvic.h>
#include "rtc.h"

void rtc_init(void)
{
    rtc_auto_awake(RCC_LSE, 0x7fff);
    nvic_enable_irq(NVIC_RTC_IRQ);
    rtc_interrupt_enable(RTC_SEC);
}
