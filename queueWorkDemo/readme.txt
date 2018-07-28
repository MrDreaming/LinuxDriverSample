[root@arm9-mk /mnt]$ ls

Makefile            modules.order       queueWordMod.ko     queueWordMod.mod.o
Module.symvers      queueWordMod.c      queueWordMod.mod.c  queueWordMod.o

[root@arm9-mk /mnt]$ insmod queueWordMod.ko

Create workqueue successful!
first ret=1!
delay_work_init:ret=1,i=0
delay_work_init:ret=1,i=1
delay_work_init:ret=1,i=2
#####
delay_work_func:15
delay_work_func:i=0
delay_work_func:i=1
delay_work_func:i=2
delay_work_func:i=3
delay_work_func:i=4
second ret=0!

[root@arm9-mk /mnt]$ rmmod queueWordMod

