#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/sys.h>
#include <linux/kobject.h>
#include <linux/irq_vectors>


#define Region_name "SysRegion"
#define ClassName "SysClass"
#define DeviceName "SysDevice"

volatile int value = 0;

dev_t dev = 0;
static struct class *Myclass;
static struct cdev CharDevice;
struct kobject *kobj_ref;

static int __init Module_start(void);
static void __exit Module_end(void);
static int File_open(struct inode *, struct file *);
static int File_close(struct inode *, struct file *);
static ssize_t File_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t File_write(struct file *, const char __user *, size_t, loff_t *);

static ssize_t sys_show(struct kobject *kobj, struct kobj_attribute *attr,
                        char *rbuf);
static ssize_t sys_store(struct kobject *kobj, struct kobj_attribute *attr,
                         const char *buff, size_t count);

static struct kobj_attribute SysObjAttr = __ATTR(value, 0660, sys_show, sys_store);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = File_open,
    .release = File_close,
    .read = File_read,
    .write = File_write,
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
    return 0;
}

static ssize_t File_write(struct file *file, const char __user *rbuff, size_t len, loff_t *offset)
{
    pr_info("Written someting.....\n");
    return 0;
}

static ssize_t sys_show(struct kobject *kobj, struct kobj_attribute *attr, char *rbuf)
{
    pr_info("Sys read....\n");
    return sprintf(rbuf, "version :- %d\n", value);
}

static ssize_t sys_store(struct kobject *kobj, struct kobj_attribute *attr , const char *buff, size_t count)
{
    pr_info("sysFile Written....\n");
     sscanf(buff, "%d", &value);
     return count;
}

static int __init Module_start(void)
{

    int res;
    res = alloc_chrdev_region(dev, 0, 1, Region_name);
    if (res < 0)
    {
        pr_info("Region cannot allocate .....\n");
        return res;
    }
    pr_info("Major :- %d , Minor :- %d ", MAJOR(dev), MINOR(dev));

    cdev_init(&CharDevice, &fops);
    if (cdev_add(&CharDevice, dev, 1) < 0)
    {
        pr_info("Cannot creat the cdevice...\n");
        goto unregister_chrdev;
    }

    Myclass = class_create(ClassName);
    if (IS_ERR(Myclass))
    {
        pr_info("Class Cannot be Created....\n");
        goto cdev_del;
    }

    if (IS_ERR(device_create(Myclass, NULL, dev, NULL, DeviceName)))
    {
        pr_info("Cannot Create Device....\n");
        goto destroy_class;
    }

    kobj_ref = kobject_create_and_add("etx_sysfs", kernel_kobj);

    /*Creating sysfs file for etx_value*/
    if (sysfs_create_file(kobj_ref, &SysObjAttr.attr))
    {
        pr_err("Cannot create sysfs file......\n");
        goto r_sysfs;
    }

    pr_info("Device Drive Inserted......Done!!!!\n");
    return 0;

r_sysfs:
    kobject_put(kobj_ref);
    sysfs_remove_file(kernel_kobj, &SysObjAttr.attr);

destroy_class:
    class_destroy(Myclass);

cdev_del:
    cdev_del(&CharDevice);
unregister_chrdev:
    unregister_chrdev_region(dev, 1);

    return res;
}

static void __exit Module_end(void)
{
         kobject_put(kobj_ref); 
        sysfs_remove_file(kernel_kobj,&SysObjAttr.attr);
        device_destroy(Myclass,dev);
        class_destroy(Myclass);
        cdev_del(&CharDevice);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!!\n");
}

module_init(Module_start);
module_exit(Module_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DNYANESHs");
MODULE_DESCRIPTION("SYSSTEM FILE..");
MODULE_VERSION("1.14");