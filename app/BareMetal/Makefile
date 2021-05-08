# Name: Makefile
# Author: <insert your name here>
# Copyright: <insert your copyright message here>
# License: <insert your license reference here>

# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected.
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.

DEVICE     = attiny3217
CLOCK      = 20000000
PROGRAMMER = -C../../optiboot_x/avrdude.conf -cxplainedpro_updi -Pusb 
OBJECTS    = main.o
FUSES      = -Ufuse0:w:0x00:m -Ufuse1:w:0x00:m -Ufuse2:w:0x02:m -Ufuse4:w:0x00:m -Ufuse5:w:0b11000100:m -Ufuse6:w:0x04:m -Ufuse7:w:0x00:m -Ufuse8:w:0x02:m


######################################################################
######################################################################

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-g++ -I "Microchip.ATtiny_DFP.2.6.122/include" -B "Microchip.ATtiny_DFP.2.6.122/gcc/dev/attiny3217" -D__ATtiny3217__ -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -Wl,--gc-sections -Wl,--section-start=.text=0x200

# symbolic targets:
all:	main.hex

.cpp.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.cpp.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c