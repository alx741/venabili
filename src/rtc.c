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


#include <libopencm3/stm32/rtc.h>
#include <libopencm3/cm3/nvic.h>
#include "rtc.h"

void rtc_init(void)
{
    rtc_auto_awake(RCC_LSE, 0x7fff);
    nvic_enable_irq(NVIC_RTC_IRQ);
    rtc_interrupt_enable(RTC_SEC);
}

int rtc_get_hour(void)
{
    volatile uint32_t c = rtc_get_counter_val();
    return c / 3600;
}

int rtc_get_minute(void)
{
    volatile uint32_t c = rtc_get_counter_val();
    return (c % 3600) / 60;
}

int rtc_get_second(void)
{
    volatile uint32_t c = rtc_get_counter_val();
    return (c % 3600) % 60;
}
