#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");   //内核2.6以上版本建议我们加上这个license

static int hello_init(void)  //驱动入口
{
	printk(KERN_ALERT "Hello, world\n");
	printk("Hello, world 222\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
