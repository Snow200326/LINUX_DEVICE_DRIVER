#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dnyanesh");
MODULE_DESCRIPTION("Simple Character Device Driver");

/* Device number */
static dev_t devt_num;

/* Character device structure */
static struct cdev my_cdev;

/* Device class */
static struct class *my_class;

/* Device */
static struct device *my_device;
copy_to_user(buffer, s, len))

/* Function declarations */

static int my_open(struct inode *inode, struct file *file);

static ssize_t my_read(struct file *file,
                       char __user *buffer,
                       size_t count,
                       loff_t *offset);

static ssize_t my_write(struct file *file,
                        const char __user *buffer,
                        size_t count,
                        loff_t *offset);

static int my_release(struct inode *inode,
                      struct file *file);


/* File operations */

static const struct file_operations my_fops = {
    .owner   = THIS_MODULE,
    .open    = my_open,
    .read    = my_read,
    .write   = my_write,
    .release = my_release,
};


/* Open */

static int my_open(struct inode *inode, struct file *file)
{
    pr_info("mychardev: Device opened\n");

    return 0;
}


/* Read */

static ssize_t my_read(struct file *file,
                       char __user *buffer,
                       size_t count,
                       loff_t *offset)
{
    pr_info("mychardev: Device read\n");

    return 0;
}


/* Write */

static ssize_t my_write(struct file *file,
                        const char __user *buffer,
                        size_t count,
                        loff_t *offset)
{
    pr_info("mychardev: Device write\n");

    return count;
}


/* Release */

static int my_release(struct inode *inode,
                      struct file *file)
{
    pr_info("mychardev: Device closed\n");

    return 0;
}


/* Module initialization */

static int __init myChardevInit(void)
{
    int ret;

    pr_info("mychardev: Module loading\n");


    /*
     * 1. Allocate major and minor numbers
     *
     * &devt_num -> stores allocated device number
     * 0         -> starting minor number
     * 1         -> number of device numbers required
     * "my_device" -> name of registration
     */

    ret = alloc_chrdev_region(&devt_num,
                              0,
                              1,
                              "my_device");

    if (ret < 0)
    {
        pr_err("mychardev: Device allocation failed\n");

        return ret;
    }


    pr_info("mychardev: Major = %d\n", MAJOR(devt_num));
    pr_info("mychardev: Minor = %d\n", MINOR(devt_num));


    /*
     * 2. Initialize character device
     *
     * Connect my_cdev with my_fops
     */

    cdev_init(&my_cdev, &my_fops);

    my_cdev.owner = THIS_MODULE;


    /*
     * 3. Add character device to kernel
     */

    ret = cdev_add(&my_cdev,
                   devt_num,
                   1);

    if (ret < 0)
    {
        pr_err("mychardev: cdev_add failed\n");

        unregister_chrdev_region(devt_num, 1);

        return ret;
    }


    /*
     * 4. Create device class
     */

    my_class = class_create("mychardev_class");

    if (IS_ERR(my_class))
    {
        pr_err("mychardev: Class creation failed\n");

        cdev_del(&my_cdev);

        unregister_chrdev_region(devt_num, 1);

        return PTR_ERR(my_class);
    }


    /*
     * 5. Create device
     *
     * This creates:
     *
     * /dev/mychardev
     */

    my_device = device_create(my_class,
                              NULL,
                              devt_num,
                              NULL,
                              "mychardev");

    if (IS_ERR(my_device))
    {
        pr_err("mychardev: Device creation failed\n");

        class_destroy(my_class);

        cdev_del(&my_cdev);

        unregister_chrdev_region(devt_num, 1);

        return PTR_ERR(my_device);
    }


    pr_info("mychardev: Character device created\n");

    pr_info("mychardev: /dev/mychardev is ready\n");


    return 0;
}


/* Module exit */

static void __exit mychardev_exit(void)
{
    /*
     * 1. Remove /dev/mychardev
     */

    device_destroy(my_class, devt_num);


    /*
     * 2. Destroy class
     */

    class_destroy(my_class);


    /*
     * 3. Remove cdev
     */

    cdev_del(&my_cdev);


    /*
     * 4. Release major/minor numbers
     */

    unregister_chrdev_region(devt_num, 1);


    pr_info("mychardev: Character device removed\n");
}


module_init(myChardevInit);
module_exit(mychardev_exit);