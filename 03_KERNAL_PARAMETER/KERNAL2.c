
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

static int number[6] = {1,2,3,4,5,6};
static int count;
 // module_param(number, int, 0644) ;  -------> for storing the  single value
 module_param_array(number,int, &count , 0644);
static int __init hello_init(void)
{
	//pr_info("hello world \n");
	//pr_info("Number = %d\n",number);
	int i;
         pr_info("Modlue loaded\n");
	for(i=0;i<count ;i++)
	{
		pr_info("Numbers[%d] = %d\n", i, number[i]);
	}
	return 0;
}
static void __exit hello_exit(void)
{
	pr_info("MODULE UNLOADED..... \n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

