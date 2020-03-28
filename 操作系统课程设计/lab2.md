

![1584005371071](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584005371071.png)

### 一、书上例程

##### （1）模块编译

```
#make
```

hello_exit()的没有参数时，应当补上void，否则报错如下

![1584006308122](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584006308122.png)

再次执行命令，成功编译

![1584006450184](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584006450184.png)

##### （2）加载模块命令（root权限下）

```
#insmod [filename] [module options...]或者
#modprobe [module options...] [modulename] [module parameters...] 
Modprobe 命令的功能与 insmod 一样，区别在于 modprobe 能够处理 module 载入的 相依问题
```

本例中

```
#insmod hello.ko  加载
#lsmod 			  查看
#dmesg			  查看输出
```

![1584006849418](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584006849418.png)



![1584007203815](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584007203815.png)

```
#rmmod hello.ko		卸载模块
#dmesg				查看输出
```

![1584007661831](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584007661831.png)

这里注意提示验证失败，，没有签名或者密钥

module没有签名，可以在驱动的Makefile文件里面添加这行CONFIG_MODULE_SIG=n来关掉验证

或者是在当前linux 系统的kernel源码下修改config文件，CONFIG_MODULE_SIG=n

### 二、kernel process information

##### 结构体task_struct成员（这里仅列出部分实验用到的）

mm 进程用户地址空间的描述符（内核线程的mm成员为空，内核态）

comm 相应的程序名

![1584020442830](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584020442830.png)

pid 进程号

state 状态

normal_prio 优先级 

parent->pid 父进程号

```
#define for_each_process(p) 
	for (p = &init_task ; (p = next_task(p)) != &init_task ; )
```



##### 编写代码lab2.c

```
#make 			编译
#insmod lab2.ko 模块导入
```

报错如下

![1584107596635](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584107596635.png)

使用root权限重新执行命令即可

```
#dmesg		查看
```

![1584107726750](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584107726750.png)

```
#rmmod lab2.ko	模块卸载
#dmesg			查看
```

![1584107830841](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584107830841.png)

### 三、process family information

```
#define module_param(name, type, perm)				
	module_param_named(name, name, type, perm)

/*参数解释*/
* @name: a valid C identifier which is the parameter name. 即参数名
* @value: the actual value to alter. 要更改的实际值
* @type: the type of the parameter. 参数类型 
* @perm: visibility in sysfs. 权限 0444：world(全局)-readable, 0644：root-writable
```

根据nr，在当前task所在的namespace下找到nr对应的struct pid结构体

```
struct pid *find_vpid(int nr)
{
	return find_pid_ns(nr, current->nsproxy->pid_ns);
}
EXPORT_SYMBOL_GPL(find_vpid);
```



```
struct task_struct *pid_task(struct pid *pid, enum pid_type type)
{
	struct task_struct *result = NULL;
	if (pid) {
		struct hlist_node *first;
		first = rcu_dereference_check(hlist_first_rcu(&pid->tasks[type]),
					      lockdep_tasklist_lock_is_held());
		if (first)
			result = hlist_entry(first, struct task_struct, pids[(type)].node);
	}
	return result;
}
EXPORT_SYMBOL(pid_task);
```

```
struct list_head {            //list_head不是拿来单独用的，它一般被嵌到其它结构中
	struct list_head *next, *prev;
};
```

```
enum pid_type
{
	PIDTYPE_PID,表示进程PID
	PIDTYPE_PGID,表示线程组领头的进程的PID
	PIDTYPE_SID,表示进程组领头的进程的PID
	PIDTYPE_MAX,表示会话组领头的进程的PID
};
```

```
#define list_for_each(pos, head) \
	for (pos = (head)->next; prefetch(pos->next), pos != (head); \
        	pos = pos->next)
* @pos:	the &struct list_head to use as a loop cursor.
* @head: the head for your list.
```

```
/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)
```

![1584158996882](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584158996882.png)

![1584159105742](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584159105742.png)