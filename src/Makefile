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

OPENCM3_DIR=../lib/libopencm3
SCRIPTS_DIR= ../scripts/

DEVICE = stm32f103c8

OBJS += usb.o
OBJS += usb_keyboard.o
OBJS += usb_mouse.o
OBJS += sensing.o
OBJS += keys.o
OBJS += macros.o
OBJS += keyboard.o
OBJS += main.o

CFLAGS   += -Os -ggdb3
CPPFLAGS += -MD
LDFLAGS  += -static -nostartfiles
LDLIBS   += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/gcc-config.mk

all: binary.elf binary.hex

flash: $(BINARY).bin
	@echo Enter flash mode now
	@echo Starting flashing process in 5 seconds...
	@sleep 5
	dfu-util -a 0 -d 0483:df11 -s 0x08002000:leave -D $<

flash_low: $(BINARY).bin
	st-flash write $< 0x8002000

check:
	lsbusb -v | grep Venabili

test:
	sudo showkey -s

clean:
	$(Q)$(RM) -rf binary.* *.o *.d generated.*.ld

include $(OPENCM3_DIR)/mk/genlink-rules.mk
include $(OPENCM3_DIR)/mk/gcc-rules.mk
