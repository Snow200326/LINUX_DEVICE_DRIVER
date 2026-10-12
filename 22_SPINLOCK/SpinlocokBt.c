#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>

static DEFINE_SPINLOCK(my_lock);

static int counter = 0;

static struct tasklet_struct my_tasklet;

/* Bottom-half context: tasklet callback */
static void my_tasklet_fn(struct tasklet_struct *t)
{
    spin_lock(&my_lock);

    counter++;

    pr_info("Tasklet: counter = %d\n", counter);

    spin_unlock(&my_lock);
}

/* Process-context function */
static void process_context_function(void)
{
    // int value;

    // spin_lock_bh(&my_lock);
    spin_lock(&my_lock);
    

    counter++;

    // value = counter;
    spin_unlock(&my_lock);


    pr_info("Process context: counter = %d\n", counter);

    // spin_unlock_bh(&my_lock);
}

static int __init locking_bh_init(void)
{
    pr_info("Locking BH module loaded\n");

    tasklet_setup(&my_tasklet, my_tasklet_fn);

    tasklet_schedule(&my_tasklet);
    process_context_function();


    return 0;
}

static void __exit locking_bh_exit(void)
{
    tasklet_kill(&my_tasklet);

    pr_info("Locking BH module unloaded\n");
}

module_init(locking_bh_init);
module_exit(locking_bh_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Locking between process context and bottom halves");