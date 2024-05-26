## git操作

> marco

[toc]

### 0. 常用git指令

* 代理设置
  * `git config --global http.proxy http://127.0.0.1:7890`
  * `git config --global https.proxy https://127.0.0.1:7890`
* 查看设置
  * `git config --global -l`


### 1. git基本操作

#### 1.1 git的工程区域和工作状态

* **工程区域**

  * **版本库(repository)**

    在工作区中有一个隐藏目录.git,这个文件夹就是git的版本库,里面存放了git用来管理该工程的所有版本数据,也可以叫本地仓库.

  * **工作区(working directory)**

    日常工作的代码文件或文档所在的文件夹

  * **暂存区(stage)**

    一般存放在工程根目录.git/index文件中,暂存区亦可称为索引(index)

#### 1.2 工程准备/工程下载

* `git init`
* `git clone`

#### 1.4 提交代码推送代码

* `git commit`
* `git push [远端仓库名][本地分支名]`

#### 1.5 撤销操作

* `git reset`

  * `git reset [commit_id]` 用于撤销当前工作区中某些git add/commit操作,可以将工作区内容回退到历史提交节点(貌似只回退了历史节点没回退代码)

  * `git reset --hard [commit_id]` 强制回退历史节点及工作区代码

  * `git reset --soft [commit_id]` 强制回退历史节点及工作区代码

#### 1.6 分支管理

* `git branch`

  * `git branch -r`

    查看远端分支

  * `git branch --show-current`

    查看当前分支

  * `git branch -a`

    查看本地和远端分支

  * `git branch -d [NAME]`

    删除指定分支

  * `git branch -f A B`

    是 Git 中用于移动分支指针的命令.具体含义如下:

    - `A` 是目标分支名,代表你想要移动的目标分支.
    - `B` 是目标分支指针的新位置,可以是一个提交哈希值/一个分支名或一个标签名.

    该命令的作用是将目标分支 `A` 的指针强制移动到指定的位置 `B`,忽略目标分支当前的位置.

  * `git branch [NAME]`

    新建分支

  * `git switch [NAME]`

    切换分支

#### 1.7 更新本地代码

* `git pull`
  * `git pull origin remote_branch:local_branch` 更新远端代码到本地
  * `git pull origin remote_branch` 远程指定分支与本地指定分支相同
* `git fetch`
  - `git fetch origin remote_branch:local_branch` 获取远端更新(分支名不同)
  - `git fetch origin remote_branch` 获取远端更新(分支名相同)

#### 1.8 合并代码

* `git merge branch_name` 将指定分支合并到当前分支
* `git rebase branch_name` 将指定分支合并到当前分支

### 2. commit点处理

#### 2.1 commit点信息修改

* `git commit --amend`

  是用于修改最近一次提交的命令.它可以用于修改提交的消息/添加漏掉的文件或修改文件的内容.

#### 2.2 commit点移动

* `git cherry-pick`

  cherry-pick 可以将提交树上任何地方的提交记录取过来追加到 HEAD 上(只要不是 HEAD 上游的提交就没问题).

  是一个用于选择性地应用单个提交的命令.它可以将指定的提交复制到当前分支上,而不会复制其他提交历史.

### 3. config

* git config
    配置被写在~/.git/config
    可以通过git config --list 查看

git config --global http.proxy 'socks5://127.0.0.1:7890'
git config --global https.proxy 'socks5://127.0.0.1:7890'


### 3. config

#### 3.1 .gitattributes

.gitattributes怎么用?
`.gitattributes` 文件是一个文本文件,放在 Git 仓库的根目录或其子目录中,用于定义文件的属性.每一行都是一个模式(pattern)和一个或多个属性,模式和属性之间用空格分隔.

以下是一些常见的 `.gitattributes` 文件的用法:

1. 设置行尾风格:你可以使用 `text` 属性来设置文件的行尾风格.例如,如果你想让所有的 `.txt` 文件在提交时自动转换为 LF 行尾,你可以添加以下行:

   ```
   *.txt text
   ```

2. 设置二进制文件:你可以使用 `binary` 属性来标记二进制文件,这样 Git 就不会尝试对它们进行合并或查找差异.例如,如果你想让所有的 `.jpg` 文件被视为二进制文件,你可以添加以下行:

   ```
   *.jpg binary
   ```

3. 设置文件的合并策略:你可以使用 `merge` 属性来设置文件的合并策略.例如,如果你想让所有的 `.html` 文件使用 `html` 合并策略,你可以添加以下行:

   ```
   *.html merge=html
   ```

