obj-m += km-session.o

.PHONY: build build-user create-node remove-node clean-user clean

build: build-user
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

build-user: create-node
	cd user; gcc test.c -o TestApp

create-node:
	sudo mknod km-session c 10 100 || exit 0

remove-node:
	sudo rm -f km-session

clean: clean-user
	make -C /lib/modules/`uname -r`/build M=`pwd` clean

clean-user: remove-node
	rm -f user/TestApp

insert-module:
	sudo insmod km-session.ko

remove-module:
	sudo rmmod km-session
