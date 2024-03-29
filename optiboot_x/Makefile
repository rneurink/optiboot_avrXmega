# Makefile for AVR Mega-0 (4809), Tiny-0, and Tiny-1 version of Optiboot
# Bill Westfield, 2019
# $Id$
#
# Edit History
# Sep-2019 refactor from the normal AVR Makefile.
# * Copyright 2013-2019 by Bill Westfield.  Part of Optiboot.
# * This software is licensed under version 2 of the Gnu Public Licence.
# * See optiboot.c for details.

HELPTEXT = "\n"
#----------------------------------------------------------------------
#
# program name should not be changed...
PROGRAM    = optiboot_x
MF:= $(MAKEFILE_LIST)

# export symbols to recursive makes (for ISP)
export

# defaults
MCU_TARGET = atmega4809

LDSECTIONS  = -Wl,-section-start=.text=0 \
	      -Wl,--section-start=.application=0x200 \
	      -Wl,--section-start=.version=0x1fe

BAUD_RATE=115200


TOOLROOT = ../tools

GCCROOT = $(TOOLROOT)/avr/bin/
AVRDUDE_CONF = -C$(TOOLROOT)/avr/etc/avrdude.conf


#
# End of build environment code.


CC         = $(GCCROOT)avr-gcc
RCC        = $(abspath $(CC))
#$(info wildcard ("$(wildcard $(CC))",""))
ifndef PRODUCTION
$(info Using Compiler at: ${RCC})
endif


# If we have a PACKS directory specified, we should use it...
ifdef PACKS
PACK_OPT= -I $(PACKS)/include/ -B $(PACKS)/gcc/dev/$*
ifndef PRODUCTION
$(info   and Chip-defining PACKS at ${PACKS})
endif
endif


OPTIMIZE = -Os -fno-split-wide-types -mrelax

# Override is only needed by avr-lib build system.

override CFLAGS  = -g -Wall $(OPTIMIZE)
override LDFLAGS = $(LDSECTIONS) -Wl,--relax -nostartfiles -nostdlib

OBJCOPY        = $(GCCROOT)avr-objcopy
OBJDUMP        = "$(GCCROOT)avr-objdump"
SIZE           = $(GCCROOT)avr-size

include parse_options.mk

.PRECIOUS: optiboot_%.elf

ifndef PRODUCTION
LISTING= $(OBJDUMP) -S
else
LISTING= @true
endif



#---------------------------------------------------------------------------
# "Chip-level Platform" targets.
# A "Chip-level Platform" compiles for a particular chip, but probably does
# not have "standard" values for things like clock speed, LED pin, etc.
# Makes for chip-level platforms should usually explicitly define their
# options like: "make atmega4809 UARTTX=A4 LED=D0"
#---------------------------------------------------------------------------
#
# Mega0, tiny0, tiny1 don't really have any chip-specific requirements.
#
# Note about fuses:
#  The fuses are defined in the source code.  There are 9!
#  Be sure to use a programmer that will program the fuses from the object file.
#
#---------------------------------------------------------------------------
#

HELPTEXT += "\n-------------\n\n"


optiboot_%.hex: optiboot_%.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O ihex $< $@

optiboot_%.elf:	optiboot_x.c FORCE
	$(CC) $(CFLAGS) $(CPU_OPTIONS) $(LED_OPTIONS) $(UART_OPTIONS) $(POR_CMD) $(COMMON_OPTIONS) $(LDFLAGS) $(PACK_OPT) -mmcu=$(TARGET) -o $@ $<
	$(SIZE) $@
	$(LISTING) $@ > optiboot_$*.lst


#---------------------------------------------------------------------------
# "Board-level Platform" targets.
# A "Board-level Platform" implies a manufactured platform with a particular
# AVR_FREQ, LED, and so on.  Parameters are not particularly changeable from
# the "make" command line.
# Most of the board-level platform builds should envoke make recursively
#  appropriate specific options
#---------------------------------------------------------------------------

## For tinyAVR 0/1-series with default UART port mapping
HELPTEXT += "Generic 8 pin dev board, default serial pins, 8 second timeout, LED on A3\n"
tinyxy2: TARGET = attiny412
tinyxy2:
	$(MAKE) -f $(MF) optiboot_txy2.hex UARTTX=A6 TIMEOUT=8 LED=A3

HELPTEXT += "Generic 14~24 pin dev board, default serial pins, 8 second timeout, LED on A7\n"
tinyxyz: TARGET = attiny3217
tinyxyz:
	$(MAKE) -f $(MF) optiboot_txyz.hex UARTTX=B2 TIMEOUT=8 LED=A7

