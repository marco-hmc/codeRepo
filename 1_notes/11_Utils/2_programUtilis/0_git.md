## git操作

> marco

[toc]

### 1. git基本操作

#### 1.1 git的工程区域和工作状态

* **工程区域**

  * **版本库(repository)**

    在工作区中有一个隐藏目录.git,这个文件夹就是git的版本库,里面存放了git用来管理该工程的所有版本数据,也可以叫本地仓库.

  * **工作区(working directory)**

    日常工作的代码文件或文档所在的文件夹

  * **暂存区(stage)**

    一般存放在工程根目录.git/index文件中,暂存区亦可称为索引(index)

* **提交状态**

  - **已提交(committed)** 

    该文件已被安全的保存到本地数据库中

  - **已修改(modified)** 

    修改了某个文件,但还没有提交

  - **已暂存(staged)** 

    把已修改的文件放在下次提交时要保存的清单中

#### 1.2 工程准备/工程下载

* `git init`
* `git clone`

#### 1.3 新增文件,删除/移动文件到暂存区

* `git add`
* `git rm`
* `git mv`

#### 1.4 提交代码推送代码

* `git commit`
* `git push [远端仓库名][本地分支名]`

#### 1.5 撤销操作

* `git reset`

  * `git reset [commit_id]` 用于撤销当前工作区中某些git add/commit操作,可以将工作区内容回退到历史提交节点(貌似只回退了历史节点没回退代码)

  * `git reset --hard [commit_id]` 强制回退历史节点及工作区代码

  * `git reset --soft [commit_id]` 强制回退历史节点及工作区代码


* `git revert`

  可以撤销某次提交,但与reset不同的是reset的撤销会从log中删除一条记录,而revert会增加一条撤销的记录

* `git checkout .` 用于回退本地所有修改而未提交的文件内容
* `git checkout -file_name` 仅回退某个文件的未提交改动
* `git checkout commit_id` 将工作区代码回退(检出)到某个提交版本

#### 1.5 查看差异以及历史信息

* `git diff`
* `git log`

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

* **`git add`是递归的吗?**

  不是,因此可以使用`git add -A`

* **commit点能够被删除吗?**

  你无法直接删除已提交的 commit.提交的历史记录在 Git 中被视为不可更改的.

  因此,一般是通过`git revert`和`git reset`修改commit点.

* **如何查看当前分支名称?**

  `git branch --show-current`

* **如何删除服务器远端分支?**

  1. `git branch -d -r branch_name` // branch_name为本地分支名
  2. `git push origin branch_name` // 将删除推送远端

* **`git pull`和`git fetch`的区别是什么?**

  `git pull`命令的作用是从远程仓库拉取最新的代码并合并到当前分支.它的执行相当于依次执行`git fetch`和`git merge`两个命令,即先获取远程仓库的更新,然后将更新合并到当前分支.

* **`origin`是什么?**

  当你克隆一个远程仓库时,Git 会默认给远程仓库起一个别名叫做 `origin`.

  * **为什么origin不能够作为缺省处理,难道还会有多个远程仓库?**

    是的,可能会有多个仓库.

    有多个团队同时开发一个产品.A团队开发公共组件,他们有一个仅包含公共组件相关代码的仓库;B团队开发业务层面的逻辑,他们既需要开发业务相关,也需要使用A团队的公共组件代码.因此对于B团队来说,他们需要同步更新A团队的仓库,他们是多仓库的.而对于A团队来说,他们不太需要考虑B团队,因此他们是单仓库的.

* **git merge和git rebase,是谁合并了谁?**

  例如,如果你当前在 `main` 分支上,想要将 `feature` 分支的更改合并到 `main` 分支上,可以执行以下命令:

  ```shell
  git checkout main
  git merge feature
  ```

  使用git merge和git rebase一般不显式指定两个分支,可能是怕谁合并谁带来太大的心智负担,因此一般都是切换到要保留的分支,然后合并其他分支.

* **git rebase和git merge的区别是什么?**

  1. **提交历史:**
     - `git merge` 会创建一个新的合并提交,将两个分支的更改合并在一起.合并提交的历史会保留每个分支的提交记录,并按照合并的顺序生成新的提交.
     - `git rebase` 将源分支上的每个提交应用到目标分支上,使得目标分支看起来像是在源分支的最新提交之后进行的开发.重放提交的历史看起来是线性的,没有合并提交的历史记录.
  2. **分支结构:**
     - `git merge` 保留原有的分支结构,合并后的分支会保留原有的分叉结构,合并提交可以形成一个分支合并的历史记录.
     - `git rebase` 会改写提交历史,将源分支上的每个提交都应用到目标分支上,因此目标分支的提交历史会变成一条线性的记录,没有分叉结构.
  3. **变基与冲突:**
     - `git merge` 通常会自动解决合并冲突.如果在合并过程中出现冲突,你需要手动解决冲突,并进行合并提交.
     - `git rebase` 在将源分支的提交应用到目标分支时,如果遇到冲突,你需要解决冲突并手动添加解决后的文件.这意味着在变基过程中可能会有多个冲突点需要处理.
  4. **公共分支和提交历史:**
     - `git merge` 适用于合并公共分支,或者在分支之间保留明确的分叉结构的情况.
     - `git rebase` 适用于保持干净/线性的提交历史,减少分支分叉.它常用于在开发分支上进行变基,以便将最新的更改应用到基准分支上.

  **选择使用 `git merge` 还是 `git rebase` 取决于以下因素:**

  - 分支的提交历史结构需求.
  - 需要保留合并记录还是想要一个干净的提交历史.
  - 是否愿意手动解决冲突以获得线性的提交历史.

* **一般git在团队协作时的使用基本流程时怎样的?**

  1. `git pull `拉下最新代码
  2. `git checkout `切换到自己的分支
  3. `git merge master `合并主分支代码
  4. `git add./ `提交代码到暂存区
  5. `git commit -m` 提到暂存区代码到本地
  6. `git push `推到远端

  * **更具体一点的操作**

    \1. 创建一个新的分支,该分支是功能分支,但是有多人一起开发,所以有对应的远端分支.这里称为A分支

    \2. 基于该分支切一个本地的分支,不需要有对应的远端分支,用来开发自己的任务.这里成为a分支

    \3. 需要养成经常拉远端代码的习惯,即A分支的代码要经常从远端更新.

    \4. a分支的代码按功能提交,每次提交一个完整的commit,每个commit不应该包含多个任务

    \5. 开发完成该功能之后切换到A分支,从远端更新代码,再将a分支合并过来,然后解决冲突,推到远端,删除a分支.

  

