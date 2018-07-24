#include <linux/module.h>
#include <linux/input.h>
 
/**
*
* https://blog.csdn.net/A694543965/article/details/79849831
*
*/
static struct input_dev *button_dev;


static int __init button_init(void){
	int error;
	button_dev = input_allocate_device();
	if (!button_dev) {
		printk(KERN_ERR "button.c: Not enough memory\n");
		error = -ENOMEM;
		return error;
	}
	button_dev->name="I am simplest input subsystem";
	button_dev->evbit[0] = BIT_MASK(EV_KEY);
	button_dev->keybit[BIT_WORD(KEY_UP)] = BIT_MASK(KEY_UP);

	button_dev->id.bustype=BUS_I8042;
	button_dev->id.vendor=0x1111;
	button_dev->id.product=0x2222;
	button_dev->id.version=0x5555;

	// the key-call register into input system
	error = input_register_device(button_dev);
	if (error){
		printk(KERN_ERR "button.c: Failed to register device\n");
		input_free_device(button_dev);
		return error;
	}
	printk(KERN_DEBUG "OK,input subsystem inited!\n");
	return 0;
}


static void __exit button_exit(void){
	input_unregister_device(button_dev);
}

module_init(button_init);
module_exit(button_exit);

MODULE_AUTHOR("dreaming Microelectronic Ltd.");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("dreaming timer.demo driver");
MODULE_ALIAS("dreaming timer.demo");

