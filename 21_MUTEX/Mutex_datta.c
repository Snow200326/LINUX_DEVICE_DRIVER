#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mutex.h>

#define Region_name "MutexRegion"
#define ClassName "MutexClass"
#define DeviceName "MutexDevice"
#define ThreadName "MyThread"
#define ThreadName2 "MyThread2"

volatile int x = 1;

dev_t dev = 0;
static struct class *Myclass;
static struct cdev Mydevice;
static struct task_struct *thread1;
static struct task_struct *thread2;

// MUTEXT CODE

struct mutex Mymutex;

static int threadfunction(void *);
static int threadfunction2(void *);

static int __init Module_start(void);
static void __exit Module_end(void);
static int file_open(struct inode *node, struct file *file);
static int file_close(struct inode *node, struct file *file);
static ssize_t file_read(struct file *file, char __user *rbuff, size_t len, loff_t *offset);
static ssize_t file_write(struct file *file, const char __user *rbuff, size_t len, loff_t *offset);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = file_open,
    .read = file_read,
    .write = file_write,
    .release = file_close,
};

static int threadfunction(void *p)
{
    // int *data = p;


    while (!kthread_should_stop())
    {
        mutex_lock(&Mymutex);
        (x)++;
         pr_info("Thread 1 running: x value :- %d Mutext locked\n" , x);
        mutex_unlock(&Mymutex);
        msleep(1000);
    }
    pr_info("Thread Stop..\n");
    pr_info("value of gloable var :- %d \n", x);
    return 0;
}

static int threadfunction2(void *p)
{
    // int *data = p;

    while (!kthread_should_stop())
    {
        mutex_lock(&Mymutex);
        (x)++;
        pr_info("Thread 2 running: x value :- %d Mutext locked\n" , x);
        mutex_unlock(&Mymutex);
        msleep(1000);
    }
    pr_info("value of gloable var :- %d \n", x);

    pr_info("Thread Stop..\n");
    return 0;
}

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
    pr_info("File read ....\n");
    wake_up_process(thread1);
    wake_up_process(thread2);

    return 0;
}
static ssize_t file_write(struct file *file, const char __user *rbuff, size_t len, loff_t *offset)
{
    pr_info("File write...\n");
    return 0;
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

    if (IS_ERR(device_create(Myclass, NULL, dev, NULL, DeviceName)))
    {
        pr_info("CANNOT CREATE DEVICE .....\n");
        goto ClassDevice;
    }
    mutex_init(&Mymutex);

    thread1 = kthread_create(threadfunction, &x, ThreadName);
    if (IS_ERR(thread1))
    {
        pr_info("Cannot create the threas...\n");
        goto ClassDevice;
    }

    thread2 = kthread_create(threadfunction2, &x, ThreadName2);
    if (IS_ERR(thread2))
    {
        pr_info("Cannot create the threas...\n");
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
    kthread_stop(thread1);
    kthread_stop(thread2);

    device_destroy(Myclass, dev);
    class_destroy(Myclass);
    cdev_del(&Mydevice);
    unregister_chrdev_region(dev, 1);
    pr_info("Drive Removed....\n");
}

module_init(Module_start);
module_exit(Module_end);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TITLE MUTEX");
MODULE_AUTHOR("DNYANEHS");
MODULE_VERSION("1.21");