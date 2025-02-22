# 数据库和数据库管理系统（DBMS）

## 什么是数据库？

数据库是一个有组织的结构化信息或数据的集合，通常以电子方式存储在计算机系统中。数据库通常由数据库管理系统（DBMS）控制。数据和 DBMS 以及与它们相关的应用程序一起被称为数据库系统，通常简称为数据库。

## 什么是 DBMS？

数据库通常需要一个全面的数据库软件程序，称为数据库管理系统（DBMS）。DBMS 作为数据库与其终端用户或程序之间的接口，允许用户检索、更新和管理信息的组织和优化方式。DBMS 还促进对数据库的监督和控制，支持各种管理操作，如性能监控、调优和备份与恢复。

## 组件

以下是不同数据库中常见的一些组件：

### 模式

模式的作用是定义数据结构的形状，并指定哪些类型的数据可以放在哪里。模式可以在整个数据库中严格执行，也可以在部分数据库中松散执行，或者根本不存在。

### 表

每个表包含各种列，就像电子表格一样。表可以只有两列，也可以有多达一百列或更多列，具体取决于表中存放的信息类型。

### 列

列包含特定类型的数据值集合，每行一个值。列可以包含文本值、数字、枚举、时间戳等。

### 行

表中的数据以行记录。表中可以有成千上万甚至数百万行记录特定信息。

## 类型

![数据库类型](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/databases-and-dbms/database-types.png)

以下是不同类型的数据库：