HELPTEXT += "Ziuz TOF sensor, serial on B2, LED on C1, timout 8 seconds"
ziuz_tof: TARGET = attiny3217
ziuz_tof:
	$(MAKE) -f $(MF) optiboot_ziuz_tof.hex UARTTX=B2 TIMEOUT=8 LED=C1

HELPTEXT += "Ziuz TOF sensor, serial on B2, LED on C1, timout 8 seconds"
ziuz_tof_1617: TARGET = attiny1617
ziuz_tof_1617:
	$(MAKE) -f $(MF) optiboot_ziuz_tof_1617.hex UARTTX=B2 TIMEOUT=8 LED=C1

HELPTEXT += "Ziuz backlight driver, serial on A1, LED on C3, timout 8 seconds"
ziuz_bld_1617: TARGET = attiny1617
ziuz_bld_1617:
	$(MAKE) -f $(MF) optiboot_ziuz_bld_1617.hex UARTTX=A1 TIMEOUT=8 LED=C3

#HELPTEXT += "target drazzy*4      - Dr Azzy's 14pin dev boards.\n"
#tinyxy4: TARGET = attiny1614
#tinyxy4:
#	$(MAKE) -f $(MF) optiboot_txy4.hex UARTTX=B2 TIMEOUT=8 LED=A7

#HELPTEXT += "target drazzy*6      - Dr Azzy's 20pin dev boards.\n"
#tinyxy6: TARGET = attiny3216
#tinyxy6:
#	$(MAKE) -f $(MF) optiboot_txy6.hex UARTTX=B2 TIMEOUT=8 LED=A7

HELPTEXT += "target drazzy*7      - Dr Azzy's 24pin dev boards.\n"
tinyxy7: TARGET = attiny3217
tinyxy7:
	$(MAKE) -f $(MF) optiboot_txy7.hex UARTTX=B2 TIMEOUT=8 LED=A7

## For tinyAVR 0/1-series with alternate UART port mapping
HELPTEXT += "Generic 8 pin dev board, alt serial pins, 8 second timeout, LED on A7\n"
tinyxy2alt: TARGET = attiny412
tinyxy2alt:
	$(MAKE) -f $(MF) optiboot_txy2_alt.hex UARTTX=A1 TIMEOUT=8 LED=A7

HELPTEXT += "Generic 14~24 pin dev board, alternate serial pins, 8 second timeout, LED on A7\n"
tinyxyzalt: TARGET = attiny3217
tinyxyzalt:
	$(MAKE) -f $(MF) optiboot_txyz_alt.hex UARTTX=A1 TIMEOUT=8 LED=A7


#HELPTEXT += "target drazzy*4      - Dr Azzy's 14pin dev boards.\n"
#tinyxy4alt: TARGET = attiny1614
#tinyxy4alt:
#	$(MAKE) -f $(MF) optiboot_txy4_alt.hex UARTTX=A1 TIMEOUT=8 LED=A7

#HELPTEXT += "target drazzy*6      - Dr Azzy's 20pin dev boards.\n"
#tinyxy6alt: TARGET = attiny3216
#tinyxy6alt:
#	$(MAKE) -f $(MF) optiboot_txy6_alt.hex UARTTX=A1 TIMEOUT=8 LED=A7

#HELPTEXT += "target drazzy*7      - Dr Azzy's 24pin dev boards.\n"
#tinyxy7alt: TARGET = attiny3217
#tinyxy7alt:
#	$(MAKE) -f $(MF) optiboot_txy7_alt.hex UARTTX=A1 TIMEOUT=8 LED=A7

## For tinyAVR 0/1-series for use when UPDI is reset
## For tinyAVR 0/1-series with default UART port mapping
HELPTEXT += "Generic 8 pin dev board, default serial pins, 1 second timeout, doesn't run on POR, LED on A3\n"
tinyxy2rst: TARGET = attiny412
tinyxy2rst:
	$(MAKE) -f $(MF) optiboot_txy2_rst.hex START_APP_ON_POR=1 UARTTX=A6 TIMEOUT=1 LED=A3

HELPTEXT += "Generic 14~24 pin dev board, default serial pins, 1 second timeout, doesn't run on POR, LED on A7\n"
tinyxyzrst: TARGET = attiny3217
tinyxyzrst:
	$(MAKE) -f $(MF) optiboot_txyz_rst.hex START_APP_ON_POR=1 UARTTX=B2 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*4      - Dr Azzy's 14pin dev boards.\n"
