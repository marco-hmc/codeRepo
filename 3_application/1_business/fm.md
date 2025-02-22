## 3d底层重构项目讲解视频

### 1. 重构背景

目前zw3d，存在着一些亟待解决的关键问题。这些关键问题，并非由单一因素导致，而是多个模块综合作用的结果，是整个设计流程中的短板共同造成的，而有些短板的修改又会波及到非常多的模块适配工作。这就是 FM Feature Modeling（特征建模）项目提出的背景。而顺带的，一些其他的历史遗留问题可能也可以借由这个契机去修改。

具体关键问题：
* 重生成稳定性方面
    * 结果不可重复：在零件设计过程中，常常出现重生成稳定性不佳的情况。具体表现为，即便给定完全相同的输入条件，每次进行重生成操作时，所得到的结果却并不一致，也就是结果缺乏可重复性。
    * 和用户预期不符：哪怕只是对参数做出细微的调整，重生成后的结果都会出现很大的变化，这与用户原本的预期严重不符，极大地影响了零件设计工作的准确性和可靠性。

* 设计效率方面：
    * 对于有着较长历史的零件设计任务而言，其生成效率并非呈现出简单的线性退化趋势，而是有着复杂且难以预测的变化情况。
    * 涉及多实体的设计时，效率问题更加突出，并非按照常规理解的线性变化规律，而是会直接出现非常卡顿的现象。
    > 例如，在一个复杂的建模环境下，当添加一个新的 block（模块）时，理论上这个 block 作为新的实体，与前面已有的部分并无关联，按常理应该能够直接顺畅地绘制出来，但实际情况却是卡顿严重，严重拖慢了设计进度。


### 2. 重生成稳定性方面
- **关键因素**：重生成稳定性的关键在于永久命名。
- **不稳定原因**：由于永久命名存在随机性，呈现不稳定特性，使得后续特征引用上一次输出（命名）也不稳定，输入不固定，后续连带的输出也就不稳定了。
- **相关流程及命名结构问题**：
  - 命名的结构需要发生变化。
  - 每个特征完成后会产生一系列 topo 实体，旧框架依赖内核产生并命名实体。其命名结构作为整型数组，是内核拓扑变化追溯信息的压缩，但扩展性很差，且本身无法附带特征的语义信息。
  - 上层命名要做到稳定，要求特征本身能够携带一些特征能够识别的语义信息附着到命名上。
- **具体设计细节**：
  - 内核应该不可见命名，不应该知道上层怎么命名。因此内核需要暴露什么能力给到上层完成命名能力呢？简单来说就是追溯信息。
      - 实体的创建（create）、复制（copy）、分裂（split）、合并（merge）。
      - 例如，草图线画了一条线，拉伸出一个面，面是由线创建的，面的追踪信息就是线，希望面的命名能够体现这个线的信息。

### 3. 设计效率问题方面

#### 3.1 topoTable - Brep 相关

- **问题背景**：
  - topoTable 是 OverDrive 数据格式要求的运算数据，是实体建模信息，纯粹用于计算；Brep 是用于生成 3D 图纸、显示和拾取的数据。也就是说topoTable 和 Brep 之间存在一一对应关系。
  - 每次完成特征计算后，都需要进行 topoTable 到 Brep 的同步。

- **解决思路**：
  - 为了消除数据同步问题，最直接的思路是保留一份数据。Brep 数据是从 topoTable 数据派生而来的，因此一定会先有 topoTable 数据，再有 Brep 数据。而又不希望上层了解太多底层细节，因此只能保留topoTable数据，并提供一定的数据管理能力，体现在事务处理等方面。也就是说扩大 OverDrive 的能力，不仅用于计算几何，还要具备一定的数据管理和历史管理能力。

- **注意事项**
  - 提供一个监控机制，当 topoTable 底层数据变化时，能够影响到应用层。
  - OverDrive 需要保留可剥离出去、可单独商业化的能力。因此om/db数据和overdrive数据不能够完全合并。

#### 3.2 多实体相关

- **问题**：
  - 当新增一个实体时，需要与已存在的实体进行判断，查看是否存在影响。

- **解决思路**：
  - 数据分区设计（partition）。
  - 如果两个数据块有交互操作，拷贝数据完成操作，再拷贝回去，而不是建立引用的方式。


### 4. 模块职责调整

#### 4.1 内核期望

- 提供 trackingInfo：
    内核应提供追踪信息。
- 提供数据管理能力：
  - 数据分块：解决多个实体的问题。
  - 事务处理能力：支持事务处理，确保数据操作的完整性和一致性。

#### 4.2 OM 期望

- 支持 OverDrive 数据管理能力：
    能够管理和处理 OverDrive 数据。
- 支持 3D 未来的数据定义，兼容旧数据：
  - 保留定义：保留数据定义、CRUD 能力和基本数据类型定义。
  - 多种容器支持：OM 应支持多种数据容器。
- RTTI（运行时类型识别）：
- 观察者模式：
    支持观察者模式，实现数据变化的通知机制。
- 局部加载和数据分块：
    支持局部数据加载和数据分块管理。

#### 4.3 FMF（Feature Modeling Framework）期望
- 永久命名：
    支持永久命名机制。
- 特征语义附加：
    在特征创建和修改实体时，能够给实体附加特征自带的语义信息以及内核信息。
- 重生成优化：
    在重生成时，希望只清空 OverDrive 信息，但保留命名。

### 98. 未整理的实现细节
* vxcdbase
    * 几何拓扑信息
    * 上层应用属性信息
        * 颜色
        * 纹理
        * 永久命名
    * vxCdFace
    * OdBase?
        几何内核信息
    * faceRep?
        永久命名
        dataTracking
    * 重生成的时候在删除Odbase数据


### 99. quiz

#### 1. 怎么理解实体和特征？
实体是几何数据的表示，特征是对实体（几何数据）的操作（比如创建、修改、赋值、删除等）。
比如说在草图，画了一个封闭曲线。这个曲线是一个实体。
对封闭曲线，进行拉伸。这个拉伸是一种特征，创建了一个新的实体面。

#### 2. 重生成稳定性和永久命名的关系是什么？
```
    - **不稳定原因**：由于永久命名存在随机性，呈现不稳定特性，使得后续特征引用上一次输出（命名）也不稳定，输入不固定，后续连带的输出也就不稳定了。
```
这个理由不够自洽，不够完整。
永久命名有什么用？只是用于检索吗？

#### 3. 多实体部分？
需要再补充一下。