- **[SQL](https://karanpratapsingh.com/courses/system-design/sql-databases)**
- **[NoSQL](https://karanpratapsingh.com/courses/system-design/nosql-databases)**
  - 文档型
  - 键值型
  - 图形型
  - 时间序列型
  - 宽列型
  - 多模型

SQL 和 NoSQL 数据库是广泛的话题，将在 [SQL 数据库](https://karanpratapsingh.com/courses/system-design/sql-databases) 和 [NoSQL 数据库](https://karanpratapsingh.com/courses/system-design/nosql-databases) 中分别讨论。了解它们之间的比较，请参见 [SQL vs NoSQL 数据库](https://karanpratapsingh.com/courses/system-design/sql-vs-nosql-databases)。

## 挑战

在大规模运行数据库时面临的一些常见挑战：

- **吸收显著增加的数据量**：来自传感器、连接设备和其他来源的数据爆炸性增长。
- **确保数据安全**：如今数据泄露无处不在，确保数据安全但也易于用户访问比以往任何时候都更重要。
- **跟上需求**：公司需要实时访问数据以支持及时决策并抓住新机会。
- **管理和维护数据库和基础设施**：随着数据库变得越来越复杂，数据量不断增长，公司面临着雇佣额外人才来管理数据库的费用。
- **消除扩展限制**：如果企业要生存，就需要增长，其数据管理也必须随之增长。但很难预测公司需要多少容量，特别是对于本地数据库。
- **确保数据驻留、数据主权或延迟要求**：某些组织有更适合在本地运行的用例。在这些情况下，预配置和预优化的工程系统是理想的选择。

# SQL 数据库

SQL（或关系型）数据库是具有预定义关系的数据项集合。这些项被组织为具有列和行的表。表用于保存要在数据库中表示的对象的信息。表中的每一列保存某种类型的数据，字段存储属性的实际值。表中的行表示一个对象或实体的相关值集合。

表中的每一行可以用一个称为主键的唯一标识符标记，多个表之间的行可以使用外键关联。这些数据可以通过多种方式访问，而无需重新组织数据库表。SQL 数据库通常遵循 [ACID 一致性模型](https://karanpratapsingh.com/courses/system-design/acid-and-base-consistency-models#acid)。

## 物化视图

物化视图是从查询规范派生并存储以供以后使用的预计算数据集。由于数据是预计算的，查询物化视图比执行对视图基表的查询更快。当查询频繁运行或足够复杂时，这种性能差异可能非常显著。

它还支持数据子集化，并提高在大数据集上运行的复杂查询的性能，从而减少网络负载。物化视图还有其他用途，但它们主要用于性能和复制。

## N+1 查询问题

N+1 查询问题发生在数据访问层执行 N 个额外的 SQL 语句以获取可以通过执行主 SQL 查询检索到的相同数据时。N 的值越大，执行的查询越多，性能影响越大。

这在 GraphQL 和 ORM（对象关系映射）工具中很常见，可以通过优化 SQL 查询或使用批量连续请求并在底层进行单次数据请求的数据加载器来解决。

## 优点

让我们看看使用关系数据库的一些优点：

- 简单且准确
- 可访问性
- 数据一致性
- 灵活性

## 缺点

以下是关系数据库的缺点：

- 维护成本高
- 模式演变困难
- 性能影响（连接、反规范化等）
- 由于水平扩展性差，难以扩展

## 示例

以下是一些常用的关系数据库：

- [PostgreSQL](https://www.postgresql.org)
- [MySQL](https://www.mysql.com)
- [MariaDB](https://mariadb.org)
- [Amazon Aurora](https://aws.amazon.com/rds/aurora)

# NoSQL 数据库

NoSQL 是一个广泛的类别，包括任何不使用 SQL 作为主要数据访问语言的数据库。这些类型的数据库有时也被称为非关系型数据库。与关系数据库不同，NoSQL 数据库中的数据不必符合预定义的模式。NoSQL 数据库遵循 [BASE 一致性模型](https://karanpratapsingh.com/courses/system-design/acid-and-base-consistency-models#base)。

以下是不同类型的 NoSQL 数据库：

### 文档型

文档数据库（也称为文档导向数据库或文档存储）是一种以文档形式存储信息的数据库。它们是通用数据库，服务于各种事务性和分析性应用。

**优点**

- 直观且灵活
- 易于水平扩展
- 无模式

**缺点**

- 无模式
- 非关系型

**示例**

- [MongoDB](https://www.mongodb.com)
- [Amazon DocumentDB](https://aws.amazon.com/documentdb)
- [CouchDB](https://couchdb.apache.org)

### 键值型

键值数据库是最简单的 NoSQL 数据库类型之一，以键值对的形式保存数据，每对由两个数据项组成。它们有时也被称为键值存储。

**优点**

- 简单且高效
- 高度可扩展，适用于高流量
- 会话管理
- 优化查找

**缺点**

- 基本的 CRUD 操作
- 无法过滤值
- 缺乏索引和扫描功能
- 不适合复杂查询

**示例**

- [Redis](https://redis.io)
- [Memcached](https://memcached.org)
- [Amazon DynamoDB](https://aws.amazon.com/dynamodb)
- [Aerospike](https://aerospike.com)

### 图形型

图形数据库是一种 NoSQL 数据库，使用图结构进行语义查询，使用节点、边和属性来表示和存储数据，而不是表或文档。

图形数据库将存储中的数据项与节点和边的集合相关联，边表示节点之间的关系。这些关系允许存储中的数据直接链接在一起，并且在许多情况下可以通过一次操作检索。

**优点**

- 查询速度快
- 敏捷且灵活
- 明确的数据表示

**缺点**

- 复杂
- 没有标准化的查询语言

**用例**

- 欺诈检测
- 推荐引擎
- 社交网络
- 网络映射

**示例**

- [Neo4j](https://neo4j.com)
- [ArangoDB](https://www.arangodb.com)
- [Amazon Neptune](https://aws.amazon.com/neptune)
- [JanusGraph](https://janusgraph.org)

### 时间序列型

时间序列数据库是一种针对时间戳或时间序列数据进行优化的数据库。

**优点**

- 快速插入和检索
- 高效的数据存储

**用例**

- 物联网数据
- 指标分析
- 应用监控
- 理解金融趋势

**示例**

- [InfluxDB](https://www.influxdata.com)
- [Apache Druid](https://druid.apache.org)

### 宽列型

宽列数据库，也称为宽列存储，是无模式的。数据存储在列族中，而不是行和列中。

**优点**

- 高度可扩展，可以处理 PB 级数据
- 适用于实时大数据应用

**缺点**

- 昂贵
- 写入时间增加

**用例**

- 商业分析
- 基于属性的数据存储

**示例**

- [BigTable](https://cloud.google.com/bigtable)
- [Apache Cassandra](https://cassandra.apache.org)
- [ScyllaDB](https://www.scylladb.com)

### 多模型

多模型数据库将不同的数据库模型（如关系型、图形、键值、文档等）结合到一个单一的集成后端中。这意味着它们可以容纳各种数据类型、索引、查询，并以多种模型存储数据。

**优点**

- 灵活性
- 适用于复杂项目
- 数据一致

**缺点**

- 复杂
- 不够成熟

**示例**

- [ArangoDB](https://www.arangodb.com)
- [Azure Cosmos DB](https://azure.microsoft.com/en-in/services/cosmos-db)
- [Couchbase](https://www.couchbase.com)

# SQL vs NoSQL 数据库

在数据库的世界中，有两种主要类型的解决方案：SQL（关系型）和 NoSQL（非关系型）数据库。它们在构建方式、存储的信息类型以及存储方式上有所不同。关系数据库是结构化的，具有预定义的模式，而非关系数据库是非结构化的、分布式的，具有动态模式。

## 高层次的区别

以下是 SQL 和 NoSQL 之间的一些高层次区别：

### 存储

SQL 将数据存储在表中，每行代表一个实体，每列代表该实体的一个数据点。

NoSQL 数据库有不同的数据存储模型，如键值、图形、文档等。

### 模式

在 SQL 中，每条记录符合固定的模式，这意味着在数据输入之前必须决定和选择列，并且每行必须有每列的数据。模式可以稍后更改，但需要通过迁移修改数据库。

而在 NoSQL 中，模式是动态的。可以随时添加字段，并且每个记录（或等效物）不必包含每个字段的数据。

### 查询

SQL 数据库使用 SQL（结构化查询语言）来定义和操作数据，非常强大。

在 NoSQL 数据库中，查询集中在文档集合上。不同的数据库有不同的查询语法。

### 可扩展性

在大多数常见情况下，SQL 数据库是垂直可扩展的，这可能非常昂贵。可以将关系数据库扩展到多个服务器，但这是一个具有挑战性且耗时的过程。

另一方面，NoSQL 数据库是水平可扩展的，这意味着我们可以轻松地向 NoSQL 数据库基础设施中添加更多服务器以处理大量流量。任何廉价的商品硬件或云实例都可以托管 NoSQL 数据库，因此比垂直扩展更具成本效益。许多 NoSQL 技术还会自动将数据分布到服务器上。

### 可靠性

绝大多数关系数据库符合 ACID 标准。因此，当涉及数据可靠性和执行事务的安全保证时，SQL 数据库仍然是更好的选择。

大多数 NoSQL 解决方案为了性能和可扩展性而牺牲了 ACID 合规性。

## 原因

我们应该始终选择更符合需求的技术。让我们看看选择 SQL 或 NoSQL 数据库的一些原因：

**选择 SQL 的原因**

- 结构化数据，具有严格的模式
- 关系数据
- 需要复杂的连接
- 事务
- 按索引查找非常快

**选择 NoSQL 的原因**

- 动态或灵活的模式
- 非关系数据
- 不需要复杂的连接
- 非常数据密集的工作负载
- 非常高的 IOPS 吞吐量

# 数据库复制

复制是一个涉及共享信息以确保冗余资源（如多个数据库）之间一致性的过程，以提高可靠性、容错性或可访问性。

## 主从复制

主服务器处理读写操作，将写操作复制到一个或多个从服务器，从服务器仅处理读操作。从服务器还可以以树状结构复制其他从服务器。如果主服务器离线，系统可以继续以只读模式运行，直到从服务器提升为主服务器或配置新的主服务器。

![主从复制](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/database-replication/master-slave-replication.png)

### 优点

- 对整个数据库进行备份，对主服务器几乎没有影响。
- 应用程序可以从从服务器读取，而不会影响主服务器。
- 从服务器可以离线并同步回主服务器，而不会有任何停机时间。

### 缺点

- 复制增加了更多的硬件和额外的复杂性。
- 主服务器故障时的停机时间和可能的数据丢失。
- 在主从架构中，所有写操作也必须在主服务器上进行。
- 读从服务器越多，我们需要复制的越多，这将增加复制延迟。

## 主主复制

两个主服务器都处理读写操作，并相互协调。如果其中一个主服务器宕机，系统可以继续处理读写操作。

![主主复制](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/database-replication/master-master-replication.png)

### 优点

- 应用程序可以从两个主服务器读取。
- 将写负载分布在两个主节点上。
- 简单、自动和快速的故障切换。

### 缺点

- 配置和部署不如主从简单。
- 要么松散一致，要么由于同步而增加写延迟。
- 随着写节点的增加和延迟的增加，冲突解决变得更加重要。

## 同步 vs 异步复制

同步复制和异步复制的主要区别在于数据写入副本的方式。在同步复制中，数据同时写入主存储和副本。因此，主副本和副本应该始终保持同步。

相比之下，异步复制在数据已经写入主存储后将数据复制到副本。尽管复制过程可能接近实时发生，但更常见的是复制按计划进行，并且更具成本效益。

# 索引

当涉及数据库时，索引是众所周知的，它们用于提高数据存储上的数据检索操作的速度。索引通过增加存储开销和减慢写入速度（因为我们不仅要写入数据，还要更新索引）来换取更快的读取速度。索引用于快速定位数据，而无需检查数据库表中的每一行。索引可以使用数据库表的一列或多列创建，为快速随机查找和有序记录的高效访问提供基础。

![索引](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/indexes/indexes.png)

索引是一种数据结构，可以看作是指向实际数据位置的目录。因此，当我们在表的一列上创建索引时，我们在索引中存储该列和指向整行的指针。索引还用于创建相同数据的不同视图。对于大数据集，这是指定不同过滤器或排序方案的绝佳方式，而无需创建多个数据副本。

数据库索引的一个特性是它们可以是**密集**的或**稀疏**的。每种索引类型都有其自身的权衡。让我们看看每种索引类型的工作原理：

## 密集索引

在密集索引中，为表的每一行创建一个索引记录。记录可以直接定位，因为索引的每条记录都包含搜索键值和指向实际记录的指针。

![密集索引](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/indexes/dense-index.png)

密集索引在写入时比稀疏索引需要更多的维护。由于每行必须有一个条目，数据库必须在插入、更新和删除时维护索引。每行都有一个条目也意味着密集索引需要更多的内存。密集索引的好处是可以通过二分搜索快速找到值。密集索引也不对数据施加任何排序要求。

## 稀疏索引

在稀疏索引中，仅为部分记录创建索引记录。

![稀疏索引](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/indexes/sparse-index.png)

稀疏索引在写入时比密集索引需要更少的维护，因为它们只包含值的子集。这种较轻的维护负担意味着插入、更新和删除会更快

稀疏索引在写入时比密集索引需要更少的维护，因为它们只包含值的一个子集。这种较轻的维护负担意味着插入、更新和删除操作会更快。较少的条目也意味着索引将使用更少的内存。由于通常在二分搜索之后需要跨页面扫描，因此查找数据的速度较慢。当处理有序数据时，稀疏索引也是可选的。


# 规范化和反规范化

## 术语

在进一步讨论之前，让我们看看规范化和反规范化中一些常用的术语。

### 键

**主键**：可以用来唯一标识表中每一行的列或列组。

**复合键**：由多个列组成的主键。

**超键**：能够唯一标识表中所有行的所有键的集合。

**候选键**：在表中唯一标识行的属性。

**外键**：引用另一个表的主键。

**备用键**：不是主键的键称为备用键。

**代理键**：当没有其他列能够满足主键属性时，系统生成的唯一标识表中每个条目的值。

### 依赖关系

**部分依赖**：当主键决定其他一些属性时发生。

**函数依赖**：在表中，通常是主键和非键属性之间存在的关系。

**传递函数依赖**：当某些非键属性决定其他属性时发生。

### 异常

数据库异常是由于不正确的规划或将所有内容存储在一个平面数据库中而导致的数据库缺陷。通常通过规范化过程来解决这些问题。

有三种类型的数据库异常：

**插入异常**：当我们无法在没有其他属性的情况下插入某些属性时发生。

**更新异常**：在数据冗余和部分更新的情况下发生。换句话说，正确更新数据库需要其他操作，如添加、删除或两者兼有。

**删除异常**：当删除某些数据需要删除其他数据时发生。

**示例**

让我们考虑以下未规范化的表：

| ID  | 名字   | 角色              | 团队 |
| --- | ------ | ----------------- | ---- |
| 1   | 彼得  | 软件工程师         | A    |
| 2   | 布莱恩 | DevOps 工程师      | B    |
| 3   | 海莉  | 产品经理           | C    |
| 4   | 海莉  | 产品经理           | C    |
| 5   | 史蒂夫 | 前端工程师         | D    |

假设我们雇佣了一个新员工“约翰”，但他可能不会立即被分配到团队。这将导致插入异常，因为团队属性尚不存在。

接下来，假设来自团队 C 的海莉被提升了，为了在数据库中反映这一变化，我们需要更新两行以保持一致性，这可能导致更新异常。

最后，我们想要删除团队 B，但要做到这一点，我们还需要删除其他信息，如名字和角色，这是删除异常的一个例子。

## 规范化

规范化是组织数据库中数据的过程。这包括创建表并根据设计规则在这些表之间建立关系，以保护数据并通过消除冗余和不一致的依赖关系使数据库更加灵活。

### 为什么需要规范化？

规范化的目标是消除冗余数据并确保数据一致性。一个完全规范化的数据库允许其结构扩展以容纳新类型的数据，而无需过多更改现有结构。因此，与数据库交互的应用程序受到的影响最小。

### 规范形式

规范形式是一系列确保数据库规范化的指南。让我们讨论一些基本的规范形式：

**第一范式 (1NF)**

一个表要满足第一范式 (1NF)，应遵循以下规则：

- 不允许重复组。
- 使用主键标识每组相关数据。
- 相关数据集应有一个单独的表。
- 不允许在同一列中混合数据类型。

**第二范式 (2NF)**

一个表要满足第二范式 (2NF)，应遵循以下规则：

- 满足第一范式 (1NF)。
- 不应有任何部分依赖。

**第三范式 (3NF)**

一个表要满足第三范式 (3NF)，应遵循以下规则：

- 满足第二范式 (2NF)。
- 不允许传递函数依赖。

**BCNF**

Boyce-Codd 规范形式 (BCNF) 是第三范式 (3NF) 的稍强版本，用于解决 3NF 原始定义未处理的某些类型的异常。有时也称为 3.5 范式 (3.5NF)。

一个表要满足 Boyce-Codd 规范形式 (BCNF)，应遵循以下规则：

- 满足第三范式 (3NF)。
- 对于每个函数依赖 X → Y，X 应该是超键。

_还有更多的规范形式，如 4NF、5NF 和 6NF，但我们在这里不讨论它们。请查看这个 [精彩视频](https://www.youtube.com/watch?v=GFQaEYEc8_8)，了解详细信息。_

在关系数据库中，如果一个关系满足第三范式，通常被描述为“规范化”。大多数 3NF 关系都没有插入、更新和删除异常。

与许多正式规则和规范一样，现实世界的场景并不总是允许完全遵守。如果你决定违反前三条规范化规则之一，请确保你的应用程序预见到可能发生的任何问题，如数据冗余和不一致的依赖关系。

### 优点

以下是规范化的一些优点：

- 减少数据冗余。
- 更好的数据设计。
- 增加数据一致性。
- 强制执行参照完整性。

### 缺点

让我们看看规范化的一些缺点：

- 数据设计复杂。
- 性能较慢。
- 维护开销。
- 需要更多的连接。

## 反规范化

反规范化是一种数据库优化技术，我们在一个或多个表中添加冗余数据。这可以帮助我们避免在关系数据库中进行昂贵的连接。它试图在牺牲一些写性能的情况下提高读取性能。为了避免昂贵的连接，冗余数据的副本被写入多个表中。

一旦数据通过分片和分区等技术分布，跨网络管理连接会进一步增加复杂性。反规范化可能会避免这种复杂连接的需求。

_注意：反规范化并不意味着逆转规范化。_

### 优点

让我们看看反规范化的一些优点：

- 检索数据更快。
- 编写查询更容易。
- 减少表的数量。
- 方便管理。

### 缺点

以下是反规范化的一些缺点：

- 插入和更新昂贵。
- 增加数据库设计的复杂性。
- 增加数据冗余。
- 数据不一致的可能性更大。

# ACID 和 BASE 一致性模型

让我们讨论 ACID 和 BASE 一致性模型。

## ACID

ACID 代表原子性、一致性、隔离性和持久性。ACID 属性用于在事务处理期间维护数据完整性。

为了在事务前后保持一致性，关系数据库遵循 ACID 属性。让我们理解这些术语：

### 原子性

事务中的所有操作成功或所有操作回滚。

### 一致性

事务完成后，数据库结构完整。

### 隔离性

事务之间不相互竞争。数据库通过调节数据的竞争访问，使事务看起来是顺序运行的。

### 持久性

一旦事务完成，写入和更新被写入磁盘，即使发生系统故障，它们也会保留在系统中。

## BASE

随着数据量的增加和高可用性要求，数据库设计的方法也发生了巨大变化。为了提高可扩展性并同时保持高可用性，我们将逻辑从数据库移到单独的服务器上。这样，数据库变得更加独立，专注于实际的数据存储过程。

在 NoSQL 数据库世界中，ACID 事务较少见，因为一些数据库放宽了对即时一致性、数据新鲜度和准确性的要求，以获得其他好处，如可扩展性和弹性。

BASE 属性比 ACID 保证要宽松得多，但两者之间没有一一对应的映射。让我们理解这些术语：

### 基本可用性

数据库大部分时间看起来都在工作。

### 软状态

存储不必是写一致的，不同副本也不必一直相互一致。

### 最终一致性

数据可能不会立即一致，但最终会变得一致。即使系统中的读取可能不会立即给出正确的响应，但它们仍然是可能的。

## ACID vs BASE 权衡

我们的应用程序是否需要 ACID 或 BASE 一致性模型没有正确答案。这两种模型都是为了满足不同的需求而设计的。在选择数据库时，我们需要牢记两种模型的属性和应用程序的需求。

鉴于 BASE 的宽松一致性，如果选择 BASE 存储，开发人员需要对一致数据更加了解和严格。熟悉所选数据库的 BASE 行为并在这些约束内工作是至关重要的。

另一方面，与 ACID 事务的简单性相比，围绕 BASE 限制进行规划有时可能是一个主要缺点。对于数据可靠性和一致性至关重要的用例，完全 ACID 数据库是完美的选择。

# CAP 定理

CAP 定理指出，分布式系统只能提供一致性、可用性和分区容忍性（CAP）中的两个特性。

![cap-theorem](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/cap-theorem/cap-theorem.png)

让我们详细看看 CAP 定理所指的三个分布式系统特性。

### 一致性

一致性意味着所有客户端在同一时间看到相同的数据，无论它们连接到哪个节点。为了实现这一点，每当数据写入一个节点时，必须立即转发或复制到系统中的所有节点，然后写操作才被视为“成功”。

### 可用性

可用性意味着任何请求数据的客户端都会得到响应，即使一个或多个节点宕机。

### 分区容忍性

分区容忍性意味着系统在消息丢失或部分故障的情况下继续工作。一个分区容忍的系统可以承受任何不导致整个网络故障的网络故障。数据在节点和网络的组合中充分复制，以便在间歇性中断期间保持系统运行。

## 一致性-可用性权衡

我们生活在一个物理世界中，无法保证网络的稳定性，因此分布式数据库必须选择分区容忍性 (P)。这意味着在一致性 (C) 和可用性 (A) 之间进行权衡。

### CA 数据库

CA 数据库在所有节点上提供一致性和可用性。如果系统中任何两个节点之间存在分区，它就无法做到这一点，因此无法提供容错。

**示例**：[PostgreSQL](https://www.postgresql.org)、[MariaDB](https://mariadb.org)。

### CP 数据库

CP 数据库在牺牲可用性的情况下提供一致性和分区容忍性。当任何两个节点之间发生分区时，系统必须关闭不一致的节点，直到分区解决。

**示例**：[MongoDB](https://www.mongodb.com)、[Apache HBase](https://hbase.apache.org)。

### AP 数据库

AP 数据库在牺牲一致性的情况下提供可用性和分区容忍性。当发生分区时，所有节点仍然可用，但位于分区错误一端的节点可能会返回比其他节点更旧版本的数据。当分区解决后，AP 数据库通常会重新同步节点以修复系统中的所有不一致。

**示例**：[Apache Cassandra](https://cassandra.apache.org)，[CouchDB](https://couchdb.apache.org)。

# PACELC 定理

PACELC 定理是 CAP 定理的扩展。CAP 定理指出，在分布式系统中发生网络分区 (P) 的情况下，必须在可用性 (A) 和一致性 (C) 之间做出选择。

PACELC 通过引入延迟 (L) 作为分布式系统的一个附加属性扩展了 CAP 定理。该定理指出，即使在系统正常运行且没有分区的情况下 (E)，也必须在延迟 (L) 和一致性 (C) 之间做出选择。

_PACELC 定理最早由 [Daniel J. Abadi](https://scholar.google.com/citations?user=zxeEF2gAAAAJ) 描述。_

![pacelc-theorem](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/pacelc-theorem/pacelc-theorem.png)

PACELC 定理的提出是为了应对 CAP 定理的一个关键限制，因为 CAP 定理没有考虑性能或延迟。

例如，根据 CAP 定理，如果查询在 30 天后返回响应，数据库可以被认为是可用的。显然，这样的延迟对于任何现实世界的应用程序都是不可接受的。

# 事务

事务是一系列被视为_“单一工作单元”_的数据库操作。事务中的操作要么全部成功，要么全部失败。通过这种方式，事务的概念在系统的一部分发生故障时支持数据完整性。并非所有数据库都选择支持 ACID 事务，通常是因为它们优先考虑其他难以或理论上不可能一起实现的优化。

_通常，关系数据库支持 ACID 事务，而非关系数据库则不支持（有例外情况）。_

## 状态

数据库中的事务可以处于以下状态之一：

![transaction-states](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/transactions/transaction-states.png)

### 活动

在此状态下，事务正在执行。这是每个事务的初始状态。

### 部分提交

当事务执行其最后一个操作时，称其处于部分提交状态。

### 提交

如果事务成功执行了所有操作，则称其为提交状态。其所有影响现在都永久地建立在数据库系统上。

### 失败

如果数据库恢复系统进行的任何检查失败，则称事务处于失败状态。失败的事务不能再继续进行。

### 中止

如果任何检查失败且事务已达到失败状态，则恢复管理器会回滚数据库上的所有写操作，将数据库恢复到事务执行前的原始状态。处于此状态的事务被中止。

事务中止后，数据库恢复模块可以选择以下两种操作之一：

- 重新启动事务
- 终止事务

### 终止

如果没有回滚或事务来自_提交状态_，则系统一致并准备好进行新事务，旧事务被终止。

# 分布式事务

分布式事务是一组在两个或多个数据库上执行的数据操作。它通常在通过网络连接的独立节点之间协调，但也可能跨越单个服务器上的多个数据库。

## 为什么需要分布式事务？

与单个数据库上的 ACID 事务不同，分布式事务涉及更改多个数据库上的数据。因此，分布式事务处理更加复杂，因为数据库必须协调事务中更改的提交或回滚，作为一个自包含的单元。

换句话说，所有节点必须提交，或者所有节点必须中止并回滚整个事务。这就是为什么我们需要分布式事务。

现在，让我们看看一些流行的分布式事务解决方案：

## 两阶段提交

![two-phase-commit](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/distributed-transactions/two-phase-commit.png)

两阶段提交 (2PC) 协议是一种分布式算法，用于协调参与分布式事务的所有进程是否提交或中止（回滚）事务。

该协议在许多临时系统故障情况下实现了其目标，因此被广泛使用。然而，它并不能抵御所有可能的故障配置，在极少数情况下需要手动干预以纠正结果。

该协议需要一个协调节点，基本上协调和监督不同节点之间的事务。协调器尝试在两个阶段中建立进程集之间的共识，因此得名。

### 阶段

两阶段提交包括以下阶段：

**准备阶段**

准备阶段涉及协调节点从每个参与节点收集共识。除非每个节点都响应_准备好_，否则事务将被中止。

**提交阶段**

如果所有参与者都向协调器响应_准备好_，则协调器要求所有节点提交事务。如果发生故障，事务将被回滚。

### 问题

两阶段提交协议可能出现以下问题：

- 如果其中一个节点崩溃怎么办？
- 如果协调器本身崩溃怎么办？
- 它是一个阻塞协议。

## 三阶段提交

![three-phase-commit](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/distributed-transactions/three-phase-commit.png)

三阶段提交 (3PC) 是两阶段提交的扩展，其中提交阶段分为两个阶段。这有助于解决两阶段提交协议中出现的阻塞问题。

### 阶段

三阶段提交包括以下阶段：

**准备阶段**

此阶段与两阶段提交相同。

**预提交阶段**

协调器发出预提交消息，所有参与节点必须确认。如果参与者未能及时收到此消息，则事务将被中止。

**提交阶段**

此步骤也类似于两阶段提交协议。

### 预提交阶段为何有用？

预提交阶段实现了以下目标：

- 如果在此阶段找到参与节点，则意味着_每个_参与者都已完成第一阶段。准备阶段的完成得到保证。
- 现在每个阶段都可以超时，避免无限期等待。

## Sagas

![sagas](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/distributed-transactions/sagas.png)

Saga 是一系列本地事务。每个本地事务更新数据库并发布消息或事件以触发 Saga 中的下一个本地事务。如果本地事务因违反业务规则而失败，则 Saga 执行一系列补偿事务，撤销前面本地事务所做的更改。

### 协调

有两种常见的实现方法：

- **编排**：每个本地事务发布域事件，触发其他服务中的本地事务。
- **协调**：协调者告诉参与者要执行哪些本地事务。

### 问题

- Saga 模式特别难以调试。
- 存在 Saga 参与者之间循环依赖的风险。
- 缺乏参与者数据隔离带来了持久性挑战。
- 测试困难，因为所有服务必须运行以模拟事务。

# 分片

在讨论分片之前，让我们谈谈数据分区：

## 数据分区

数据分区是一种将数据库拆分成许多更小部分的技术。它是将数据库或表拆分到多个机器上的过程，以提高数据库的可管理性、性能和可用性。

### 方法

有许多不同的方法可以用来决定如何将应用程序数据库拆分成多个更小的数据库。以下是一些大型应用程序使用的最流行的方法：

**水平分区（或分片）**

在这种策略中，我们根据_分区键_定义的值范围水平拆分表数据。这也称为**_数据库分片_**。

**垂直分区**

在垂直分区中，我们根据列垂直分区数据。我们将表拆分成相对较小的表，每个部分存在于单独的分区中。

在本教程中，我们将特别关注分片。

## 什么是分片？

分片是一种与_水平分区_相关的数据库架构模式，它将一个表的行分离到多个不同的表中，称为_分区_或_分片_。每个分区具有相同的模式和列，但也包含共享数据的子集。同样，每个分区中的数据是唯一的，与其他分区中的数据独立。

![sharding](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/sharding/sharding.png)

数据分片的理由是，在某个点之后，水平扩展通过添加更多机器比通过添加强大的服务器进行垂直扩展更便宜和更可行。分片可以在应用程序级别或数据库级别实现。

## 分区标准

有许多可用于数据分区的标准。以下是一些最常用的标准：

### 基于哈希

这种策略基于哈希算法将行划分到不同的分区中，而不是基于连续索引对数据库行进行分组。

这种方法的缺点是动态添加/删除数据库服务器变得昂贵。

### 基于列表

在基于列表的分区中，每个分区是根据列上的值列表定义和选择的，而不是一组连续的值范围。

### 基于范围

范围分区根据分区键的值范围将数据映射到各个分区。换句话说，我们以每个分区包含给定范围内的行的方式对表进行分区。

范围应是连续的但不重叠，每个范围为分区指定一个非包含的下限和上限。任何等于或高于范围上限的分区键值都将添加到下一个分区。

### 复合

顾名思义，复合分区基于两种或多种分区技术对数据进行分区。在这里，我们首先使用一种技术对数据进行分区，然后每个分区进一步细分为子分区，使用相同或其他方法。

## 优点

但为什么我们需要分片？以下是一些优点：

- **可用性**：为分区数据库提供逻辑独立性，确保应用程序的高可用性。这里各个分区可以独立管理。
- **可扩展性**：通过将数据分布到多个分区来提高可扩展性。
- **安全性**：通过将敏感和非敏感数据存储在不同的分区中，有助于提高系统的安全性。这可以为敏感数据提供更好的可管理性和安全性。
- **查询性能**：提高系统性能。系统不再需要查询整个数据库，而只需查询较小的分区。
- **数据可管理性**：将表和索引划分为更小、更易管理的单元。

## 缺点

- **复杂性**：分片增加了系统的整体复杂性。
- **跨分片连接**：一旦数据库被分区并分布到多台机器上，通常无法执行跨多个数据库分片的连接。这样的连接不会高效，因为数据必须从多个服务器检索。
- **重新平衡**：如果数据分布不均匀或单个分片负载过大，在这种情况下，我们必须重新平衡分片，以便请求尽可能均匀地分布在分片之间。

## 何时使用分片？

以下是一些分片可能是正确选择的原因：

- 利用现有硬件而不是高端机器。
- 在不同地理区域维护数据。
- 通过添加更多分片快速扩展。
- 更好的性能，因为每台机器的负载较小。
- 当需要更多并发连接时。


# 一致性哈希

首先让我们了解我们要解决的问题。

## 为什么我们需要这个？

在传统的基于哈希的分布方法中，我们使用哈希函数来哈希我们的分区键（例如请求 ID 或 IP）。然后，如果我们对节点总数（服务器或数据库）取模，这将给我们要路由请求的节点。

!simple-hashing

$$
\begin{align*}
& Hash(key_1) \to H_1 \bmod N = Node_0 \\
& Hash(key_2) \to H_2 \bmod N = Node_1 \\
& Hash(key_3) \to H_3 \bmod N = Node_2 \\
& ... \\
& Hash(key_n) \to H_n \bmod N = Node_{n-1}
\end{align*}
$$

其中，

`key`：请求 ID 或 IP。

`H`：哈希函数结果。

`N`：节点总数。

`Node`：请求将被路由到的节点。

问题在于，如果我们添加或删除一个节点，将导致 `N` 发生变化，这意味着我们的映射策略将失效，因为相同的请求现在将映射到不同的服务器。因此，大多数请求将需要重新分配，这非常低效。

我们希望在不同节点之间均匀分配请求，以便我们能够轻松地添加或删除节点。因此，我们需要一种不直接依赖节点数量（或服务器）的分配方案，这样在添加或删除节点时，需要重新分配的键的数量最小化。

一致性哈希解决了这个水平可扩展性问题，确保每次我们扩展或缩减时，我们不必重新排列所有键或触及所有服务器。

现在我们了解了问题，让我们详细讨论一致性哈希。

## 它是如何工作的

一致性哈希是一种分布式哈希方案，它通过在抽象圆或哈希环上分配位置来独立于分布式哈希表中的节点数量进行操作。这允许服务器和对象进行扩展而不影响整个系统。

!consistent-hashing

使用一致性哈希，只有 `K/N` 的数据需要重新分配。

$$R = K/N$$

其中，

`R`：需要重新分配的数据。
`K`：分区键的数量。
`N`：节点的数量。

哈希函数的输出是一个范围，比如说 `0...m-1`，我们可以在我们的哈希环上表示。我们对请求进行哈希并根据输出将它们分布在环上。同样，我们也对节点进行哈希并将它们分布在同一个环上。

$$
\begin{align*}
& Hash(key_1) = P_1 \\
& Hash(key_2) = P_2 \\
& Hash(key_3) = P_3 \\
& ... \\
& Hash(key_n) = P_{m-1}
\end{align*}
$$

其中，

`key`：请求/节点 ID 或 IP。

`P`：在哈希环上的位置。

`m`：哈希环的总范围。

现在，当请求到来时，我们可以简单地将其路由到顺时针方向（也可以是逆时针方向）最近的节点。这意味着如果添加或删除一个新节点，我们可以使用最近的节点，只有一部分请求需要重新路由。

理论上，一致性哈希应该均匀分配负载，但实际上并不会发生这种情况。通常，负载分布不均匀，一个服务器可能最终处理大多数请求，成为一个热点，实际上成为系统的瓶颈。我们可以通过添加额外的节点来解决这个问题，但这可能会很昂贵。

让我们看看如何解决这些问题。

## 虚拟节点

为了确保更均匀的负载分布，我们可以引入虚拟节点的概念，有时也称为 VNode。

与其为一个节点分配一个位置，不如将哈希范围划分为多个较小的范围，每个物理节点分配这些较小范围中的几个。每个子范围被视为一个 VNode。因此，虚拟节点基本上是现有的物理节点在哈希环上多次映射，以最小化对节点分配范围的更改。

!virtual-nodes

为此，我们可以使用 `k` 个哈希函数。

$$
\begin{align*}
& Hash_1(key_1) = P_1 \\
& Hash_2(key_2) = P_2 \\
& Hash_3(key_3) = P_3 \\
& ... \\
& Hash_k(key_n) = P_{m-1}
\end{align*}
$$

其中，

`key`：请求/节点 ID 或 IP。

`k`：哈希函数的数量。

`P`：在哈希环上的位置。

`m`：哈希环的总范围。

由于 VNode 通过将哈希范围划分为较小的子范围，有助于在集群上的物理节点之间更均匀地分布负载，这加快了添加或删除节点后的重新平衡过程。这也有助于减少热点的概率。

## 数据复制

为了确保高可用性和持久性，一致性哈希在系统中的多个 `N` 个节点上复制每个数据项，其中 `N` 的值等于复制因子。

复制因子是将接收相同数据副本的节点数量。在最终一致性系统中，这是异步完成的。

## 优点

让我们看看一致性哈希的一些优点：

- 使快速扩展和缩减更加可预测。
- 促进跨节点的分区和复制。
- 实现可扩展性和可用性。
- 减少热点。

## 缺点

以下是一些一致性哈希的缺点：

- 增加了复杂性。
- 级联故障。
- 负载分布仍然可能不均匀。
- 当节点暂时失败时，密钥管理可能会很昂贵。

## 示例

让我们看看一些使用一致性哈希的示例：

- Apache Cassandra 中的数据分区。
- Amazon DynamoDB 中的负载分布。

# 数据库联邦

联邦（或功能分区）通过功能拆分数据库。联邦架构使多个独立的物理数据库在最终用户看来像一个逻辑数据库。

联邦中的所有组件通过一个或多个联邦模式连接在一起，这些模式表达了整个联邦的数据共性。这些联邦模式用于指定联邦组件可以共享的信息，并为它们之间的通信提供共同基础。

!database-federation

联邦还提供了从多个来源派生数据的统一视图。联邦系统的数据源可以包括数据库和各种其他形式的结构化和非结构化数据。

## 特点

让我们看看联邦数据库的一些关键特点：

- **透明性**：联邦数据库掩盖了用户对底层数据源的差异和实现。因此，用户不需要知道数据存储在哪里。
- **异构性**：数据源可以在许多方面有所不同。联邦数据库系统可以处理不同的硬件、网络协议、数据模型等。
- **可扩展性**：可能需要新的数据源以满足业务的不断变化需求。一个好的联邦数据库系统需要使添加新源变得容易。
- **自治性**：联邦数据库不会更改现有数据源，接口应保持不变。
- **数据集成**：联邦数据库可以集成来自不同协议、数据库管理系统等的数据。

## 优点

以下是联邦数据库的一些优点：

- 灵活的数据共享。
- 数据库组件之间的自治性。
- 以统一的方式访问异构数据。
- 应用程序与遗留数据库没有紧密耦合。

## 缺点

以下是联邦数据库的一些缺点：

- 增加了更多硬件和额外的复杂性。
- 从两个数据库中连接数据是复杂的。
- 依赖于自治数据源。
- 查询性能和可扩展性。