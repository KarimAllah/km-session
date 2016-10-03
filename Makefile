obj-m += km-session.o

.PHONY: build clean

build:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean

insert-module:
	sudo insmod km-session.ko

remove-module:
	sudo rmmod km-session
