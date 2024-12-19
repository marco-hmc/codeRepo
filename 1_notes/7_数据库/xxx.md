# 一致性哈希

首先让我们了解我们要解决的问题。

## 为什么我们需要这个？

在传统的基于哈希的分布方法中，我们使用哈希函数来哈希我们的分区键（例如请求 ID 或 IP）。然后，如果我们对节点总数（服务器或数据库）取模，这将给我们要路由请求的节点。

![simple-hashing](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/consistent-hashing/simple-hashing.png)

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

[`key`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A22%2C%22character%22%3A1%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：请求 ID 或 IP。

[`H`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A24%2C%22character%22%3A1%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：哈希函数结果。

[`N`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A12%2C%22character%22%3A28%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：节点总数。

[`Node`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A16%2C%22character%22%3A32%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：请求将被路由到的节点。

问题在于，如果我们添加或删除一个节点，将导致 [`N`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A12%2C%22character%22%3A28%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition") 发生变化，这意味着我们的映射策略将失效，因为相同的请求现在将映射到不同的服务器。因此，大多数请求将需要重新分配，这非常低效。

我们希望在不同节点之间均匀分配请求，以便我们能够轻松地添加或删除节点。因此，我们需要一种不直接依赖节点数量（或服务器）的分配方案，这样在添加或删除节点时，需要重新分配的键的数量最小化。

一致性哈希解决了这个水平可扩展性问题，确保每次我们扩展或缩减时，我们不必重新排列所有键或触及所有服务器。

现在我们了解了问题，让我们详细讨论一致性哈希。

## 它是如何工作的

一致性哈希是一种分布式哈希方案，它通过在抽象圆或哈希环上分配位置来独立于分布式哈希表中的节点数量进行操作。这允许服务器和对象进行扩展而不影响整个系统。

![consistent-hashing](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/consistent-hashing/consistent-hashing.png)

使用一致性哈希，只有 `K/N` 的数据需要重新分配。

$$
R = K/N
$$

其中，

[`R`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A47%2C%22character%22%3A0%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：需要重新分配的数据。

[`K`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A44%2C%22character%22%3A32%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：分区键的数量。

[`N`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A12%2C%22character%22%3A28%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：节点的数量。

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

[`key`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A22%2C%22character%22%3A1%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：请求/节点 ID 或 IP。

[`P`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A66%2C%22character%22%3A16%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：在哈希环上的位置。

[`m`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A58%2C%22character%22%3A58%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：哈希环的总范围。

现在，当请求到来时，我们可以简单地将其路由到顺时针方向（也可以是逆时针方向）最近的节点。这意味着如果添加或删除一个新节点，我们可以使用最近的节点，只有一部分请求需要重新路由。

理论上，一致性哈希应该均匀分配负载，但实际上并不会发生这种情况。通常，负载分布不均匀，一个服务器可能最终处理大多数请求，成为一个热点，实际上成为系统的瓶颈。我们可以通过添加额外的节点来解决这个问题，但这可能会很昂贵。

让我们看看如何解决这些问题。

## 虚拟节点

为了确保更均匀的负载分布，我们可以引入虚拟节点的概念，有时也称为 VNode。

与其为一个节点分配一个位置，不如将哈希范围划分为多个较小的范围，每个物理节点分配这些较小范围中的几个。每个子范围被视为一个 VNode。因此，虚拟节点基本上是现有的物理节点在哈希环上多次映射，以最小化对节点分配范围的更改。

![virtual-nodes](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/consistent-hashing/virtual-nodes.png)

为此，我们可以使用 [`k`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A92%2C%22character%22%3A22%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition") 个哈希函数。

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

[`key`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A22%2C%22character%22%3A1%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：请求/节点 ID 或 IP。

[`k`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A92%2C%22character%22%3A22%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：哈希函数的数量。

[`P`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A66%2C%22character%22%3A16%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：在哈希环上的位置。

[`m`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A58%2C%22character%22%3A58%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition")：哈希环的总范围。

由于 VNode 通过将哈希范围划分为较小的子范围，有助于在集群上的物理节点之间更均匀地分布负载，这加快了添加或删除节点后的重新平衡过程。这也有助于减少热点的概率。

## 数据复制

为了确保高可用性和持久性，一致性哈希在系统中的多个 [`N`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A12%2C%22character%22%3A28%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition") 个节点上复制每个数据项，其中 [`N`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F7_%E6%95%B0%E6%8D%AE%E5%BA%93%2Fxxx.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A12%2C%22character%22%3A28%7D%7D%5D%2C%224657aeb0-573a-484d-8605-6e518cbeb729%22%5D "Go to definition") 的值等于复制因子。

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

- [Apache Cassandra](https://cassandra.apache.org) 中的数据分区。
- [Amazon DynamoDB](https://aws.amazon.com/dynamodb) 中的负载分布。

# 数据库联邦

联邦（或功能分区）通过功能拆分数据库。联邦架构使多个独立的物理数据库在最终用户看来像一个逻辑数据库。

联邦中的所有组件通过一个或多个联邦模式连接在一起，这些模式表达了整个联邦的数据共性。这些联邦模式用于指定联邦组件可以共享的信息，并为它们之间的通信提供共同基础。

![database-federation](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-II/database-federation/database-federation.png)

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