#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/proc_fs.h>

#define region_name "My_region"
#define Class_name "My_class"
#define Device_name "Demo"
#define Max_size_buff 1024
#define proc_name "Myproc"

dev_t dev = 0;
static struct class *Class;
static struct cdev device;
static struct proc_dir_entry *proc_entry;
static struct proc_dir_entry *proc_File;

// for procfs

int32_t value = 0;
char ext_dev[20];
static int len = sizeof(ext_dev);
char buff_write[Max_size_buff];
size_t buff_len = 0;

// function defination
static int __init Module_startt(void);
static void __exit Moudle_end(void);
static int File_open(struct inode *, struct file *);
static int File_close(struct inode *, struct file *);
static ssize_t File_read(struct file *, char __user *, size_t len, loff_t *);
static ssize_t File_write(struct file *, const char __user *, size_t len, loff_t *);

// for procs l...

static int proc_FileOpen(struct inode *, struct file *);
static int proc_Fileclose(struct inode *, struct file *);
static ssize_t proc_FileRead(struct file *, char __user *, size_t len, loff_t *);
static ssize_t proc_FileWrite(struct file *, const char __user *, size_t len, loff_t *);

static struct file_operations FileOps = {
    .owner = THIS_MODULE,
    .read = File_read,
    .open = File_open,
    .write = File_write,
    .release = File_close,
};

// File Operation for procfs...

static struct proc_ops proc_file_ops = {
    .proc_open = proc_FileOpen,
    .proc_release = proc_Fileclose,
    .proc_read = proc_FileRead,
    .proc_write = proc_FileWrite,
};

// FILE OPERATION FOR HE PROCSSS...
static int proc_FileOpen(struct inode *node, struct file *file)
{
    pr_info("Procss open .....\n");
    return 0;
}
static int proc_Fileclose(struct inode *node, struct file *file)
{
    pr_info("procss Close...\n");
    return 0;
}
static ssize_t proc_FileRead(struct file *file,
                             char __user *rbuff,
                             size_t len,
                             loff_t *offset)
{
    size_t copy_len;

    if (*offset >= buff_len)
    {
        return 0;
    }

    copy_len = min(len, buff_len - *offset);

    if (copy_to_user(rbuff,
                     buff_write + *offset,
                     copy_len))
    {
        pr_info("Cannot read device....\n");
        return -EFAULT;
    }

    *offset += copy_len;

    pr_info("Data read ...... %s\n",
            file->f_path.dentry->d_name.name);

    return copy_len;
}
static ssize_t proc_FileWrite(struct file *file, const char __user *wbuff, size_t len, loff_t *offset)
{
    buff_len = len;
    if (buff_len >= Max_size_buff)
    {
        buff_len = Max_size_buff - 1;
    }

    if (copy_from_user(buff_write, wbuff, buff_len))
    {
        return -EFAULT;
    }
     buff_write[buff_len] = '\0';
    pr_info("Written something.. %s", buff_write);
    return buff_len;
}

// filse Operations....
static int File_open(struct inode *inode, struct file *file)
{
    pr_info("Driver open....\n");
    return 0;
}

static int File_close(struct inode *inode, struct file *file)
{
    pr_info("Driver Close...\n");
    return 0;
}

static ssize_t File_read(struct file *file, char __user *Rbuff, size_t len, loff_t *offs)
{
    pr_info("Read something ...\n");
    return len;
}
static ssize_t File_write(struct file *file, const char __user *Wbuff, size_t len, loff_t *offs)
{
    pr_info("Written ......\n");
    return len;
}

static int __init Module_startt(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev, 0, 1, region_name);
    if (ret < 0)
    {
        pr_info("Cannot Allocate the region....\n");
        return ret;
    }

    pr_info("Major :- %d, Minor :- %d\n", MAJOR(dev), MINOR(dev));

    cdev_init(&device, &FileOps);

    ret = cdev_add(&device, dev, 1);
    if (ret < 0)
    {
        pr_info("Cannot add cdev...\n");
        goto unregister_region;
    }

    Class = class_create(Class_name);

    if (IS_ERR(Class))
    {
        ret = PTR_ERR(Class);
        pr_info("Class Cannot be Created...\n");
        goto delete_cdev;
    }

    if (IS_ERR(device_create(Class, NULL, dev, NULL, Device_name)))
    {
        ret = -ENOMEM;
        pr_info("Device cannot be Created....\n");
        goto destroy_class;
    }

    proc_entry = proc_mkdir("My_porc", NULL);

    if (proc_entry == NULL)
    {
        ret = -ENOMEM;
        pr_info("Cannot create proc directory\n");
        goto destroy_device;
    }

    proc_File = proc_create(proc_name, 0666, proc_entry,
                            &proc_file_ops);

    if (proc_File == NULL)
    {
        ret = -ENOMEM;
        pr_info("Cannot create proc file\n");
        goto remove_proc_dir;
    }

    pr_info("Device Driver Created....\n");

    return 0;


remove_proc_dir:
    remove_proc_entry("My_porc", NULL);

destroy_device:
    device_destroy(Class, dev);

destroy_class:
    class_destroy(Class);

delete_cdev:
    cdev_del(&device);

unregister_region:
    unregister_chrdev_region(dev, 1);

    return ret;
}
static void __exit Moudle_end(void)
{
    remove_proc_entry(proc_name, proc_entry);
    remove_proc_entry("My_porc", NULL);

    device_destroy(Class, dev);
    class_destroy(Class);
    cdev_del(&device);
    unregister_chrdev_region(dev, 1);

    pr_info("Device Driver Removed ....\n");
}

module_init(Module_startt);
module_exit(Moudle_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DNYANESHs");
MODULE_DESCRIPTION("PROCFS FILE EXPLAIN");
MODULE_VERSION("1.12");