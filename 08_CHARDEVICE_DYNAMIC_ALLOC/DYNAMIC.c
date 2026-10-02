#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
dev_t device = 0 ;

static int __init ModuleStart(void){
    if(alloc_chrdev_region(device,0,1,"DynamicDeviceAlloc") < 0){
        pr_info("The Allocation Failed.....\n");
        return -1;
    } 
    pr_info("Major :- %d , Minor :- %d \n" , MAJOR(device), MINOR(device));
    pr_info("Kernal is loadded....\n");
    return 0;
}

static void __exit ModuleEnd(void){
    unregister_chrdev_region(device,1);
    pr_info("Kernal unloaded....\n");
}
MODULE_LICENSE("GPL");
module_init(ModuleStart);
module_exit(ModuleEnd);