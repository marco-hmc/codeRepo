# 基本排序算法

## 总结

| 排序算法 |      平均时间复杂度       |         最好情况          |         最坏情况          |       空间复杂度       | 排序方式  | 稳定性 |
| :------: | :-----------------------: | :-----------------------: | :-----------------------: | :--------------------: | :-------: | :----: |
| 冒泡排序 |    $ \textbf{O}(n^2) $    |     $ \textbf{O}(n) $     |    $ \textbf{O}(n^2) $    |   $ \textbf{O}(1) $    | In-place  |  稳定  |
| 选择排序 |    $ \textbf{O}(n^2) $    |    $ \textbf{O}(n^2) $    |    $ \textbf{O}(n^2) $    |   $ \textbf{O}(1) $    | In-place  | 不稳定 |
| 插入排序 |   $ \textbf{O}(n^{2}) $   |     $ \textbf{O}(n) $     |    $ \textbf{O}(n^2) $    |   $ \textbf{O}(1) $    | In-place  |  稳定  |
| 希尔排序 |  $ \textbf{O}(n\log n) $  |  $ \textbf{O}(n^{1.3}) $  |    $ \textbf{O}(n^2) $    |   $ \textbf{O}(1) $    | In-place  | 不稳定 |
| 归并排序 |  $ \textbf{O}(n\log n) $  |  $ \textbf{O}(n\log n) $  |  $ \textbf{O}(n\log n) $  |   $ \textbf{O}(n) $    | Out-place |  稳定  |
| 快速排序 |  $ \textbf{O}(n\log n) $  |  $ \textbf{O}(n\log n) $  |    $ \textbf{O}(n^2) $    | $ \textbf{O}(\log n) $ | In-place  | 不稳定 |
|  堆排序  |  $ \textbf{O}(n\log n) $  |  $ \textbf{O}(n\log n) $  |  $ \textbf{O}(n\log n) $  |   $ \textbf{O}(1) $    | In-place  | 不稳定 |
|          |                           |                           |                           |                        |           |        |
| 计数排序 |    $ \textbf{O}(n+k) $    |    $ \textbf{O}(n+k) $    |    $ \textbf{O}(n+k) $    |  $ \textbf{O}(n+k) $   | Out-place |  稳定  |
|  桶排序  |    $ \textbf{O}(n+k) $    |     $ \textbf{O}(n) $     |    $ \textbf{O}(n^2) $    |  $ \textbf{O}(n+k) $   | Out-place |  稳定  |
| 基数排序 | $ \textbf{O}(n\times k) $ | $ \textbf{O}(n\times k) $ | $ \textbf{O}(n\times k) $ |  $ \textbf{O}(n+k) $   | Out-place |  稳定  |

* 平均时间复杂度同样是$ \textbf{O}(n\log n) $，为什么快速排序要比堆排序性能好？
  * 堆排序访问数据的方式没有快速排序友好
    * **对于快速排序来说，数据是顺序访问的。而对于堆排序来说，数据是跳着访问的。**比如，堆排序中，最重要的一个操作就是数据的堆化。比如下面这个例子，对堆顶进行堆化，会依次访问数组下标是1，2，4，8的元素，而不像快速排序那样，局部顺序访问，所以，**这样对CPU缓存是不友好的**
  * 对于同样的数据，在排序过程中，堆排序算法的数据交换次数要多于快速排序
    * 对于基于比较的排序算法来说，整个排序过程是由两个基本操作组成的，比较和交换。**快速排序交换的次数不会比逆序的多。但是堆排序的第一步是建堆，建堆的过程会打乱数据原有的相对选择顺序，导致数据有序度降低。比如对于一组已经有序的数据来说，经过建堆之后，数据反而变得更无序了**


# KMP算法

* 代码实现

  ```c++
  class Solution {
  public:
      int strStr(string target, string pattern) 
      {
          if(pattern.empty())
              return 0;
          if(target.size() < pattern.size())
              return -1;
          vector<int> next(pattern.size(), 0);
          findNext(pattern, next);
          int i = 0, j = 0, tlen = target.size(), plen = pattern.size();
          while(i < tlen && j < plen) {
              if(j == -1 || target[i] == pattern[j]) {
                  i++;
                  j++;
              }
              else {
                  j = next[j];
              }    
          }
          if(j >= plen) {
              return i - plen;
          }
          return -1;
      }
  
      void findNext(string & str, vector<int> &next)
      {
          next[0] = -1;
          int i = 0, k = -1;
          int len = str.size();
          while(i < len - 1) {
              if(k == -1 || str[i] == str[k]) {
                  i++;
                  k++;
                  if(str[i] != str[k]) {
                   	next[i] = k;   
                  }
                  else {
                      next[i] = next[k];
                  }
              }
              else {
                  k = next[k];
              }  
          }
      }
  };
  ```
  

