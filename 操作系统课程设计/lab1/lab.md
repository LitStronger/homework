### linux内核编译及添加系统调用

注：文章共四部分，分别是

1、编译更换内核

2、添加一个简单系统系统调用

3、添加读取/修改nice值的系统调用

4、自己设计简单（真的简单）系统调用

四个部分结构相似，请根据自身需求自行选择观看。（ps有点唠叨的，但也比较完整）



### (一)、下载新内核并编译、更换：

##### 第一步：下载解压,进入文件夹

```
#wget <https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-#4.16.1.tar.xz> 
#xz –d linux-4.16.1.tar.xz
#tar –xvf linux-4.16.1.tar 
#cd linux-4.16.1
```

 ##### 第二步 ：清楚残留的 .config和 .o文件（每次编译出错或者重新编译最好都清理，不清理很占内存）

```
#make mrproper
```

 报错提醒安装ncurses，重新执行make mrproper

```
#apt-get install libncurses5-dev   
```

##### 第三步：配置内核

```
#make menuconfig 
```

根据报错提示安装组件，缺啥装啥

```
#sudo apt install build-essential //安装make和gcc等
#apt-get install libncurses5-dev	 //安装ncurses-devel
#sudo apt-get install flex		 //安装flex
#sudo apt-get install bison 		 //安装bison
```

没有报错后再执行

```
#make menuconfig 
```

出现配置的对话框，直接保存（save），文件名也默认.config, 退出。

##### 第四步：编译内核，生成启动映像文件

```
#make -j4 //-j4是用于加快编译速度。这里我是4核
```

报错提示要openssl，安装完再次执行命令即可

```
#apt-get install libssl-dev 
```

##### 第五步：编译模块

这一步要好久（2-3小时，可能虚拟机配置太低吧）。。。。睡一觉回来就好了

```
#make modules
```

##### 第六步：安装内核、模块

```
安装模块：# make modules_install 
安装内核：#make install
```

##### 第七步：配置 grub 引导程序 
只需要执行如下命令：该命令会自动修改 grub

```
#update-grub2
```

##### 最后一步重启：

```
#reboot -n
```

查看内核版本

```
#uname -a
```

![1582793333263](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582793333263.png)

成功更换内核！



 ### (二)、添加简单系统调用

系统调用表

- 用于关联系统调用号及其相对应的服务历程入口地址。例如系统调用read在系统调用表中结构如下

| 系统调用号 | 32/64/common | 系统调用名称 | 服务例程入口                             |
| ---------- | ------------ | ------------ | ---------------------------------------- |
| 0          | common       | read         | sys_read（这里不同内核版本格式有所不同） |

```path: /arch/x86/entry/syscalls/syscall_64.tbl(32位系统是syscall_32.tbl)```

##### 第一步：修改源程序

```
#cd linux-4.16.1 //进入linux解压包（我下的版本是4.16.1）
#vim arch/x86/entry/syscalls/syscall_64.tbl //进入该文件分配系统调用号 （注意别写在最后面，300多行，别写到下半部分的x32那一块里面）
```

![1582793550595](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582793550595.png)

```
#vim include/linux/syscalls.h 进入该文件，添加服务例程的原型声明（shift+g快速跳到最后一行）
```

 ![1582793882548](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582793882548.png)

```
vim kernel/sys.c 实现系统调用服务例程
```

SYSCALL_DEFINE后的数字代表参数个数，这里0个参数（void）

![1582793980496](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582793980496.png)

##### 第二步：编译安装内核

```
1. #make menuconfig 配置内核
2. #make –j2 编译内核
3. #make modules 编译模块
4. #make modules_install 和 make install 安装模块和安装内核
5. #update-grub2（好像虚拟机不需要这一步）
6. #reboot –n 立即重启
```

##### 第三步：新系统调用测试

这里编写一个test.c文件来测试（文件存放位置可以任意）

```
#vim test.c
```

![1582794361481](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582794361481.png)

编译

```
gcc test.c -o test //-o test指定编译输出文件名为test
```

![1582794469277](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582794469277.png)

执行文件

```
./test
```

查看信息

```
dmesg
```

![1582794530603](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582794530603.png)

可见系统调用成功执行

