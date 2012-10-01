PREFIX		 = arm-cortex_a8-linux-gnueabi
CFLAGS		:= -fno-stack-protector -fno-builtin -nostdinc -fPIC -D__LOADER__ -Os
LDFLAGS		:= -static -nostdlib -fPIC
ASFLAGS		:= -c -x assembler-with-cpp -D__LOADER__

ELF_TARGET	 = boot.elf
RAW_TARGET	 = boot

CC		 = $(PREFIX)-gcc
AS		 = $(PREFIX)-gcc
LD 		 = $(PREFIX)-gcc
OBJCOPY		 = $(PREFIX)-objcopy

LD_SCRIPT	:= ld-script
ASM_OBJS	:= init.o
C_OBJS		:= main.o images.o console.o vsprintf.o printf.o memstr.o atag.o gpt.o crc32.o hw_misc.o
OBJS		:= $(ASM_OBJS) $(C_OBJS)

VERSION		 = $(shell hg -q id 2>/dev/null || echo unknown)
CFLAGS		+= $(CFLAGS) -DLDR_VERSION=\"$(VERSION)\"

.PHONY		 : all clean install
all:		$(RAW_TARGET)
clean:
	rm -f $(OBJS) $(ELF_TARGET) $(RAW_TARGET)

$(ELF_TARGET):	$(OBJS) $(LD_SCRIPT)
	$(LD) -T$(LD_SCRIPT) $(LDFLAGS) -o $@ $(OBJS)
$(RAW_TARGET):	$(ELF_TARGET)
	$(OBJCOPY) -O binary -R .note -R .comment -S $< $@


.SECONDEXPANSION:
$(ASM_OBJS):	$$(patsubst %.o,%.S,$$@)
	$(AS) $(ASFLAGS) -o $@ $^
$(C_OBJS):	$$(patsubst %.o,%.c,$$@)
	$(CC) $(CFLAGS) -c $^