#tinyxy4rst: TARGET = attiny1614
#tinyxy4rst:
#	$(MAKE) -f $(MF) optiboot_txy4_rst.hex START_APP_ON_POR=1 UARTTX=B2 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*6      - Dr Azzy's 20pin dev boards.\n"
#tinyxy6rst: TARGET = attiny3216
#tinyxy6rst:
#	$(MAKE) -f $(MF) optiboot_txy6_rst.hex START_APP_ON_POR=1 UARTTX=B2 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*7      - Dr Azzy's 24pin dev boards.\n"
#tinyxy7rst: TARGET = attiny3217
#tinyxy7rst:
#	$(MAKE) -f $(MF) optiboot_txy7_rst.hex START_APP_ON_POR=1 UARTTX=B2 TIMEOUT=1 LED=A7
## For tinyAVR 0/1-series with alternate UART port mapping
HELPTEXT += "Generic 8 pin dev board, alternate serial pins, 1 second timeout, doesn't run on POR, LED on A7\n"
tinyxy2altrst: TARGET = attiny412
tinyxy2altrst:
	$(MAKE) -f $(MF) optiboot_txy2_alt_rst.hex START_APP_ON_POR=1 UARTTX=A1 TIMEOUT=1 LED=A7

HELPTEXT += "Generic 14~24 pin dev board, default serial pins, 1 second timeout, doesn't run on POR, LED on A7\n"
tinyxyzaltrst: TARGET = attiny3217
tinyxyzaltrst:
	$(MAKE) -f $(MF) optiboot_txyz_alt_rst.hex START_APP_ON_POR=1 UARTTX=A1 TIMEOUT=1 LED=A7


#HELPTEXT += "target drazzy*4      - Dr Azzy's 14pin dev boards.\n"
#tinyxy4altrst: TARGET = attiny1614
#tinyxy4altrst:
#	$(MAKE) -f $(MF) optiboot_txy4_alt_rst.hex START_APP_ON_POR=1 UARTTX=A1 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*6      - Dr Azzy's 20pin dev boards.\n"
#tinyxy6altrst: TARGET = attiny3216
#tinyxy6altrst:
#	$(MAKE) -f $(MF) optiboot_txy6_alt_rst.hex START_APP_ON_POR=1 UARTTX=A1 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*7      - Dr Azzy's 24pin dev boards.\n"
#tinyxy7altrst: TARGET = attiny3217
#tinyxy7altrst:
#	$(MAKE) -f $(MF) optiboot_txy7_alt_rst.hex START_APP_ON_POR=1 UARTTX=A1 TIMEOUT=1 LED=A7



## For tinyAVR 0/1-series for use when UPDI is not reset, but using ersatz reset pin
## For tinyAVR 0/1-series with default UART port mapping
HELPTEXT += "Generic 8 pin dev board, default serial pins, 1 second timeout, LED on A3\n"
tinyxy21sec: TARGET = attiny412
tinyxy21sec:
	$(MAKE) -f $(MF) optiboot_txy2_1sec.hex UARTTX=A6 TIMEOUT=1 LED=A3

HELPTEXT += "Generic 14~24 pin dev board, default serial pins, 1 second timeout, LED on A7\n"
tinyxyz1sec: TARGET = attiny3217
tinyxyz1sec:
	$(MAKE) -f $(MF) optiboot_txyz_1sec.hex UARTTX=B2 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*4      - Dr Azzy's 14pin dev boards.\n"
#tinyxy41sec: TARGET = attiny1614
#tinyxy41sec:
#	$(MAKE) -f $(MF) optiboot_txy4_1sec.hex UARTTX=B2 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*6      - Dr Azzy's 20pin dev boards.\n"
#tinyxy61sec: TARGET = attiny3216
#tinyxy61sec:
#	$(MAKE) -f $(MF) optiboot_txy6_1sec.hex UARTTX=B2 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*7      - Dr Azzy's 24pin dev boards.\n"
#tinyxy71sec: TARGET = attiny3217
#tinyxy71sec:
#	$(MAKE) -f $(MF) optiboot_txy7_1sec.hex UARTTX=B2 TIMEOUT=1 LED=A7
## For tinyAVR 0/1-series with alternate UART port mapping
HELPTEXT += "Generic 8 pin dev board, alternate serial pins, 1 second timeout, LED on A7\n"
tinyxy2alt1sec: TARGET = attiny412
tinyxy2alt1sec:
	$(MAKE) -f $(MF) optiboot_txy2_alt_1sec.hex UARTTX=A1 TIMEOUT=1 LED=A7

