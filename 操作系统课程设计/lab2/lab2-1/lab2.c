#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>

static int function_init(void)
{
	struct task_struct *p;
	p = NULL;
	p = &init_task;
	printk("welcome! Here is the kernel processes infomation\n");
	printk(KERN_ALERT"name\tPID\tstate\tpriority\tPPID\t");
	for_each_process(p)
	{
		if(p->mm == NULL){ //the mm of kernel thread is NULL,so here only kernel threads will be output
			printk(KERN_ALERT"%s\t%d\t%ld\t%d\t%d\n", p->comm, p->pid,p->state, p->normal_prio, p->parent->pid);
		}
	}
	return 0;
}

static void function_exit(void)
{
	printk(KERN_ALERT"goodbye!\n");
}

module_init(function_init);
module_exit(function_exit);


MODULE_LICENSE("GPL");

