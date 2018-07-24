
输入子系统

在 /dev/input/ 下面生成输入设备节点
使用 input_register_device 接口注册输入设备
不再需要使用 mknod 在目录 /dev/ 下添加设备节点

例程来自网络
https://blog.csdn.net/A694543965/article/details/79849831

这两个命令可以看到新加入的输入子系统设备节点
添加输入模块

admin@ubuntu:~/src/inputSystenDemo$ make

$ insmod inputzzy.ko
$ lsmod
inputzzy 610 0 - Live 0xbf0fb000

$ cat /proc/bus/input/devices 
I: Bus=0011 Vendor=1111 Product=2222 Version=5555
N: Name="I am simplest input subsystem"
P: Phys=
S: Sysfs=/devices/virtual/input/input4
U: Uniq=
H: Handlers=event2 
B: EV=3
B: KEY=80 0 0 0

$ ls /dev/input/
event0  event1  event2


删除输入设备节点
$ rm /dev/input/event2
$ rmmod inputzzy