HELPTEXT += "Generic 14~24 pin dev board, alternate serial pins, 1 second timeout, LED on A7\n"
tinyxyzalt1sec: TARGET = attiny3217
tinyxyzalt1sec:
	$(MAKE) -f $(MF) optiboot_txyz_alt_1sec.hex UARTTX=A1 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*4      - Dr Azzy's 14pin dev boards.\n"
#tinyxy4alt1sec: TARGET = attiny1614
#tinyxy4alt1sec:
#	$(MAKE) -f $(MF) optiboot_txy4_alt_1sec.hex UARTTX=A1 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*6      - Dr Azzy's 20pin dev boards.\n"
#tinyxy6alt1sec: TARGET = attiny3216
#tinyxy6alt1sec:
#	$(MAKE) -f $(MF) optiboot_txy6_alt_1sec.hex UARTTX=A1 TIMEOUT=1 LED=A7

#HELPTEXT += "target drazzy*7      - Dr Azzy's 24pin dev boards.\n"
#tinyxy7alt1sec: TARGET = attiny3217
#tinyxy7alt1sec:
#	$(MAKE) -f $(MF) optiboot_txy7_alt_1sec.hex UARTTX=A1 TIMEOUT=1 LED=A7




HELPTEXT += "target curiosity1607 - Microchip ATtiny1607 Curiosity Nano.\n"
curiosity1607: TARGET = attiny1607
curiosity1607:
	$(MAKE) -f $(MF) optiboot_curiosity1607.hex UARTTX=B2 TIMEOUT=8 LED=B7 LED_INVERT=1

HELPTEXT += "target curiosity4809 - Microchip ATmega4809 Curiosity Nano.\n"
curiosity4809:
	$(MAKE) -f $(MF) optiboot_atmega4809.hex UARTTX=B0 TIMEOUT=8 LED=F5 LED_INVERT=1

HELPTEXT += "target xplained416   - Microchip ATtiny416 Xplained Nano.\n"
xplained416: TARGET = attiny1607
xplained416:
	$(MAKE) -f $(MF) optiboot_xplained416.hex UARTTX=A1 TIMEOUT=8 LED=B5 LED_INVERT=1 BAUD_RATE=57600

HELPTEXT += "target xplained817   - Microchip ATtiny817 Xplained Mini.\n"
xplained817: TARGET = attiny1607
xplained817:
	$(MAKE) -f $(MF) optiboot_xplained817.hex UARTTX=B2 TIMEOUT=8 LED=C0 BAUD_RATE=57600

HELPTEXT += "target xplained3217   - Microchip ATtiny3217 Xplained Mini.\n"
xplained3217: TARGET = attiny3217
xplained3217:
	$(MAKE) -f $(MF) optiboot_xplained3217.hex UARTTX=B2 TIMEOUT=8 LED=B4

HELPTEXT += "target xplained4809  - Microchip ATmega4809 Xplained Pro.\n"
xplained4809:
	$(MAKE) -f $(MF) optiboot_atmega4809.hex UARTTX=C0 TIMEOUT=8 LED=B5 LED_INVERT=1 BAUD_RATE=115200

HELPTEXT += "target freeduino4809 - WestfW ATmega4809 Uno-style board.\n"
freeduino4809:
	$(MAKE) -f $(MF) optiboot_atmega4809.hex UARTTX=B4 TIMEOUT=1 LED=D6 RESETPIN=1

HELPTEXT += "target freeduino4809chip - WestfW ATmega4809 40pin DIP boards.\n"
freeduino4809chip:
	$(MAKE) -f $(MF) optiboot_atmega4809.hex UARTTX=A4 TIMEOUT=1 LED=A7 RESETPIN=1

#---------------------------------------------------------------------------
#
# Generic build instructions
#

FORCE:

isp: $(TARGET) FORCE
	"$(MAKE)" -f Makefile.isp isp TARGET=$(TARGET)

isp-stk500: $(PROGRAM)_$(TARGET).hex
	$(STK500-1)
	$(STK500-2)

#windows "rm" is dumb and objects to wildcards that don't exist
clean:
	@touch  __temp_.o __temp_.elf __temp_.lst __temp_.map
	@touch  __temp_.sym __temp_.lss __temp_.eep __temp_.srec
	@touch __temp_.bin __temp_.hex __temp_.tmp.sh
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex *.tmp.sh

clean_asm:
	rm -rf *.lst

%.lst: %.elf FORCE
	$(OBJDUMP) -h -S $< > $@

%.srec: %.elf FORCE
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O srec $< $@

%.bin: %.elf FORCE
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O binary $< $@

help:
	@echo -e $(HELPTEXT)
