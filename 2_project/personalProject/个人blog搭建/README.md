1. [github+hexo的Blog搭建](https://zhuanlan.zhihu.com/p/35668237)

   其中有一个问题就是github现在不建议用http直接访问,因此hexo d无法直接推送.

   需要进行如下配置

   ![image-20220120151734812](https://s2.loli.net/2022/01/20/ZQbTom6xzn7FwNa.png)

2. [图床的搭建1](https://blog.csdn.net/qq_40020447/article/details/116792098) [图床的搭建2](https://cdmana.com/2022/01/202201101803153680.html)

   上面两个搭配来看,我试了一下gitee和腾讯云cos都不能用了.

   ![image-20220120152112727](https://s2.loli.net/2022/01/20/LHOrvJl6dy4PMzf.png)

   而因为我在linux上用,是没有app支持的,只有用自定义命令模式.

3. github+hexo的搭配会导致github pages的markdown文件无法很好渲染，渲染效果不好，因此还是改用jekyll

4. 大概步骤流程如下

   1. 设置仓库，开启github pages

   2. 将仓库git clone到本地文件夹blog，将网上的[jekyll theme](http://jekyllthemes.org/)放到blog这个文件夹,修改config.yml将baseurl 设置为`“”`，为什么改这个看[这里](https://stackoverflow.com/questions/48197580/jekyll-theme-does-not-work-on-github-pages-but-works-locally)

   3. 安装jekyll环境

   4. 将仓库用`git add --all // git commit -m "" // git push -u originmain`推送到github上

   5. 在`_post`文件夹下写自己的博文即可

      开头都要有头信息，与其他md文件相同即可。

   [参考1](https://yuchuanfeng.github.io/posts/github-pages-blog/)

   [参考2](https://www.wangzhaomin.com/docs/jekyll/how-to-push-Jekyll's-blog-to-github/)

   