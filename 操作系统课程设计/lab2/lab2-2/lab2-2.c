#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>

static pid_t pid=1;
module_param(pid, int, 0644);

static int proc_family_info_init(void)
{
	struct task_struct *proc;
	struct list_head *proc_ptr;
	struct task_struct *proc_sibling;

	/*current pid*/
	proc = pid_task(find_vpid(pid), PIDTYPE_PID);
	printk("current process--pid:%d name:%s\n", proc->pid, proc->comm);

	if(proc->parent == NULL){
		printk("no parent process\n");
	}
	else {
		printk("parent process--pid:%d name:%s\n", proc->parent->pid, proc->parent->comm);
	}

	/*brother process*/	
	list_for_each(proc_ptr, &proc->parent->children){
		proc_sibling = list_entry(proc_ptr, struct task_struct, sibling);
		printk("sibling process--pid:%d name:%s\n", proc_sibling->pid, proc_sibling->comm);		
	}

	/*children process*/
	list_for_each(proc_ptr, &proc->children){
		proc_sibling = list_entry(proc_ptr, struct task_struct, sibling);
		printk("children process--pid:%d name:%s\n", proc_sibling->pid, proc_sibling->comm);
	}
	return 0;

}

static void proc_family_info_exit(void)
{
	printk(KERN_ALERT"goodbye!\n");
}

module_init(proc_family_info_init);
module_exit(proc_family_info_exit);

MODULE_LICENSE("GPL");


