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

#define IRQ 2

static struct work_struct my_work;

static void work_function(struct work_struct *work)
{
    pr_info("Executed work function.....\n");
}

#define Region_name "WorkRegion"
#define ClassName "WorkClass"
#define DeviceName "WorkDevice"

volatile int extval = 0;

dev_t dev = 0;
static struct class *WorkClass;
static struct cdev WorkDevice;
struct kobject *kojref;

static int __init Module_start(void);
static void __exit Module_End(void);
static int File_open(struct inode *, struct file *);
static int File_close(struct inode *, struct file *);
static ssize_t File_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t File_write(struct file *, const char __user *, size_t, loff_t *);
static ssize_t work_show(struct kobject *, struct kobj_attribute *, char *);
static ssize_t work_store(struct kobject *, struct kobj_attribute *, const char *, size_t);

// interrupt

static irqreturn_t irq_handler(int irq, void *dev_id);

// interrupt function

static irqreturn_t irq_handler(int irq, void *dev_id)
{
    pr_info("hared IRQ: Interrupt Occurred");
    return IRQF_SHARED;
}

static struct file_operations fos = {
    .owner = THIS_MODULE,
    .open = File_open,
    .read = File_read,
    .write = File_write,
    .release = File_close,

};

static struct kobj_attribute WorkObjAttr = __ATTR(extval, 0660, work_show, work_store);

static ssize_t work_show(struct kobject *kobject, struct kobj_attribute *attr, char *rbuff)
{
    pr_info("System File read....\n");
    asm("int $0x32");
    return sprintf(rbuff, "value :- %d ", extval); /// return the no of char stored in rbuff...
}

static ssize_t work_store(struct kobject *kobject, struct kobj_attribute *attr, const char *wbuff, size_t count)
{
    pr_info("System File write....\n");
    sscanf(wbuff, "%d", &extval);
    return count;
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
    schedule_work(&my_work);
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

    cdev_init(&WorkDevice, &fos);

    if (cdev_add(&WorkDevice, dev, 1) < 0)
    { // 1 == count of minor no u want
        pr_err("Cannot Create the add the device ....\n");
        goto UNREGISTER_REGION;
    }

    WorkClass = class_create(ClassName); // /sys/class
    if (IS_ERR(WorkClass))
    {
        pr_err("Cannot crate Class....\n");
        goto CDEV_DEL;
    }

    if (IS_ERR(device_create(WorkClass, NULL, dev, NULL, DeviceName)))
    {
        pr_err("Cannot Create Device \n");
        goto DESTROY_CLASS;
    }
    kojref = kobject_create_and_add("WorkDevice", kernel_kobj);
    if (sysfs_create_file(kojref, &WorkObjAttr.attr))
    {
        pr_err("Cannot create sysfs file......\n");
        goto r_sysfs;
    }

    if (request_irq(IRQ, irq_handler, IRQF_SHARED, "etx_device", (void *)(irq_handler)))
    {
        pr_info("my_device: cannot register IRQ ");
        goto irq_free;
    }

    INIT_WORK(&my_work, work_function);

    pr_info("Device Driver Created....!\n");

    return 0;

irq_free:
    free_irq(IRQ, (void *)(irq_handler));
r_sysfs:
    kobject_put(kojref);
    sysfs_remove_file(kojref, &WorkObjAttr.attr);

DESTROY_CLASS:
    class_destroy(WorkClass);

CDEV_DEL:
    cdev_del(&WorkDevice);

UNREGISTER_REGION:
    unregister_chrdev_region(dev, 1);
    return 0;
}

static void __exit Module_End(void)
{
    cancel_work_sync(&my_work);
    kobject_put(kojref);
    sysfs_remove_file(kojref, &WorkObjAttr.attr);
    device_destroy(WorkClass, dev);
    class_destroy(WorkClass);
    cdev_del(&WorkDevice);
    unregister_chrdev_region(dev, 1);
    pr_info("Device Driver removed.....\n");
}

module_init(Module_start);
module_exit(Module_End);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DNYANESH");
MODULE_DESCRIPTION("WORKQUEUE ( STATIC METHOD )");
MODULE_VERSION("1.16");