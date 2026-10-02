#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
    pr_info("These is start");
    return 0;
}


