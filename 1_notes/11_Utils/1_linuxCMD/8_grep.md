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
