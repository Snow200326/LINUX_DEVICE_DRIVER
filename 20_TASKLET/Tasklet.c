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
#define IRQ 2
#define Region_name "TasklietRegion"
#define ClassName "TasklisClass"
#define DeviceName "TaskLisDevice"

void TaskLisFunction(unsigned long );
// void TaskLisFunction2(struct tasklet_struct *) ;


// STATIC METHOD FOR TASKLET
// DECLARE_TASKLET(Tasklisname,TaskLisFunction);
// DECLARE_TASKLET(Tasklisname2,TaskLisFunction2);


//DYNAMIC METHOD FOR TASKLET 

struct tasklet_struct *Tasklisname =  NULL;

dev_t dev = 0;
static struct class *TaskClass;
static struct cdev TaskDevice;

static int __init Module_start(void);
static void __exit Module_End(void);
static int File_open(struct inode *, struct file *);
static int File_close(struct inode *, struct file *);
static ssize_t File_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t File_write(struct file *, const char __user *, size_t, loff_t *);
// interrupt

static irqreturn_t irq_handler(int irq, void *dev_id);

// interrupt function

static irqreturn_t irq_handler(int irq, void *dev_id)
{
    pr_info("hared IRQ: Interrupt Occurred");
    // tasklet_schedule(&Tasklisname); //schedule tasklet....
    return IRQF_SHARED;
}
// TAKSLET

// TASKLET FUNCTION
void TaskLisFunction(unsigned long args)
{
    pr_info("TASKLET 01 :- %ld \n",args);
}

// void TaskLisFunction2(struct tasklet_struct *Tasklisname2)
// {
//     pr_info("TASKLET 02....\n");
// }

static struct file_operations fos = {
    .owner = THIS_MODULE,
    .open = File_open,
    .read = File_read,
    .write = File_write,
    .release = File_close,
};

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
    tasklet_schedule(Tasklisname); //schedule tasklet....
    // tasklet_schedule(&Tasklisname2);
    // asm("int $0x32");
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

    cdev_init(&TaskDevice, &fos);

    if (cdev_add(&TaskDevice, dev, 1) < 0)
    { // 1 == count of minor no u want
        pr_err("Cannot Create the add the device ....\n");
        goto UNREGISTER_REGION;
    }

    TaskClass = class_create(ClassName); // /sys/class
    if (IS_ERR(TaskClass))
    {
        pr_err("Cannot crate Class....\n");
        goto CDEV_DEL;
    }

    if (IS_ERR(device_create(TaskClass, NULL, dev, NULL, DeviceName)))
    {
        pr_err("Cannot Create Device \n");
        goto DESTROY_CLASS;
    }

    if (request_irq(IRQ, irq_handler, IRQF_SHARED, "etx_device", (void *)(irq_handler)))
    {
        pr_info("my_device: cannot register IRQ ");
        goto irq_free;
    }

    Tasklisname = kmalloc(sizeof(struct tasklet_struct ),GFP_KERNEL);
    if(Tasklisname == NULL){
        pr_info("Cannot Allocate the Memroy..\n");
        goto irq_free;
    }
    tasklet_init(Tasklisname,TaskLisFunction,1);


    pr_info("Device Driver Created....!\n");

    return 0;

irq_free:
    free_irq(IRQ, (void *)(irq_handler));

DESTROY_CLASS:
    class_destroy(TaskClass);

CDEV_DEL:
    cdev_del(&TaskDevice);

UNREGISTER_REGION:
    unregister_chrdev_region(dev, 1);
    return 0;
}

static void __exit Module_End(void)
{

    tasklet_kill(Tasklisname); // kill tasklet.....
    device_destroy(TaskClass, dev);
    class_destroy(TaskClass);
    cdev_del(&TaskDevice);
    unregister_chrdev_region(dev, 1);
    pr_info("Device Driver removed.....\n");
}

module_init(Module_start);
module_exit(Module_End);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DNYANESH");
MODULE_DESCRIPTION("WORKQUEUE ( STATIC METHOD )");
MODULE_VERSION("1.16");