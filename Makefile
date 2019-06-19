ifneq ($(KERNELRELEASE),)
obj-m := myMPU9250.o
else
KDIR := $(HOME)/linux-kernel-labs/src/linux
all:
	$(MAKE) -C $(KDIR) M=$$PWD
endif
