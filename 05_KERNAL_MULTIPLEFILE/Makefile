
 obj-m += STARTSTOP.o
STARTSTOP-objs := START.o STOP.o

PWD := $(CURDIR)

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
