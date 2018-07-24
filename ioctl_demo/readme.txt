
open/read/write/ioctl 的使用

例程来自于网络
https://blog.csdn.net/taotaost/article/details/76592645

ubuntu:~/ioctl_demo$ make
ubuntu:~/ioctl_demo$ arm-none-linux-gnueabi-gcc main.c


$ insmod demo.ko
$ lsmod
$ cat /proc/devices
$ mknod /dec/sunny c 224 0
$
$ ./a.out

$ ./a.out 
[demo_open successfully]
open /dev/sunny successfully[demo_write successfully]

[demo_llseek successfully]
[demo_read successfully]
read successfully: yangjin[ioctl command 1 successfully]

ioctl command 1 successfully

$
$
$
