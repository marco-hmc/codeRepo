## 介绍

​	ubuntu下划词翻译脚本。

### 1. 翻译

1. 安装sdcv：
      $ sudo apt-get install sdcv

2. [下载字典](http://download.huzheng.org/zh_CN/)
   安装了不带数据的sdcv，不能使用，需要下载字典。下载地址是：[stardict dictionaries](http://download.huzheng.org/zh_CN/)要下载tarbal(即tar.bz2)格式。有计算机词典，朗道词典，成语字典.
   
3. 解压

   解压，将解压后的文件夹放到“/usr/share/stardic/dic”这里文件夹/stardic和/dic需要你自己创建，并且用chmod修改权限

   ​	然后，终端上输入sdcv hello，你会看到词典库加载成功的提示。

   4.让我们来写个脚本，利用快捷键运行

​	#!/bin/bash

​	word=`xclip -out`

​	mean=`sdcv -n ${word}|grep "^[a-z]"`

​	pkill notify-osd

​	notify-send  "$mean"

​	把这个脚本命名为xxx.sh然后保存在某个地方。我们打开系统设置-》键盘-》快捷键-》自定义快捷键

`gnome-terminal -x bash -c /home/marco/hmc/software/translator/notify-translate.sh`

### 2. 划词发音

https://www.jianshu.com/p/bee8ea9729c9

1. 下载音频
2. 使用shell编程，在命令行播放。

