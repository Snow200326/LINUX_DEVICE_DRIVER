#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>


// step 1 :- creaet the dev with custom majo and minor no
dev_t device = MKDEV(256,0);


// init function

static int __init ModuleStart(void){

    register_chrdev_region(device,1,"MyStaticDevice");
    pr_info("Major :- %d , Minor :- %d \n",MAJOR(device), MINOR(device));
    pr_info("The Kernel module is inserted successfully......\n");
    return 0;
}

static void __exit ModuleEnd(void){
    unregister_chrdev_region(device,1);
    pr_info("kernal Uloaded ......");
}

MODULE_LICENSE("GPL");

module_init(ModuleStart);
module_exit(ModuleEnd);