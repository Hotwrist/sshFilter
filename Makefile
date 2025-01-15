# Specify the module name (without the .ko extension)
MODULE_NAME := sshFilter

# The source files (.c files) for the module
obj-m := $(MODULE_NAME).o

# If you have multiple source files:
# obj-m := my_module.o
# my_module-objs := file1.o file2.o

# Specify the path to the Linux kernel source
KERNEL_DIR := /lib/modules/$(shell uname -r)/build

# Directory where the current Makefile is located
PWD := $(shell pwd)

# Default target to build the module
all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

# Target to clean the build
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

# Optional: To install the module (requires root)
install:
	sudo cp $(MODULE_NAME).ko /lib/modules/$(shell uname -r)/kernel/drivers/extra/
	sudo depmod
	sudo modprobe $(MODULE_NAME)

# Optional: To remove the module (requires root)
uninstall:
	sudo modprobe -r $(MODULE_NAME)

.PHONY: all clean install uninstall

