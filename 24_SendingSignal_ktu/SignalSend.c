#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/ioctl.h>
#define SIGEXT 44

#define IR_NO 2
#define arg_val _IOWR('a', 'a', int32_t *)
#define Region "SignalRegion"
#define deviceName "SignalName"
#define classname "SignalClass"

static struct task_struct *task;
int signum = 0;
int value = 0;
dev_t dev;
static struct cdev device;
static struct class *myclass;
static int __init Module_start(void);
static void __exit Module_end(void);
static int File_open(struct inode *node, struct file *file);
static int File_close(struct inode *node, struct file *file);
static ssize_t File_read(struct file *file, char __user *rbuff, size_t len, loff_t *offset);
static ssize_t File_write(struct file *file, const char __user *wbuff, size_t len, loff_t *offset);
static long ext_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static irqreturn_t irq_handler(int req, void *dev_id);
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = File_open,
    .read = File_read,
    .write = File_write,
    .release = File_close,
    .unlocked_ioctl = ext_ioctl,
};
static long ext_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int32_t value;
    if (cmd == arg_val )
    {
        pr_info("Arg_value for signal..... \n");
        task = get_current();
        signum = SIGEXT;
    }

    return 0;
}

static irqreturn_t irq_handler(int req, void *dev_id)
{
    struct kernel_siginfo info;
    pr_info("Interrpted successfully...");
    //SENDING SIGNAL TO APP
    memset(&info,0,sizeof(struct siginfo));
    info.si_signo = SIGEXT;
    info.si_code = SI_QUEUE;
    info.si_int = 1;

    if(task != NULL){
        pr_info("SENDING SIGNALT TO APP \n");
        if(send_sig_info(SIGEXT, &info, task)<0){
            pr_info("Cannot send message....\n");
        }
    }
    return IRQ_HANDLED;
}

static int File_open(struct inode *node, struct file *file)
{
    pr_info("File Opened....\n");
    return 0;
}
static int File_close(struct inode *node, struct file *file)
{
    struct task_struct *refTask = get_current();

    if(refTask == task){
        task = NULL;
    }
    pr_info("File Opened....\n");
    return 0;
}
static ssize_t File_read(struct file *file, char __user *rbuff, size_t len, loff_t *offset)
{
    pr_info("File read....\n");
    asm("int $0x32");
    return 0;
}

static ssize_t File_write(struct file *file, const char __user *wbuff, size_t len, loff_t *offset)
{
    pr_info("Written someting.....\n");
    return 0;
}
static int __init Module_start(void)
{
    int res;

    res = alloc_chrdev_region(&dev, 0, 1, Region);

    if (res < 0)
    {
        pr_info("Cannot alllocated the region...\n");
        return -1;
    }
    pr_info("MAJOR :- %d MINOR :- %d \n", MAJOR(dev), MINOR(dev));
    cdev_init(&device, &fops);
    if (cdev_add(&device, dev, 1))
    {
        pr_info("cannot create chr_device.....\n");
        goto unregister_region;
    }

    myclass = class_create(classname);

    if (IS_ERR(myclass))
    {
        pr_err("Cannot create the class...\n");
        goto delet_chrdev;
    }

    if (IS_ERR(device_create(myclass, NULL, dev, NULL, deviceName)))
    {
        pr_err("Cannot create devie .....\n");
        goto delet_class;
    }

    if (request_irq(IR_NO, irq_handler, IRQF_SHARED, "INTERRUPT_DEVICE", (void *)(irq_handler)))
    {
        goto free_irq;
    }

    pr_info("Device Drive Created......");
    return 0;
free_irq:
    free_irq(IR_NO, (void *)(irq_handler));

delet_class:
    class_destroy(myclass);

delet_chrdev:
    cdev_del(&device);

unregister_region:
    unregister_chrdev_region(dev, 1);

    return 0;
}

static void __exit Module_end(void)
{
    free_irq(IR_NO, (void *)(irq_handler));
    device_destroy(myclass, dev);
    class_destroy(myclass);
    cdev_del(&device);
    unregister_chrdev_region(dev, 1);
    pr_info("Device Driver Removed....!");
}

module_init(Module_start);
module_exit(Module_end);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SIGNAL SENDING TO KERNEL");
MODULE_AUTHOR("DNYANESH");
MODULE_VERSION("1.24");
