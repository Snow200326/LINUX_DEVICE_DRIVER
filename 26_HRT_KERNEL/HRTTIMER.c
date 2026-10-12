#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/hrtimer.h>


struct hrtimer Timer;

static int __init Module_start(void);
static void __exit Moudle_end(void);

static enum hrtimer_restart TimerCallback(struct hrtimer *timer)
{
   
    pr_info("5 seconds are up! This runs exactly once.\n");

    // SOLUTION: Return NORESTART. Do NOT call hrtimer_forward_now here.
    return HRTIMER_NORESTART; 
}


static int __init Module_start(void){
    ktime_t delay;
    pr_info("Module Loaded.....\n");

    hrtimer_setup(&Timer,TimerCallback,CLOCK_MONOTONIC,HRTIMER_MODE_ABS);
    delay = ktime_set(5,0);
    hrtimer_start(&Timer,delay,HRTIMER_MODE_ABS);
    return 0;
}
static void __exit Moudle_end(void)
{
    
    hrtimer_cancel(&Timer);
    pr_info("HTRTIMER REMOVE.....");

}



module_init(Module_start);
module_exit(Moudle_end);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("DNYANESH");
MODULE_DESCRIPTION("HIGH RESOLUTION TIMER");
MODULE_VERSION("1.26");