##
## This file is part of the libopencm3 project.
##
## Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
##
## This library is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this library.  If not, see <http://www.gnu.org/licenses/>.
##

SRC_DIR=./
BINARY = $(SRC_DIR)/main
LDSCRIPT=$(SRC_DIR)/f103x8_boot_offset.ld
OPENCM3_DIR=../lib/libopencm3

SCRIPTS_DIR= ../scripts/

OBJS += usb.o
OBJS += usb_keyboard.o
OBJS += usb_mouse.o
OBJS += sensing.o
OBJS += keys.o
OBJS += macros.o
OBJS += keyboard.o

include ./libopencm3.target.mk

all: $(BINARY).bin
	@$(SCRIPTS_DIR)/checks.sh

$(BINARY).bin: $(BINARY).elf
	arm-none-eabi-objcopy -O binary $< $@

burn: $(BINARY).bin
	dfu-util -a 0 -d 0483:df11 -s 0x08002000:leave -D $<

burn_low: $(BINARY).bin
	st-flash write $< 0x8002000

check:
	sudo lshw -class input
