#include <linux/sched.h>
#include <linux/init.h>   
#include <linux/module.h> 
#include <linux/workqueue.h> 
#include <linux/proc_fs.h>
#include <linux/delay.h>   
#include <linux/interrupt.h>    
#include <linux/kernel.h> 
struct delayed_work mdwq;  
struct workqueue_struct *mwq;  
void delay_work_func(struct work_struct *work)  
{  
    int i;  
	printk(KERN_INFO "#####\n");  
    printk(KERN_INFO "%s:%d\n",__FUNCTION__,__LINE__);  
    for (i = 0; i < 5; i++) {  
        printk(KERN_ERR "%s:i=%d\n",__FUNCTION__,i);  
        msleep(500);  
    }  
}  
  
static int __init delay_work_init(void)  
{  
    int ret;  
    int i;  
    mwq = create_workqueue("my workqueue");  
    if (!mwq) {  
        printk(KERN_ERR "Create workqueue failed!\n");  
        return 1;     
    }  
    printk(KERN_INFO "Create workqueue successful!\n");  
  
    INIT_DELAYED_WORK(&mdwq, delay_work_func);  
      
    //ret = queue_delayed_work(mwq, &mdwq, 5000);
	ret = queue_delayed_work(mwq, &mdwq, msecs_to_jiffies(3000));
    printk(KERN_INFO "first ret=%d!\n", ret);  
      
    for (i = 0; i < 3; i++) {   
        printk(KERN_INFO "%s:ret=%d,i=%d\n",__FUNCTION__,ret, i);  
        msleep(500);  
    }  
  
    ret = queue_delayed_work(mwq, &mdwq, 0); 
	msleep(5000);  
    printk(KERN_INFO "second ret=%d!\n", ret);  
  
    return 0;  
}  
  
static void __exit delay_work_exit(void)  
{  
    int ret;  
    ret = cancel_delayed_work(&mdwq);  
    flush_workqueue(mwq);  
    destroy_workqueue(mwq);  
    printk(KERN_INFO "Exit! ret=%d\n", ret);  
}  
module_init(delay_work_init);  
module_exit(delay_work_exit);  
MODULE_LICENSE("GPL"); 

