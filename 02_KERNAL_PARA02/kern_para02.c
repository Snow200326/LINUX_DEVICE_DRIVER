#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>

static int number = 20;

static int arr[5] = {11, 2, 34, 4, 75};

static int count;
static char str[9] = "Dnyanesh";

module_param(number, int, 0644);
MODULE_PARM_DESC(number, "This is the integer value");

module_param_array(arr, int, &count, 0644);
MODULE_PARM_DESC(arr, "Array of integer values");

module_param_string(str,str, sizeof(str),0644);
MODULE_LICENSE("GPL");

static int __init enter_point(void)
{
    int i;

    pr_info("HELLO ! ...\n");

    pr_info("Number = %d\n", number);

    pr_info("The length of array is = %d\n", count);

    for (i = 0; i < count; i++)
    {
        pr_info("Number at [%d] = %d\n", i, arr[i]);
    }

    pr_info("These string is %s",str);
    return 0;
}

static void __exit exit_point(void)
{
    pr_info("Good bye ! ...\n");
}

module_init(enter_point);
module_exit(exit_point);