obj-m:= lab2-2.o
KDIR:= /lib/modules/$(shell uname -r)/build
PWD:= $(shell pwd)
 
defualt:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) chean
CONFIG_MODULE_SIG=n
