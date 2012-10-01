#EXTRA_CFLAGS += -march=armv7-a -mtune=cortex-a8 -D__PLAT_TI_OMAP3430__ -Wall 
EXTRA_CFLAGS += -DEMU_UART3
KDIR=/home/czesiek/kernel/MILS2_U6_4.1/kernel/omap3
ARCH=arm
CROSS_COMPILE=arm-cortex_a8-linux-gnueabi-

obj-m += 2ndboot.o
2ndboot-objs := hboot.o buffers.o crc32.o cache-v7.o board-mapphone-emu_uart.o 

all:                                                                                                                                         
	PATH=$(CROSS_PATH):$(PATH) CROSS_COMPILE=$(CROSS_COMPILE) ARCH=$(ARCH) make -C $(KDIR) M=$(PWD) modules

clean:                                                                                                                                       
	PATH=$(CROSS_PATH):$(PATH) CROSS_COMPILE=$(CROSS_COMPILE) ARCH=$(ARCH) make -C $(KDIR) M=$(PWD) clean
	rm -f *.order                                                                                                                            

