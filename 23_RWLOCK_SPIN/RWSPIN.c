#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/sched.h>
#include <linux/rwlock.h>
#include <linux/printk.h>


#define Region_name "RWSPINLOCKREGION"
#define ClassName "RWSPINCLASS"
#define DeviceName "RWSPINDEVICE"

// rwlock

 rwlock_t rwlock;

dev_t dev = 0;
static struct class *Myclass;
static struct cdev Mydevice;
static char msg[100];

static int __init Module_start(void);
static void __exit Module_end(void);
static int file_open(struct inode *node, struct file *file);
static int file_close(struct inode *node, struct file *file);
static ssize_t file_read(struct file *file, char __user *rbuff, size_t len, loff_t *offset);
static ssize_t file_write(struct file *file, const char __user *wbuff, size_t len, loff_t *offset);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = file_open,
    .read = file_read,
    .write = file_write,
    .release = file_close,
};

static int file_open(struct inode *node, struct file *file)
{
    pr_info("File open...\n");
    return 0;
}
static int file_close(struct inode *node, struct file *file)
{
    pr_info("File close ...\n");

    return 0;
}
static ssize_t file_read(struct file *file, char __user *rbuff, size_t len, loff_t *offset)
{
    size_t msg_len;
    pr_info("READ: called\n");
        pr_info("READ: locked..\n");

    read_lock(&rwlock);
    msg_len = sizeof(msg);
    len = sizeof(msg) - 1;

    if (*offset > len)
    {
        read_unlock(&rwlock);
        return 0;
    }
    if (len > msg_len - *offset)
        len = msg_len - *offset;

    if (copy_to_user(rbuff, msg + *offset, len))
    {
        read_unlock(&rwlock);
        return -EFAULT;
    }

    *offset += len;
    read_unlock(&rwlock);

    pr_info("READ: lock released\n");

    return len;
}
static ssize_t file_write(struct file *file, const char __user *wbuff, size_t len, loff_t *offset)
{

    size_t count;
    pr_info("WRITE: called\n");
    pr_info("WRITE: locked..\n");
    write_lock(&rwlock);
    count = len;

    if (count > sizeof(msg) - 1)
    {
        count = sizeof(msg) - 1;
    }

    if (copy_from_user(msg, wbuff, count))
    {
        write_lock(&rwlock);
        return -EFAULT;
    }

    msg[count] = '\0';

    pr_info("WRITE: Process = %s, PID = %d\n", current->comm, current->pid);

    pr_info("File write...\n");
    write_lock(&rwlock);
    pr_info("write: lock released\n");
    return count;
}

static int __init Module_start(void)
{

    int res;
    res = alloc_chrdev_region(&dev, 0, 1, Region_name);

    if (res < 0)
    {
        pr_info("Cannot allocate region...\n");
        return res;
    }

    pr_info("MAJOR :- %d MINOR :- %d \n", MAJOR(dev), MINOR(dev));

    cdev_init(&Mydevice, &fops);
    if (cdev_add(&Mydevice, dev, 1) < 0)
    {
        pr_info("Cannot create the cdev...");
        goto Unregister_region;
    }

    Myclass = class_create(ClassName);

    if (IS_ERR(Myclass))
    {
        pr_info("cannot create class...\n");
        goto DeleChrdev;
    }
    rwlock_init(&rwlock);

    if (IS_ERR(device_create(Myclass, NULL, dev, NULL, DeviceName)))
    {
        pr_info("CANNOT CREATE DEVICE .....\n");
        goto ClassDevice;
    }

    pr_info("Driver Inserted...\n");
    return 0;

ClassDevice:
    class_destroy(Myclass);

DeleChrdev:
    cdev_del(&Mydevice);

Unregister_region:
    unregister_chrdev_region(dev, 1);
    return res;
}

static void __exit Module_end(void)
{
    device_destroy(Myclass, dev);
    class_destroy(Myclass);
    cdev_del(&Mydevice);
    unregister_chrdev_region(dev, 1);
    pr_info("Drive Removed....\n");
}

module_init(Module_start);
module_exit(Module_end);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RWSPIN_LOCK");
MODULE_AUTHOR("DNYANEHS");
MODULE_VERSION("1.23");