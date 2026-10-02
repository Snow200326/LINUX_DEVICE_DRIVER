#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/kdev_t.h>
#include <linux/sys.h>
#include <linux/kobject.h>

dev_t dev;
static struct class *my_class;
static struct cdev my_device;
static struct task_struct *wait_thread;
wait_queue_head_t wq;
show

uint32_t count = 0;
int wait_queue_flag = 0;
__ATTR()

static int __init Module_start(void);
static void __exit Module_end(void);
static ssize_t file_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t file_write(struct file *, const char __user *, size_t, loff_t *);
static int file_open(struct inode *, struct file *);
static int file_close(struct inode *, struct file *);
static int wait_function(void *unused)
{
        
        while(1) {
                pr_info("Waiting For Event...\n");
                wait_event_interruptible(wq, wait_queue_flag != 0 );
                if(wait_queue_flag == 2) {
                        pr_info("Event Came From Exit Function\n");
                        return 0;
                }
                pr_info("Event Came From Read Function - %d\n", ++count);
                wait_queue_flag = 0;
        }
        return 0;
}

static ssize_t file_read(struct file *file, char __user *rbuff, size_t len, loff_t *offset)
{
        pr_info("Read Function\n");
        wait_queue_flag = 1;
        wake_up_interruptible(&wq);
        return 0;
}
static ssize_t file_write(struct file *file, const char __user *wrbuff, size_t len, loff_t *offset)
{
    return 0;
}
static int file_open(struct inode *inode, struct file *file)
{
    return 0;
}
static int file_close(struct inode *inode, struct file *file)
{
    return 0;
}

static struct file_operations fops = {
    .open = file_open,
    .read = file_read,
    .write = file_write,
    .release = file_close,
};

static int __init Module_start(void)
{
    int res;
    res = alloc_chrdev_region(&dev, 0, 1, "My_device");
    if (res < 0)
    {
        pr_info("Cannot allocate the region\n");
        return res;
    }
    pr_info("Major :- %d, Minor :- %d\n", MAJOR(dev), MINOR(dev));


    cdev_init(&my_device, &fops);
    if (cdev_add(&my_device, dev, 1) < 0)
    {
        pr_info("Cannot creat the Cdevice");
        goto unregister_region;
    }
    
    my_class = class_create("My_class");
    if (IS_ERR(my_class))
    {
        pr_info("Cannot create the class..\n");

        goto distroy_cdev;
    }

    if (IS_ERR(device_create(my_class, NULL, dev, NULL, "DEVICE_DEMO")))
    {
        pr_info("Cannot create the device.....\n");
        goto distroy_class;
    }

            //Initialize wait queue
        init_waitqueue_head(&wq);
 
        //Create the kernel thread with name 'mythread'
        wait_thread = kthread_create(wait_function, NULL, "WaitThread");
        if (wait_thread) {
                pr_info("Thread Created successfully\n");
                wake_up_process(wait_thread);
        } else
                pr_info("Thread creation failed\n");
 
        pr_info("Device Driver Insert...Done!!!\n");
        return 0;
  

distroy_class:
    class_destroy(my_class);

distroy_cdev:
    cdev_del(&my_device);
unregister_region:
    unregister_chrdev_region(dev, 1);

    return res;
}

static void __exit Module_end(void)
{
    wait_queue_flag = 2;
    wake_up_interruptible(&wq);
    device_destroy(my_class, dev);
    class_destroy(my_class);
    cdev_del(&my_device);
    unregister_chrdev_region(dev, 1);
    pr_info("Device Driver Removed......");
}

module_init(Module_start);
module_exit(Module_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DNYANESHs");
MODULE_DESCRIPTION("WAITQUEE..");
MODULE_VERSION("1.13");