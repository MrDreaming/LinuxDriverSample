/**

$ insmod hello.ko 

$ lsmod

$ cat /proc/devices 
	>>> 251 second
	
$ mknod /dev/second c 251 7

$ rm /dev/second

$ rmmod hello

*/
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <linux/timer.h>
#include <asm/atomic.h>


// cannot DEVICEID_MAJOR=0 and DEVICEID_MINOR!=0
// you should set DEVICEID_MAJOR=DEVICEID_MINOR=0
// otherwise $ cat /proc/devices cannot delete after rmmod 
#define DEVICEID_MAJOR  	0 // 0 will call alloc_chrdev_region
#define DEVICEID_MINOR 		0 // 7 // 0
static int second_major = DEVICEID_MAJOR;

struct second_dev{
	struct cdev cdev;
	atomic_t counter;
	struct timer_list s_timer;
};

struct second_dev *second_devp;

static void second_timer_handle(unsigned long arg){
	mod_timer(&second_devp->s_timer, jiffies + HZ);
	atomic_inc(&second_devp->counter);
	printk(KERN_ERR "current jiffies is %ld\n",jiffies);
}


int second_open(struct inode *inode, struct file *filp){
	init_timer(&second_devp->s_timer);
	second_devp->s_timer.function = &second_timer_handle;
	second_devp->s_timer.expires = jiffies + HZ;
	add_timer(&second_devp->s_timer);
	atomic_set(&second_devp->counter, 0);
	return 0; 
}


int second_release(struct inode *inode, struct file *filp){
	del_timer(&second_devp->s_timer);
	return 0;
}


static ssize_t second_read(struct file *filp, char __user *buf, size_t count, 
	loff_t *ppos){
	int counter;
	counter = atomic_read(&second_devp->counter);
	if (put_user(counter, (int *)buf)){
		return -EFAULT;
	}else{
		return sizeof(unsigned int);
	}
}


static const struct file_operations second_fops ={
	.owner = THIS_MODULE,
	.open = second_open,
	.release = second_release,
	.read = second_read,
};


static void second_setup_cdev(struct second_dev *dev){
	int err, devno = MKDEV(second_major, DEVICEID_MINOR);
	cdev_init(&dev->cdev, &second_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &second_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err){
		printk(KERN_NOTICE "Error %d add second%d", err, DEVICEID_MINOR);
	}
}



int second_init(void){
	int ret;
	dev_t devno = MKDEV(second_major, DEVICEID_MINOR);
	if (second_major){
		ret = register_chrdev_region(devno, 1, "second");
		printk("major(static)=%d\n", second_major);
	}else{
		ret = alloc_chrdev_region(&devno, 0, 1, "second");
		second_major = MAJOR(devno);
		printk("major(alloc)=%d\n", second_major);
	}
	if (ret < 0){
		return ret;
	}
	second_devp = kmalloc(sizeof(struct second_dev), GFP_KERNEL);
	if (!second_devp){
		ret = -ENOMEM;
		goto fail_malloc;
	}
	memset(second_devp, 0, sizeof(struct second_dev));
	second_setup_cdev(second_devp);
	return 0;
	fail_malloc:
		unregister_chrdev_region(devno, 1);

	return 0;
}


void second_exit(void){
	cdev_del(&second_devp->cdev);
	kfree(second_devp);
	printk("exit : second_major=%d\n", second_major);
	unregister_chrdev_region(MKDEV(second_major, DEVICEID_MINOR), 1);
}

MODULE_AUTHOR("dreaming Microelectronic Ltd.");
MODULE_LICENSE("Dual BSD/GPL");
module_param(second_major, int, S_IRUGO);
module_init(second_init);
module_exit(second_exit);

MODULE_DESCRIPTION("dreaming timer.demo driver");
MODULE_ALIAS("dreaming timer.demo");
//MODULE_LICENSE("GPL");
//MODULE_LICENSE("Dual BSD/GPL");


