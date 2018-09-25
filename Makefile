CPU = HR8P506

# put your *.o targets here, make should handle the rest!
SRCS  = main.c 
SRCS += Libraries/CMSIS/system_HR8P506.c
#SRCS += port.c
SRCS += systick.c
SRCS += uart.c
SRCS += misc.c
SRCS += wdt.c
SRCS += keys.c
SRCS += leds.c

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)
PROJ_NAME=HR8P506_TEST

# Location of the Libraries folder from the STM32F0xx Standard Peripheral Library
STD_PERIPH_LIB=Libraries

# Location of the linker scripts
LDSCRIPT_INC=Device/ldscripts

# that's it, no need to change anything below this line!

###################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size

DEFS = -D$(CPU)

CFLAGS  = -Wall -g -std=c99 -Os  
#CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m0 -march=armv6s-m
CFLAGS += -mlittle-endian -mcpu=cortex-m0  -march=armv6-m -mthumb
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections -Wl,-Map=$(PROJ_NAME).map $(DEFS)

###################################################

vpath %.c FreeRTOS src
vpath %.a $(STD_PERIPH_LIB)

ROOT=$(shell pwd)

CFLAGS += -I inc -I $(STD_PERIPH_LIB) -I $(STD_PERIPH_LIB)/CMSIS
CFLAGS += -I $(STD_PERIPH_LIB)/CMSIS/Include -I $(STD_PERIPH_LIB)/HR8P506_StdPeriph_Driver/inc
CFLAGS += -include $(STD_PERIPH_LIB)/hr8p506_conf.h

ifeq ($(CPU), HR8P506)
SRCS += $(STD_PERIPH_LIB)/CMSIS/Device/startup_HR8P506.s # add startup file to build
endif

OBJS = $(SRCS:.c=.o)

###################################################

.PHONY: lib proj

all: lib proj

lib:
	$(MAKE) -C $(STD_PERIPH_LIB)

proj: 	$(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(STD_PERIPH_LIB) -lhr8p506 -L$(LDSCRIPT_INC) -Thr8p506.ld
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(OBJDUMP) -St $(PROJ_NAME).elf >$(PROJ_NAME).lst
	$(SIZE) $(PROJ_NAME).elf
	
clean:
	find ./ -name '*~' | xargs rm -f	
	rm -f *.o
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).map
	rm -f $(PROJ_NAME).lst
	rm -f src/*.bak

reallyclean: clean
	$(MAKE) -C $(STD_PERIPH_LIB) clean


