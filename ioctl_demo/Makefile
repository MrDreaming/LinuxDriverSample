obj-m := demo.o
KERNEL_PATH := /home/hp/anyka/build-test
CROSS_COMPILE =arm-none-linux-gnueabi-
CC :=$(CROSS_COMPILE)gcc
LD :=$(CROSS_COMPILE)ld
PWD := $(shell pwd)
all:  
	make -C $(KERNEL_PATH) M=$(PWD) modules
clean:  
	make -C $(KERNEL_PATH) M=$(PWD) clean 