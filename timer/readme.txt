
$ insmod hello.ko 

$ lsmod

$ cat /proc/devices 
	>>> 251 second
	
$ mknod /dev/second c 251 0

$ rm /dev/second

$ rmmod hello

使用例程可以编译

$ arm-none-linux-gnueabi-gcc testdemo.c
$ ./a.out

例程功能
1 定时器的使用
2 根据对应的主设备号和子设备号建立设备节点
3 读取设备
4 删除设备节点
5 卸载驱动模块
