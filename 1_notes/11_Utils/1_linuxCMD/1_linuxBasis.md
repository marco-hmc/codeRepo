## linuxBasicCmd

### 1. 查看文件
- more
- less
- cat
- head
- tail
- nl
- find
- egrep

### grep
* grep常用的参数
  `grep` 是一个强大的文本搜索工具,它有许多常用的参数来帮助你定制搜索.以下是一些常用的 `grep` 参数:
    - `-i`:忽略大小写.例如,`grep -i "hello" file.txt` 会在 `file.txt` 中搜索 "hello",不区分大小写.
    - `-v`:反向匹配,即列出不匹配指定模式的行.例如,`grep -v "error" file.txt` 会列出 `file.txt` 中不包含 "error" 的行.
    - `-r` 或 `-R`:递归搜索.例如,`grep -r "hello" dir/` 会在 `dir/` 目录及其所有子目录中搜索 "hello".
    - `-l`:只列出包含匹配行的文件名,而不是匹配行本身.例如,`grep -l "hello" file1.txt file2.txt` 会列出包含 "hello" 的文件名.
    - `-n`:显示匹配行的行号.例如,`grep -n "hello" file.txt` 会在 `file.txt` 中搜索 "hello",并显示匹配行的行号.
    - `-e`:允许使用多个模式进行搜索.例如,`grep -e "hello" -e "world" file.txt` 会在 `file.txt` 中搜索 "hello" 或 "world".
    - `-w`:只匹配整个单词,而不是字符串的一部分.例如,`grep -w "log" file.txt` 会匹配 "log" 这个单词,而不会匹配 "blog" 或 "logs".
    - `-c`:计算匹配行的数量.例如,`grep -c "hello" file.txt` 会计算 `file.txt` 中 "hello" 的数量.
    * your_command | grep -e "要搜索的单词" -n -m 1 -B 1 > 输出文件名
    * (your_command | head -n 1; your_command | grep "你的单词") > 输出文件名 

### 2. 查看后台进程
* jobs

查看当前控制台的后台进程

想要停止后台进程,使用jobs命令查看其进程号(比如为num),然后kill %num即可

* ps

查看后台进程

* top

查看所有进程和资源使用情况,类似Windows中的任务管理器

停止进程:界面是交互式的,在窗口输入k 之后输入PID,会提示输入停止进程模式 有SIGTERM和 SIGKILL 如果留空不输入,就是SIGTERM(优雅停止)

退出top:输入q即可

### 3. 其他
#### 3.1 crontab命令
详见:https://www.cnblogs.com/peida/archive/2013/01/08/2850483.html

corntab命令是用来指定用户计划任务的.用户将需要定时执行的任务写入crontab文件中,提交给crond进程定期执行.

* crontab命令用来对crontab文件进行管理
```
1．命令格式:
crontab [-u user] file
crontab [-u user] [ -e | -l | -r ]
2．命令功能:
通过crontab 命令,我们可以在固定的间隔时间执行指定的系统指令或 shell script脚本.时间间隔的单位可以是分钟/小时/日/月/周及以上的任意组合.这个命令非常设合周期性的日志分析或数据备份等工作.
3．命令参数:
-u user:用来设定某个用户的crontab服务,例如,"-u ixdba"表示设定ixdba用户的crontab服务,此参数一般有root用户来运行.
file:file是命令文件的名字,表示将file做为crontab的任务列表文件并载入crontab.如果在命令行中没有指定这个文件,crontab命令将接受标准输入(键盘)上键入的命令,并将它们载入crontab.
-e:编辑某个用户的crontab文件内容.如果不指定用户,则表示编辑当前用户的crontab文件.
-l:显示某个用户的crontab文件内容,如果不指定用户,则表示显示当前用户的crontab文件内容.
-r:从/var/spool/cron目录中删除某个用户的crontab文件,如果不指定用户,则默认删除当前用户的crontab文件.
-i:在删除用户的crontab文件时给确认提示.
```

* crontab文件内容

crond是Linux下的周期性执行系统任务的守护进程,他会根据/etc下的crontab配置文件的内容执行.用户需要将计划任务写入crontab文件中才能执行.

用户所建立的crontab文件中,每一行都代表一项任务,每行的每个字段代表一项设置,它的格式共分为六个字段,前五段是时间设定段,第六段是要执行的命令段,格式如下:
```
minute   hour   day   month   week   command

其中:
minute: 表示分钟,可以是从0到59之间的任何整数.
hour:表示小时,可以是从0到23之间的任何整数.
day:表示日期,可以是从1到31之间的任何整数.
month:表示月份,可以是从1到12之间的任何整数.
week:表示星期几,可以是从0到7之间的任何整数,这里的0或7代表星期日.
command:要执行的命令,可以是系统命令,也可以是自己编写的脚本文件.
在以上各个字段中,还可以使用以下特殊字符:
星号(*):代表所有可能的值,例如month字段如果是星号,则表示在满足其它字段的制约条件后每月都执行该命令操作.
逗号(,):可以用逗号隔开的值指定一个列表范围,例如,"1,2,5,7,8,9"
中杠(-):可以用整数之间的中杠表示一个整数范围,例如"2-6"表示"2,3,4,5,6"
正斜线(/):可以用正斜线指定时间的间隔频率,例如"0-23/2"表示每两小时执行一次.同时正斜线可以和星号一起使用,例如*/10,如果用在minute字段,表示每十分钟执行一次.
```



### lsof
* lsof
    `lsof` 是一个在 Unix 和类 Unix 系统(如 Linux)上用于列出打开的文件的实用程序.以下是一些常见和有用的 `lsof` 参数:

  - `-u`:按照用户或用户组来筛选文件.例如,`lsof -u username` 会列出所有由用户 `username` 打开的文件.
  - `-c`:按照命令名来筛选文件.例如,`lsof -c ssh` 会列出所有由 `ssh` 命令打开的文件.
  - `-p`:按照进程 ID 来筛选文件.例如,`lsof -p 1234` 会列出所有由进程 ID 为 `1234` 的进程打开的文件.
  - `-i`:按照网络连接来筛选文件.例如,`lsof -i TCP` 会列出所有使用 TCP 协议的网络连接.
  - `-d`:按照文件描述符来筛选文件.例如,`lsof -d 2` 会列出所有使用文件描述符 `2` 的文件.
  - `+D`:列出指定目录下被打开的文件.例如,`lsof +D /path/to/directory` 会列出 `/path/to/directory` 目录下所有被打开的文件.


### monitor