# 取模(mod)基本运算法则

1. $(a+b)\% p=(a\% p+b\% p)\% p$
2. $(a-b)\% p=(a\% p-b\% p)\% p$
3. $(a\times b)\% p=(a\% p\times b\% p)\% p$
4. $a^b\% p=((a\% p)^b)\% p$
5. 由1得：$(\sum_{1}^{n}x)\%p=(\sum_{1}^{n}x\%p)\%p$
6. 结合律
   1. $((a+b)\%p+c)\%p=(a+(b+c)\%p)\%p$
   2. $((a\times b)\%p \times c)\%p= (a \times (b\times c)\%p)\%p$
7. 交换律
   1. $(a+b)\%p=(b+a)\%p$
   2. $(a\times b)\%p=(b\times a)\%p$
8. 分配律
   1. $(a+b)\%p=(a\%p+b\%p)\%p$
   2. $((a+b)\%p\times c)\%p = ( (a\times c)\%p + (b\times c)\%p )\%p$

# 大数越界情况下的求余问题

* 解决方案：循环求余和快速幂求余法，其中后者的时间复杂度更低，两种方法均基于以下求余运算规则推出：
  $$
  (xy)\odot p=[(x\odot p)(y\odot p)]\odot p
  $$

## 循环求余法

* 根据求余运算性质推出
  $$
  x^a \odot p=[(x^{a−1}\odot p)(x\odot p)]\odot p=[(x^{a−1}\odot p)x]\odot p,其中x<p,x\odot p=x
  $$

* 解析： 利用此公式，可通过循环操作依次求$ x^1, x^2, ..., x^{a-1}, x^a $对 $p$ 的余数，保证每轮中间值 `rem` 都在 `int32` 取值范围中，代码如下

  ```c++
  int remainder(int x, int a, int p){
      int rem = 1;
      while(a--){
          rem = (rem * x) % p;
      }
      return rem;
  }
  ```

* 时间复杂度 $O(N)$ ： 即循环的线性复杂度

## 快速幂求余

* 根据求余运算性质推出
  $$
  x^a \odot p=(x^2)^{a/2}\odot p
  $$