### (三)、添加API对指定进程的 nice 值的读取功能

```
注：nice值表示进程可被执行的优先级的修正数值,加入nice值后，将会使得PRI变为：PRI(new)=PRI(old)+nice。这样，当nice值为负值的时候，那么该程序将会优先级值将变小，即其优先级会变高，则其越快被执行。
```



##### 修改源程序

![1582797000178](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582797000178.png)

![1582796949772](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582796949772.png)

pid：进程ID

flag：等于1表示修改，等于0表示读取

nicevalue：为指定进程设置新的nice值

prio，nice：指向进程当前优先级prio及nice值

![1582808305521](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582808305521.png)

find_get_pid()

```
struct pid *find_get_pid(pid_t nr)
{
	struct pid *pid;

	rcu_read_lock();
	pid = get_pid(find_vpid(nr));
	rcu_read_unlock();

	return pid;
}
```

pid_task()

```
struct task_struct *pid_task(struct pid *pid, enum pid_type type)
{
	struct task_struct *result = NULL;
	if (pid) {
		struct hlist_node *first;
		first = rcu_dereference_check(hlist_first_rcu(&pid->tasks[type]),
					      rcu_read_lock_held() ||
					      lockdep_tasklist_lock_is_held());
		if (first)
			result = hlist_entry(first, struct task_struct, pids[(type)].node);
	}
	return result;
}
EXPORT_SYMBOL(pid_task);

enum pid_type
{
	PIDTYPE_PID,
	PIDTYPE_PGID,
	PIDTYPE_SID,
	PIDTYPE_MAX
};
```

copy_to_user函数则是从内核空间拷贝内容到用户空间，用户空间的进程无法直接访问内核空间的内容。这个函数做了数据合法判断。然后进行拷贝。

```
static inline int task_nice(const struct task_struct *p)
```

用于获取当前task的nice值，并返回nice值，nice值的范围是[ -20 ... 0 ... 19 ]
其使用的例程如下：

```
void set_user_nice(struct task_struct *p, long nice)
{
bool queued, running;
int old_prio, delta;
struct rq_flags rf;
struct rq *rq;

if (task_nice(p) == nice || nice < MIN_NICE || nice > MAX_NICE)
return;
}
```

return -EFAULT代表返回一个错误代码；

```
#define	EFAULT		14	/* Bad address */
```

```
#define	ESRCH		 3	/* No such process */
```

pid_t 其实就是__pid_t类型。

```
#ifndef __pid_t_defined
typedef __pid_t pid_t;

define __pid_t_defined

#endif
```



##### 编译安装内核

```
1. #make menuconfig 配置内核
2. #make –j2 编译内核
3. #make modules 编译模块
4. #make modules_install 和 make install 安装模块和安装内核
5. #update-grub2（好像虚拟机不需要这一步）
6. #reboot –n 立即重启
```

**编写测试程序：**

```
#vim test-nice.c  //在哪创建没有特别要求
```

![1582941471840](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582941471840.png)

```
#gcc nice-test.c -o nice-test   //编译，格式gcc <c代码文件> -o <输出文件的文件名>
#./nice-test 					//执行所生成的文件
```

![1582941337513](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582941337513.png)

```
#dmesg			//查看信息
```

![1582941916641](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1582941916641.png)



### (四)、自己设计系统调用

CONFIG_NR_CPUS是内核被配置支持的CPU个数，而实际设备的CPU个数是在系统启动过程当中去动态监测的。也就是说你配置系统支持32个CPU那么CONFIG_NR_CPUS就等于32，而num_online_cpus()则是当前设备激活可调度的CPU个数。

利用内核函数：

![1583398735285](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1583398735285.png)



由于大致流程与前面相似，这里便不再详述

分配系统调用号（335）

![1583399550731](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1583399550731.png)

添加服务例程原型声明

![1583399672061](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1583399672061.png)

实现系统调用服务例程

![1583400246725](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1583400246725.png)

编译安装

- #make mrproper
- #make -j4
- #make modules
- #make modules_install
- #make install
- #reboot -n

编写测试程序

![1583417793639](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1583417793639.png)

编译执行后, dmesg查看信息，如图

![1583417777075](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1583417777075.png)