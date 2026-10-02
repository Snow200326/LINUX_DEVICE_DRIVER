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
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/interrupt.h>

#define Region_name "ThreadRegion"
#define ClassName "ThreadClass"
#define DeviceName "ThreadDevice"

dev_t dev = 0;
static struct class *kERNELc_CLASS;
static struct cdev kERNEL_DEVICE;

// Kernel Thread
DECLARE_TASKLET()

static struct task_struct *kthread;

int kthreadFunction(void *vp);

static int __init Module_start(void);
static void __exit Module_End(void);
static int File_open(struct inode *, struct file *);
static int File_close(struct inode *, struct file *);
static ssize_t File_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t File_write(struct file *, const char __user *, size_t, loff_t *);

static struct file_operations fos = {
    .owner = THIS_MODULE,
    .open = File_open,
    .read = File_read,
    .write = File_write,
    .release = File_close,

};

int kthreadFunction(void *vp)
{
    int i = 0;
    while (!kthread_should_stop())
    {
        pr_info("Thread Function %d \n", i++);
        msleep(1000);
    }
    return 0;
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
    // asm("int $0x32");
    return 0;
}

static ssize_t File_write(struct file *file, const char __user *rbuff, size_t len, loff_t *offset)
{
    pr_info("File Write....\n");
    // asm("int $0x32");
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

    cdev_init(&kERNEL_DEVICE, &fos);

    if (cdev_add(&kERNEL_DEVICE, dev, 1) < 0)
    { // 1 == count of minor no u want
        pr_err("Cannot Create the add the device ....\n");
        goto UNREGISTER_REGION;
    }

    kERNELc_CLASS = class_create(ClassName); // /sys/class
    if (IS_ERR(kERNELc_CLASS))
    {
        pr_err("Cannot crate Class....\n");
        goto CDEV_DEL;
    }

    if (IS_ERR(device_create(kERNELc_CLASS, NULL, dev, NULL, DeviceName)))
    {
        pr_err("Cannot Create Device \n");
        goto DESTROY_CLASS;
    }

    kthread = kthread_create(kthreadFunction, NULL, "EXT_THREAD");
    if (kthread)
    {
        pr_info("Thread Created.....\n");
        wake_up_process(kthread);
    }
    else
    {
        pr_err("Cannot Create Tread...\n");
        goto DESTROY_CLASS;
    }
    pr_info("PID=%d CPU=%d\n", current->pid, smp_processor_id());

    // kernel thread method 2 -------------------using run ----------------------------------------

    // kthread = kthread_run(kthreadFunction, NULL, "EXT_THREAD");

    // if (kthread)
    // {
    //     pr_info("Thread RUNNIGN.....\n");
    // }
    // else
    // {
    //     pr_err("Cannot Create Tread...\n");
    //     goto DESTROY_CLASS;
    // }
    pr_info("Device Driver Created....!\n");

    return 0;

DESTROY_CLASS:
    class_destroy(kERNELc_CLASS);

CDEV_DEL:
    cdev_del(&kERNEL_DEVICE);

UNREGISTER_REGION:
    unregister_chrdev_region(dev, 1);
    return 0;
}

static void __exit Module_End(void)
{
     kthread_stop(kthread);
    device_destroy(kERNELc_CLASS, dev);
    class_destroy(kERNELc_CLASS);
    cdev_del(&kERNEL_DEVICE);
    unregister_chrdev_region(dev, 1);
    pr_info("Device Driver removed.....\n");
}

module_init(Module_start);
module_exit(Module_End);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DNYANESH");
MODULE_DESCRIPTION("KERNEL Thread");
MODULE_VERSION("1.19");