* 当a为奇数时，a/2不是整数，分如下两种情况
  $$
  x^a \odot p=\left\{\begin{align}
    &(x^2\odot p)^{a//2}\odot p&,		a为偶数\\
    &[(x\odot p)(x^{a-1}\odot p)]\odot p=[x(x^2\odot p)^{a//2}]\odot p&,a为奇数
  
  \end{align}\right.
  $$
  
* 解析： 利用以上公式，可通过循环操作每次把指数 a 问题降低至指数 a//2问题，只需循环 $log_2(N)$ 次，因此可将复杂度降低至对数级别，实现代码如下

  ```c++
  int fast_remainder(int x, int a, int p){
      int rem = 1;
      while(a>0){
          if(a & 1 == 0){
              rem = (rem * x) % p;
          }
          x = x*x % p;
          a = a / 2;
      }
      return rem;
  }
  ```

# 图的基本概念和术语
1. 图的定义
$$\begin{aligned}
&G=(V,E) \\
&V\text{(Vertex):顶点（数据元素）的有穷非空集合；} \\
&E\text{(Edge):边的有穷集合。}
\end{aligned}$$
2. 有向图：图中每条边都是有方向的，有向图的边也称作“弧”
3. 无向图：图中每条边都是无方向的
4. 完全图：图中任意两个顶点之间都有一条边相连。完全图分为有向完全图和无向完全图，如下图示
<img src="https://img-blog.csdnimg.cn/20201023102435499.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:67%;" />
若图中有$n$个顶点，无向完全图共有$C_n^2=\frac{n(n-1)}{2}$条边，而有向完全图共有$2C_n^2=n(n-1)$条边。
5. 稀疏图：有很少边或弧的图（$e<n\log n$）,$e$为边或弧的数目，$n$为顶点数目
6. 稠密图：有较多边或弧的图
7. 网：边/弧带权的图
8. 邻接：有边/弧相连的两个顶点之间的关系。在无向图中，存在$(V_i,V_j)$，则称$V_i$和$V_j$**互为邻接点**；同样，在有向图中，存在$<V_i,V_j>$，则称$V_i$**邻接到**$V_j$，$V_j$**邻接于**$V_i$。
9. 关联（依附）：边/弧与顶点之间的关系。存在$(V_i,V_j)$/$<V_i,V_j>$，则称该边关联于$V_i$和$V_j$。
10. 顶点的度：与某顶点$v$相关联的边/弧的数目，记为TD($v$)。在有向图中，顶点的度等于该顶点的**入度**和**出度**之和。顶点$v$的入度是以$v$为终点的有向边的条数，记作ID($v$)；而顶点$v$的出度是以$v$为始点的有向边的条数，记作OD($v$)。
11. 路径：接续的边构成的顶点序列。
12. 路径长度：路径上的边/弧数目，或权值之和。
13. 回路（环）：第一个顶点和最后一个顶点相同的路径。
14. 简单路径：除路径起点和终点可以相同外，其他顶点均不相同的路径。
15. 简单回路（简单环）：除路径起点和终点相同外，其余顶点均不相同的路径。
<img src="https://img-blog.csdnimg.cn/20201023233353684.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom: 50%;" />
16. 连通图/强连通图：在无/有向图$G=(V,\{E\})$中，若对任意两个顶点$v,u$都存在从$v$到$u$的路径，则称$G$是连通图/强连通图。
<img src="https://img-blog.csdnimg.cn/20201023234146290.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom: 50%;" />
17. 权与网：图中边或弧所具有的相关系数称为权。**带权的图称为网**。
18. 子图：设有两个图$G=(V,\{E\})$，$G_1=(V_1,\{E_1\})$，若$V_1\subseteq V$，$E_1\subseteq E$，则称$G_1$是$G$的子图。
<img src="https://img-blog.csdnimg.cn/20201023234754289.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:50%;" />
19. 极大连通子图：若某子图$G_1$是$G$的连通子图，若$G$的任一不在$G_1$的顶点加入$G_1$，得到的子图不再连通，则称$G_1$为$G$的极大连通子图。
20. 连通分量：无向图$G$的极大连通子图称为$G$的连通分量。
<img src="https://img-blog.csdnimg.cn/20201023235549327.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:50%;" />
21. 极大强连通子图：若某子图$G_1$是$G$的强连通子图，若$G$的任一不在$G_1$的顶点加入$G_1$，得到的子图不再强连通，则称$G_1$为$G$的极大连通子图。
22. 强连通分量：有向图$G$的极大强连通子图称为$G$的强连通分量。
<img src="https://img-blog.csdnimg.cn/20201024000013317.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:50%;" />
23. 极小连通子图：若某子图$G_1$是$G$的连通子图，若删除$G_1$的任一条边，得到的子图不再连通，则称$G_1$为$G$的极小连通子图。
24. 生成树：包含无向图$G$所有顶点的极小连通子图。
25. 生成森林：对非连通图，由各个连通分量的生成树组成的集合。
<img src="https://img-blog.csdnimg.cn/20201024000619100.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:50%;" />
# 图的存储结构
1. 数组表示法：邻接矩阵
2. 链表存储结构：邻接表、邻接多重表、十字链表
## 邻接矩阵表示法
表示方法：建立一个**顶点表**（一维数组），记录顶点信息，再建立一个**邻接矩阵**（二维数组）表示各个顶点之间的关系。设图$G=(V,E)$​有$n$​个顶点，则顶点表 Vtxs[$n$​ ]为


|    $i$     |  $0$  |  $1$  |  $2$  |   ...   | $n-1$ |
| :--------: | :---: | :---: | :---: | :-----: | :---: |
| Vtxs[$i$ ] | $v_1$ | $v_2$ | $v_3$ | **...** | $v_n$ |

而图的邻接矩阵arcs\[$n$​][$n$]定义为：
$$
\text{arcs}[i][j]= 
	\begin{cases}1,\quad  & 
	  \text{如果}(v_i,v_j)/<v_i,v_j>\in E,\\ 
	  0, \quad  & \text{否则}.
	\end{cases}
$$

### 无向图的邻接矩阵表示法
<img src="https://img-blog.csdnimg.cn/20201025112835482.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =550x" alt="在这里插入图片描述" style="zoom:50%;" />
	特点1：无向图的邻接矩阵是对称的。
	特点2：顶点$v_i$的度是第$i$行（列）中1的个数。
	特别地，完全图的邻接矩阵对角线元素为0，其余为1。

### 有向图的邻接矩阵表示法
<img src="https://img-blog.csdnimg.cn/20201025115318630.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =550x" alt="在这里插入图片描述" style="zoom:50%;" />
在有向图的邻接矩阵中，
第$i$行的含义：以顶点$v_i$为尾的弧（即出度边）；
第$i$列的含义：以顶点$v_i$为头的弧（即入度边）。
特点1：有向图的邻接矩阵可能是不对称的。
特点2：顶点$v_i$的出度是第$i$行元素之和；顶点$v_i$的入度是第$i$列元素之和；所以顶点$v_i$的度=第$i$行元素之和 + 第$i$列元素之和。

### 网（即有权图）的邻接矩阵表示法
$$
	\text{arcs}[i][j]= 
	\begin{cases}w_{ij},\quad  & 
	  \text{如果}(v_i,v_j)/<v_i,v_j>\in E,\\ 
	  \infty, \quad  & \text{无边弧}.
	\end{cases} 
$$
<img src="https://img-blog.csdnimg.cn/20201025124422848.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =550x" alt="在这里插入图片描述" style="zoom:50%;" />

### 邻接矩阵表示法优缺点
优点：
* 直观、简单、好理解
* 方便检查任意一对顶点之间是否存在边
* 方便找任一顶点的所有邻接点（有边直接相连的顶点）
* 方便求得任一顶点的度

缺点：
* 不利于增加和删除节点
* 浪费空间，存稀疏图时有大量无效元素
* 统计稀疏图总边数时浪费时间

## 邻接表表示法（链表）
邻接表表示方法：
* **顶点**存储：按编号顺序将顶点数据存储在一维数组中
* **关联同一顶点的边**（以顶点为尾的弧）的存储：用线性链表存储
<img src="https://img-blog.csdnimg.cn/20201026204620875.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =550x" alt="在这里插入图片描述" style="zoom:50%;" />
### 无向图邻接表表示法
<img src="https://img-blog.csdnimg.cn/20201026205100440.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =550x" alt="在这里插入图片描述" style="zoom:50%;" />
特点：

* 邻接表**不唯一**
* 若无向图有$n$个节点，$e$条边，则其邻接表需要$n$个头节点和$2e$个表节点。适合存储稀疏图。
* 无向图中节点$v_i$的**度**为第$i$个存储节点关联边的**单链表的节点数**。
* 计算节点的度容易
### 有向图邻接表表示法
有向图邻接表的表示方法与无向图的表示方法类似，但只将以对应节点为尾的弧存储在单链表中。如下图示
<img src="https://img-blog.csdnimg.cn/20201026211415152.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =400x" alt="在这里插入图片描述" style="zoom:50%;" />
特点： 

* 若无向图有$n$个节点，$e$条边，则其邻接表需要$n$个头节点和$e$个表节点。
* 顶点$v_i$的**出度**为第$i$个单链表的节点数。
* 顶点$v_i$的**入度**为全部单链表中邻接点域值为$i-1$的节点的个数
* 找出度容易，找入度难

有向图邻接表的表示方法还可以用逆邻接表法，即单链表存储的是以对应节点为头的弧。
## 邻接矩阵和邻接表的关系
* 联系
	* 邻接表中每个链表对应邻接矩阵中的一行，链表中节点个数等于邻接矩阵一行中非零元素的个数。
* 区别
	* 对于任一确定的无向图，其邻接矩阵是唯一的（行列号和顶点编号一致）， 但邻接表不唯一（链接次序与顶点编号无关）。
	* 邻接矩阵空间复杂度为$\Omicron(n^2)$，邻接表空间复杂度为$\Omicron(n+e)$。
	* 用途：邻接矩阵多用于稠密图，邻接表多用于稀疏图。
## 十字链表
* 十字链表（Orthogonal List）是解决有向图的邻接表存储方式中求节点的度困难的问题，它是有向图的另一种链式存储结构，可以看成是有向图的邻接表和逆邻接表的结合。
* 有向图中每一条弧对应十字链表中一个**弧节点**，同时有向图中每一个顶点在十字链表中对应有一个**顶点节点**。
<img src="https://img-blog.csdnimg.cn/20201029222043364.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:50%;" />
## 邻接多重表
* 邻接多重表解决无向图邻接表存储方式中，每条边要存储两次的问题。
<img src="https://img-blog.csdnimg.cn/20201030131227788.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:50%;" />
# 图的遍历
## 定义
* 从给定的连通图中某一顶点除法，沿着一些边访遍图中所有顶点，且每个顶点仅被访问一次，就叫做图的遍历，它是图的**基本操作**。
* 遍历的实质：寻找每个顶点的邻接点的过程。
## 遍历可能存在的问题及解决思路
* 图中可能存在回路，且图的任一顶点都可能与其他顶点相通，访问完某个顶点后可能沿着某些边又回到曾经访问过的顶点。
* 解决思路：设置辅助数组visited[*n*]，用来标记被访问过的顶点
	* 初始状态，辅助数组visited中所有值为0。
	* 顶点*i*被访问，则将visited[*i*]设置为1，防止被多次访问。
## 深度优先搜索（Depth First Search, DFS）
遍历方法：
* 在访问图中某一起始点$v$后，由$v$出发，访问它的任一邻接点$w_1$；
* 再从$w_1$出发，访问与$w_1$邻接但还没被访问过的顶点$w_2$；
* 然后再从$w_2$出发，重复类似的访问过程，......，如此进行下去，直到所有邻接顶点都被访问过的顶点$u$为止。
* 接着，退回一步，退到前一次刚访问过的顶点，看其是否由未被访问过的邻接点：
	* 如果有，则访问此顶点，再由此顶点出发，进行与先前类似的访问过程。
	* 如果没有，则再回退一步进行搜索。重复上述过程，直到连通图中所有顶点都被访问过为止。
	<img src="https://img-blog.csdnimg.cn/20201031233559889.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:50%;" />

* 连通图的深度优先遍历的思想类似于树中先序遍历。
* 算法时间复杂度
	* 用邻接矩阵表示的图，遍历图中每一顶点都要完整扫描每一顶点所在的行，时间复杂度为$O(n^2)$。
	* 用邻接表表示的图，虽然有$2e$个表节点，但依靠辅助数组，只需扫描$e$个数组即可完成遍历，再加上访问$n$个头节点的时间，时间复杂度为$O(n+e)$。
* 空间复杂度：借用堆栈，$O(n)$。
## 广度优先搜索（Breadth First Search, BFS）
遍历方法：
* 从图的某一顶点$v_i$出发，首先依次访问该顶点的所有邻接点$v_{i_1},v_{i_2},...,v_{i_n}$，再按这些邻接点的被访问的先后次序访问与它们邻接的所有未被访问的顶点。
* 重复此过程，直到所有顶点都被访问为止。
<img src="https://img-blog.csdnimg.cn/20201031233721570.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom: 50%;" />
* 连通图的广度优先遍历的思想类似于树中的层次遍历。
* 算法时间复杂度：同DFS。
* 空间复杂度：借用队列，$O(n)$。
# 生成树
## 生成树的概念及特点
* 生成树：所有顶点都由边连在一起，但**不存在回路**的图。
* 一个图可以有许多棵不同的生成树。
<img src="https://img-blog.csdnimg.cn/20201104212850431.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =400x" alt="在这里插入图片描述" style="zoom:50%;" />
* 所有生成树均有以下特点：
	* 生成树的节点个数与图的顶点个数相同。
	* 生成树树的**极小连通子图**，去掉任一条边则不再连通。
	* **一个n个顶点的连通图的生成树有n-1条边**。
	* 在生成树中**再加一条边必形成回路**。
	* 生成树中任意两点间的路径**唯一**。
* 含n个顶点n-1条边的图不一定是生成树。
## 无向图的生成树的构建
设图$G=(V,E)$是一个连通图，当从图的任一顶点出发遍历$G$时，将边集$E(G)$分成两个集合$T(G)$和$B(G)$。其中，$T(G)$是遍历是经过的边的集合，$B(G)$是未经过的边的集合。显然$G_1=(V,T)$是$G$的极小连通子图，即$G_1$是$G$的生成树。
<img src="https://img-blog.csdnimg.cn/20201104222039726.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:50%;" />

## 最小生成树
定义：给定一个无向网络，在该网的所有生成树中，使得各边**所有权值之和最小**的生成树称为该网的最小生成树（Minimum Spanning Tree，MST），也叫最小代价生成树。
<img src="https://img-blog.csdnimg.cn/20201104222554750.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =500x" alt="在这里插入图片描述" style="zoom:50%;" />

### 最小生成树的性质
* 构造最小生成树的算法很多利用MST的性质。
* 设$N=(V,E)$是一个连通网，$U$是顶点集$V$的一个非空子集。设$u\in U,v\in V-U$若边$(u,v)$是一条具有最小权值的边，则必存在一棵包含$(u,v)$的最小生成树。
* 性质解释：在生成树的构造过程中，图中$n$个顶点分属两个不同的集合：
	* 已落在生成树上的顶点集：$U$
	* 尚未落在生成树上的顶点集：$V-U$
* 接下来应该在所有连通$U$中顶点和$V-U$中顶点的边中选取**权值最小的**边。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201105222830540.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =400x)
### 构造最小生成树——Prim算法
* 算法思想
	* 设$N=(V,E)$是一个连通网，$TE$是$N$上最小生成树中**边的集合**。
	* 初始令$U=\{u_0\}$，$u_0\in V$，$U=\{\}$。
	* 在所有$u\in U$，$v\in V-U$构成的边$(u，v)\in E$中，找出一条**代价（权值）最小**的边$(u_0,v_0)$。
	* 将$(u_0,v_0)$加入$TE$，并同时将$v_0$加入$U$。
	* 重复上两步骤，直至$U=V$，此时$T=(U,TE)$为$N$的最小生成树。
### 构造最小生成树——Kruskal算法
* 算法思想
	* 设$N=(V,E)$是一个连通网，令最小生成树为只有$n$个顶点而无边的非连通图$T=(V,\{\})$，且**每个顶点自成一个连通分量**。
	* 在$E$中选取代价最小的边，若该边依附的顶点落在$T$中不同的连通分量上（即**不能形成环**），则将此边加入$T$中；否则，舍弃此边，选取下一条代价最小的边。
	* 依次类推，直至$T$中所有顶点都在同一连通分量上为止。
### 两种算法比较
| 算法       | Prim算法               | Kruskal算法              |
| ---------- | ---------------------- | ------------------------ |
| 算法思想   | 选择点                 | 选择边                   |
| 时间复杂度 | $O(n^2)$ ($n$为顶点数) | $O(e\log e)$ ($e$为边数) |
| 适应范围   | 稠密图                 | 稀疏图                   |
# 最短路径问题

* 问题定义：在**有向网**中，A点（源点）到达B点（重点）的所有路径中，寻找一条**各边权值之和最小**的路径，即是最短路径问题。
* 特点：最短路径与最小生成树不同，路径上不一定包含$n$个顶点，也不一定包含$n-1$条边。
* **两类问题**
	* 第一类问题：两点间最短路径，使用**Dijkstra算法**。
	* 第二类问题：某源点到其他各点的最短路径，使用**Floyd算法**。
## Dijkstra最短路径算法
* 单源最短路径算法。
* 算法步骤：
	1. 初始化：初始时，令已检测的点集为$S=\varnothing$，图中其余未检测的点集为$T=\{v_i\},i=0...n-1$。定义一个距离辅助数组$D[n]$记录源点到其他各点的最短路径值，$D[1...n-1]$值为$\infty$，$D[0]=0$。
	2. 选择：$T$中选择出令$D[j]$最小的顶点$v_j$加入$S$，并将其从$T$中移去。
	3. 更新：遍历$v_j$在$T$中的所有邻接顶点：
		若在$T$中存在$v_j$的邻接点$v_k$，使得$weight(<v_j,v_k>)+D[j] < D[k]$，则用$weight(<v_j,v_k>)+D[j]$ 的值更新$D[k]$。
	4. 重复步骤2，3，直至$T=\varnothing, S=V$。
	5. 结束时，$D[i]$即为源点到$v_i$的最短路径值。

* 上述算法**只能计算到源点到各个顶点的最短路径距离，但不能得到该最短路径**。若要获得最短路径，则需要定义一个记录前驱顶点的辅助数组$predecessor$。在满足更新条件的时候，还要将被更新的顶点的前驱记录在数据中。例如，满足更新条件$weight(<v_j,v_k>)+D[j] < D[k]$的同时，记录被更新的$v_k$的前驱：$predecessor[k] = predecessor[j]$。取某个顶点的最短路径时，只需沿着该顶点往前寻找前驱，直到到达源点。
## Floyd最短路径算法
* 计算所有顶点间的最短路径，多源最短路径算法。
* 算法思想：逐个点试探，从$v_i$到$v_j$的所有可能存在的路径中，选出一条长度最短的路径。
* 算法步骤
	* 初始时设置一个$n$阶方阵，令其对角元素为0，若存在弧$<v_i,v_j>$，则方阵中对应$[i,j]$元素为权值，否则为$\infty$。
	* 逐步在原直接路径中增加中间节点，若加入中间节点后路径变短，则修改之；否则维持原值。所有顶点试探完毕，算法结束。
# 有向无环图及其应用
## 基本概念
* 有向无环图：无环的有向图，简称DAG（Directed Acycline Graph）图。
<img src="https://img-blog.csdnimg.cn/20201114231448938.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =400x" alt="在这里插入图片描述" style="zoom:50%;" />
* 有向无环图通常用来描述一个工程或者系统的进行过程。（通常把计划、施工、生产、程序流程等当成是一个工程。）
* 一个工程可以分成若干个子工程，只要完成了这些子工程，就可以导致整个工程的完成。
## AOV网
* 用一个有向图表示一个工程的各子工程及其相互制约的关系。其中以顶点表示活动，弧表示活动之间的优先制约关系，称这种有向图为顶点表示活动的网，简称AOV网（Activity On Vertex network）。
* 特点：
	* 若从$i$到$j$有一条有向路径，则$i$是$j$的前驱，$j$是$i$的后继。
	* 若$<i,j>$是网中有向边，则$i$是$j$的直接前驱，$j$是$i$的直接后继。
	* AOV网中，不允许存在回路，因为如果有回路存在，则表明某项活动以自身为先决条件，显然这是荒谬的。
* 问题：如何判断AOV网中是否存在回路？
### 拓扑排序
* 在AOV网没有回路的前提下，将全部活动排列称一个线性序列，使得若AOV网中有弧$<i,j>$存在，则在这个序列中，$i$一定排在$j$的前面，具有这种性质的线性序列称为**拓扑有序序列**，相应的拓扑有序排序的算法称为**拓扑排序**。
* 方法步骤：
	* 在有向图中选一个没有前驱的顶点且输出之。
	* 在图中删除该顶点和所有以它为尾的弧。
	* 重复上面两步，直至全部顶点均已输出；或者当图中不存在无前驱的顶点为止。
	<img src="https://img-blog.csdnimg.cn/20201116203936837.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =450x" alt="在这里插入图片描述" style="zoom:50%;" />
* 检测AOV网中是否存在环的方法：对有向图构造其顶点的拓扑有序序列，若网中所有顶点都在它的拓扑有序序列中，则该AOV网必定不存在环。

## AOE网
* 用一个有向图表示一个工程的各子工程及其相互制约的关系。其中以弧表示活动，顶点表示活动的开始或结束时间，称这种有向图为边表示活动的网，简称AOE网（Activity On Edge network）。
* 解决关键路径问题。
* 把工程计划表示为边表示活动的网络，用顶点表示时间，弧表示活动，弧的权值表示活动持续时间。
* 事件表示在它之前的活动已经结束，在它之后的活动可以开始。
<img src="https://img-blog.csdnimg.cn/20201117213901874.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzMjY1Nzk2,size_16,color_FFFFFF,t_70#pic_center =600x" alt="在这里插入图片描述" style="zoom:50%;" />

1⃣️算法:
* 在无序数组中找最大的K个数?
* 对无序数组`A[0:n-1]`进行预处理(不能改变`A[0:n-1]`内元素的顺序),使得能在O(1)时间内快速找到子数组`A[i:j]`的和?
* 在一个单向链表中实现快排?(快排效率以及内省排序)
* 讲解一下内省排序的原理?

* PageRank
* 两个数相乘,用什么数据结构(栈)
* hashmap源码(我没看).hashmap如何实现(广义链表).
* 找数组中加和为k的一组数.


* 几个基本排序算法的最好时间复杂度以及平均复杂度?