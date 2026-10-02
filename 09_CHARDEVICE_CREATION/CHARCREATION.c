#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

dev_t dev = 0;
static struct class *deviClass;

static int __init Module_Enter(void)
{
    if (alloc_chrdev_region(&dev, 0, 1, "NewChar") < 0)
    {
        pr_info("Cannot allocate Major number of device..\n");
        return -1;
    }

    pr_info("Major :- %d, Minor :- %d\n", MAJOR(dev), MINOR(dev));

    /* Create Class */
    deviClass = class_create("NewClass");

    if (IS_ERR(deviClass))
    {
        pr_info("Cannot create the Class...\n");
        goto r_class;
    }

    /* Create Device */
    if (IS_ERR(device_create(deviClass, NULL, dev, NULL, "MyDevice")))
    {
        pr_err("Cannot create the Device\n");
        goto r_device;
    }

    return 0;

r_device:
    class_destroy(deviClass);

r_class:
    unregister_chrdev_region(dev, 1);
    return -1;
}

static void __exit Module_exit(void)
{
    device_destroy(deviClass, dev);
    class_destroy(deviClass);
    unregister_chrdev_region(dev, 1);
}

module_init(Module_Enter);
module_exit(Module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbeTronicX <embetronicx@gmail.com>");
MODULE_DESCRIPTION("Simple linux driver (Automatically Creating a Device file)");
MODULE_VERSION("1.2");