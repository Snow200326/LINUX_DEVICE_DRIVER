#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/kobject.h>
#include <linux/sys.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/jiffies.h>



#define TIMEOUT 5000
#define Region_name "kERNELTIMERREGION"
#define ClassName "KTCLASS"
#define DeviceName "KTTIMER"


static struct timer_list Timer;
static unsigned int count = 0;

dev_t dev = 0;
static struct class *KTCLASS;
static struct cdev KTDEVICE;

static int __init Module_start(void);
static void __exit Module_End(void);
static int File_open(struct inode *, struct file *);
static int File_close(struct inode *, struct file *);
static ssize_t File_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t File_write(struct file *, const char __user *, size_t, loff_t *);
void timer_callback(struct timer_list * data);


static struct file_operations fos = {
    .owner = THIS_MODULE,
    .open = File_open,
    .read = File_read,
    .write = File_write,
    .release = File_close,
};

//timer call back function...

void timer_callback (struct timer_list * data){
    pr_info("Timer callback fucntion callled , time expired count :- [%d]\n",count ++);

    mod_timer(&Timer, jiffies + msecs_to_jiffies(TIMEOUT));
}

static int File_open(struct inode *node, struct file *file)
{
    pr_info("File Opened....\n");
    return 0;
}

static int File_close(struct inode *node, struct file *file)
{
    pr_info("File Opened....\n");
    return 0;
}

static ssize_t File_read(struct file *file, char __user *rbuff, size_t len, loff_t *offset)
{
    pr_info("File read....\n");
    return 0;
}

static ssize_t File_write(struct file *file, const char __user *rbuff, size_t len, loff_t *offset)
{
    pr_info("File Write....\n");
    return 0;
}

static int __init Module_start(void)
{

    int res;
    res = alloc_chrdev_region(&dev, 0, 1, Region_name); // / proc/device
    if (res < 0)
    {
        pr_err("Cannot allocate the region....");
        return res;
    }

    pr_info("Major :- %d , Minor :- %d \n", MAJOR(dev), MINOR(dev));

    cdev_init(&KTDEVICE, &fos);

    if (cdev_add(&KTDEVICE, dev, 1) < 0)
    { 
        pr_err("Cannot Create the add the device ....\n");
        goto UNREGISTER_REGION;
    }

    KTCLASS = class_create(ClassName);
    if (IS_ERR(KTCLASS))
    {
        pr_err("Cannot crate Class....\n");
        goto CDEV_DEL;
    }

    if (IS_ERR(device_create(KTCLASS, NULL, dev, NULL, DeviceName)))
    {
        pr_err("Cannot Create Device \n");
        goto DESTROY_CLASS;
    }

    timer_setup(&Timer,timer_callback,0);

    if (timer_pending(&Timer))
        pr_info("Timer is pending\n");
    else
        pr_info("Timer is NOT pending\n");

    mod_timer(&Timer, jiffies + msecs_to_jiffies(TIMEOUT));


    if (timer_pending(&Timer))
        pr_info("Timer is pending\n");
    else
        pr_info("Timer is NOT pending\n");



    pr_info("Device Driver Created....!\n");

    return 0;

DESTROY_CLASS:
    class_destroy(KTCLASS);

CDEV_DEL:
    cdev_del(&KTDEVICE);

UNREGISTER_REGION:
    unregister_chrdev_region(dev, 1);
    return 0;
}

static void __exit Module_End(void)
{

    timer_delete(&Timer);
    device_destroy(KTCLASS, dev);
    class_destroy(KTCLASS);
    cdev_del(&KTDEVICE);
    unregister_chrdev_region(dev, 1);
    pr_info("Device Driver removed.....\n");
}

module_init(Module_start);
module_exit(Module_End);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DNYANESH");
MODULE_DESCRIPTION("KERNEL TIMER");
MODULE_VERSION("1.25");