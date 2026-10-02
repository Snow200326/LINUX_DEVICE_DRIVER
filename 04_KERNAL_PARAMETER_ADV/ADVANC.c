
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

static int number = 10;

static int my_set( const char *val , const struct kernel_param *kp){
    int res;
    int newValue ;
    res = param_set_int(val,kp);
    pr_info("%d,res");
    if(res)
    {

        return res;
    }

    pr_info("number updated :- %d",number);
    return 0;
}

static int my_get(char *buffer, const struct kernel_param *kp)
{
    int res;
    res = param_get_int(buffer,kp);
    if(res>=0)
    {
         pr_info("number was read\n");
    }
    return res;
}
static const struct kernel_param_ops my_ops = {
    .set = my_set,
    .get = my_get,
};


static int __init hello_init(void)
{
	pr_info("Module loaded... \n");
    pr_info("number is %d",number);
	return 0;
}
static void __exit hello_exit(void)
{
	pr_info("MODULE UNLOADED..... \n");
}

module_param_cb(number,&my_ops,&number,0644);
// MODULE_PARAM_DESC(number,"An integer that logs every update")
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