4. 设置文件的差异策略:你可以使用 `diff` 属性来设置文件的差异策略.例如,如果你想让所有的 `.py` 文件使用 `python` 差异策略,你可以添加以下行:

   ```
   *.py diff=python
   ```

5. 设置导出忽略:你可以使用 `export-ignore` 属性来设置在导出操作(如 `git archive`)时应忽略的文件.例如,如果你不想将 `.gitignore` 文件包含在导出的存档中,你可以添加以下行:

   ```
   .gitignore export-ignore
   ```

注意,`.gitattributes` 文件中的设置对所有的 Git 操作都有效,包括 `git diff`/`git merge` 和 `git add` 等.如果你想要覆盖全局的设置,你可以在项目的子目录中创建另一个 `.gitattributes` 文件.

### 4. 其他操作

#### 4.1 版本号


#### 4.2 stash

* `git stash save [MSG]`

  存储代码或者将代码从存储中取出

  使用git stash save 'label' 就是将修改的代码存储起来

  使用git stash pop 就是将存储起来的代码取出来,不加任何的参数就说取出栈顶的那个,可以使用git stash list 查看存储的列表

* `git stash list` 

  查看存储区的内容

* `git stash drop index `

  删除第index条内容,不指定就是最近一条

* `git stash pop `

  将最近的一条内容从存储区取出,存储区里就没有了


#### 3.3 squash

* **`squash`的使用**

  在 Git 中,`squash` 是一种合并提交(commit)的方式,它允许将多个连续的提交合并为一个新的提交,并将这个新的提交添加到当前分支的提交历史中.这样可以使提交历史更加整洁和易于阅读,特别是当你在开发过程中有多个较小的提交,但希望将它们合并为一个有意义的提交时.

  要使用 `squash`,你可以使用交互式变基(interactive rebase)来重写提交历史.下面是使用 `squash` 的步骤:

  1. 使用 `git log` 查看当前分支的提交历史,确定要合并的提交范围.假设你要合并从 `HEAD~3`(倒数第三个提交)开始的三个提交.

  2. 执行交互式变基命令:

     ```
     bashCopy code
     git rebase -i HEAD~3
     ```

  3. Git 将会打开一个文本编辑器,显示类似以下内容的交互式界面:

     ```
     graphqlCopy codepick abc123 Commit message 1
     pick def456 Commit message 2
     pick ghi789 Commit message 3
     
     # Rebase xxxxx onto yyyyy
     #
     # Commands:
     #  p, pick = use commit
     #  r, reword = use commit, but edit the commit message
     #  e, edit = use commit, but stop for amending
     #  s, squash = use commit, but meld into previous commit
     #  f, fixup = like "squash", but discard this commit's log message
     #  x, exec = run command (the rest of the line) using shell
     #
     # These lines can be re-ordered; they are executed from top to bottom.
     #
     # If you remove a line here THAT COMMIT WILL BE LOST.
     #
     # However, if you remove everything, the rebase will be aborted.
     #
     # Note that empty commits are commented out
     ```

  4. 将要合并的提交前面的 `pick` 关键字改为 `squash` 或简写为 `s`.这将把后续提交合并到当前提交中.

     ```
     sqlCopy codepick abc123 Commit message 1
     squash def456 Commit message 2
     squash ghi789 Commit message 3
     ```

  5. 保存并关闭编辑器.Git 将会合并这三个提交为一个新的提交.

  6. 在编辑器中,Git 会打开一个新的编辑器用于编辑合并提交的提交信息.你可以编辑并保存提交信息.

  7. 保存并关闭编辑器.完成后,Git 将会创建一个新的合并提交,并将其添加到当前分支的提交历史中.

  需要注意的是,使用 `squash` 会改写提交历史,因此谨慎使用,特别是在与其他人共享代码时.如果提交已经被推送(push)到远程仓库,应避免对这些提交使用 `squash`,以免导致冲突和混乱的提交历史.

### 99. git问答

* **commit点能够被删除吗?**

  你无法直接删除已提交的 commit.提交的历史记录在 Git 中被视为不可更改的.

  因此,一般是通过`git revert`和`git reset`修改commit点.

* **如何删除服务器远端分支?**

  1. `git branch -d -r branch_name` // branch_name为本地分支名
  2. `git push origin branch_name` // 将删除推送远端

* **git merge和git rebase,是谁合并了谁?**

  例如,如果你当前在 `main` 分支上,想要将 `feature` 分支的更改合并到 `main` 分支上,可以执行以下命令:

  ```shell
  git checkout main
  git merge feature
  ```

  使用git merge和git rebase一般不显式指定两个分支,可能是怕谁合并谁带来太大的心智负担,因此一般都是切换到要保留的分支,然后合并其他分支.
