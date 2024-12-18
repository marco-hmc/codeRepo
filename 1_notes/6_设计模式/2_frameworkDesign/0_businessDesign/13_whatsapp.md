# WhatsApp

让我们设计一个类似于 [WhatsApp](https://whatsapp.com) 的即时消息服务，类似于 [Facebook Messenger](https://www.messenger.com) 和 [WeChat](https://www.wechat.com) 等服务。

## 什么是 WhatsApp？

WhatsApp 是一个为用户提供即时消息服务的聊天应用程序。它是全球使用最广泛的移动应用程序之一，连接了超过 20 亿用户，覆盖 180 多个国家。WhatsApp 也可以在网页上使用。

## 需求

我们的系统应满足以下需求：

### 功能需求

- 应支持一对一聊天。
- 群聊（最多 100 人）。
- 应支持文件共享（图片、视频等）。

### 非功能需求

- 高可用性，延迟最小。
- 系统应具有可扩展性和高效性。

### 扩展需求

- 消息的发送、送达和已读回执。
- 显示用户的最后上线时间。
- 推送通知。

## 估算和约束

让我们从估算和约束开始。

_注意：确保与面试官确认任何与规模或流量相关的假设。_

### 流量

假设我们有 5000 万日活跃用户（DAU），每个用户每天平均向 4 个不同的人发送至少 10 条消息。这给我们带来了每天 20 亿条消息。

$$
50 \space million \times 40 \space messages = 2 \space billion/day
$$

消息还可以包含媒体，如图片、视频或其他文件。我们可以假设 5% 的消息是用户共享的媒体文件，这给我们带来了额外的 1 亿个文件需要存储。

$$
5 \space percent \times 2 \space billion = 100 \space million/day
$$

**我们的系统每秒请求数 (RPS) 会是多少？**

每天 20 亿次请求相当于每秒 24K 次请求。

$$
\frac{2 \space billion}{(24 \space hrs \times 3600 \space seconds)} = \sim 24K \space requests/second
$$

### 存储

如果我们假设每条消息平均为 100 字节，我们每天将需要大约 200 GB 的数据库存储空间。

$$
2 \space billion \times 100 \space bytes = \sim 200 \space GB/day
$$

根据我们的需求，我们还知道每天大约 5% 的消息（1 亿条）是媒体文件。如果我们假设每个文件平均为 100 KB，我们每天将需要 10 TB 的存储空间。

$$
100 \space million \times 100 \space KB = 10 \space TB/day
$$

在 10 年内，我们将需要大约 38 PB 的存储空间。

$$
(10 \space TB + 0.2 \space TB) \times 10 \space years \times 365 \space days = \sim 38 \space PB
$$

### 带宽

由于我们的系统每天处理 10.2 TB 的输入数据，我们将需要大约 120 MB 每秒的最低带宽。

$$
\frac{10.2 \space TB}{(24 \space hrs \times 3600 \space seconds)} = \sim 120 \space MB/second
$$

### 高级估算

以下是我们的高级估算：

| 类型                      | 估算       |
| ------------------------- | ---------- |
| 日活跃用户（DAU）         | 5000 万    |
| 每秒请求数（RPS）         | 24K/s      |
| 存储（每天）              | ~10.2 TB   |
| 存储（10 年）             | ~38 PB     |
| 带宽                      | ~120 MB/s  |

## 数据模型设计

这是反映我们需求的一般数据模型。

![whatsapp-datamodel](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/whatsapp/whatsapp-datamodel.png)

我们有以下表格：

**users**

此表将包含用户的信息，如 [`name`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A107%2C%22character%22%3A54%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")、[`phoneNumber`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A107%2C%22character%22%3A62%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition") 和其他详细信息。

**messages**

顾名思义，此表将存储消息，具有 [`type`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A111%2C%22character%22%3A78%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")（文本、图片、视频等）、[`content`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A111%2C%22character%22%3A113%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition") 和消息传递的时间戳等属性。消息还将有相应的 [`chatID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A111%2C%22character%22%3A204%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition") 或 [`groupID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A111%2C%22character%22%3A216%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")。

**chats**

此表基本上代表两个用户之间的私人聊天，可以包含多条消息。

**users_chats**

此表将用户和聊天映射在一起，因为多个用户可以有多个聊天（N:M 关系），反之亦然。

**groups**

此表代表由多个用户组成的群组。

**users_groups**

此表将用户和群组映射在一起，因为多个用户可以是多个群组的一部分（N:M 关系），反之亦然。

### 我们应该使用哪种数据库？

虽然我们的数据模型看起来相当关系型，但我们不一定需要将所有内容存储在单个数据库中，因为这会限制我们的可扩展性并迅速成为瓶颈。

我们将数据分散到不同的服务中，每个服务拥有特定表的所有权。然后我们可以根据我们的用例使用关系数据库（如 [PostgreSQL](https://www.postgresql.org)）或分布式 NoSQL 数据库（如 [Apache Cassandra](https://cassandra.apache.org/_/index.html)）。

## API 设计

让我们为我们的服务做一个基本的 API 设计：

### 获取所有聊天或群组

此 API 将获取给定 [`userID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A141%2C%22character%22%3A51%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition") 的所有聊天或群组。

```tsx
getAll(userID: UUID): Chat[] | Group[]
```

**参数**

用户 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A144%2C%22character%22%3A15%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 当前用户的 ID。

**返回**

结果 (`Chat[] | Group[]`): 用户参与的所有聊天和群组。

### 获取消息

获取给定 [`channelID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A157%2C%22character%22%3A39%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")（聊天或群组 ID）的所有消息。

```tsx
getMessages(userID: UUID, channelID: UUID): Message[]
```

**参数**

用户 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A144%2C%22character%22%3A15%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 当前用户的 ID。

频道 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A144%2C%22character%22%3A15%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 需要检索消息的频道（聊天或群组）的 ID。

**返回**

消息 (`Message[]`): 给定聊天或群组中的所有消息。

### 发送消息

从用户向频道（聊天或群组）发送消息。

```tsx
sendMessage(userID: UUID, channelID: UUID, message: Message): boolean
```

**参数**

用户 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A144%2C%22character%22%3A15%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 当前用户的 ID。

频道 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A144%2C%22character%22%3A15%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 用户想要发送消息的频道（聊天或群组）的 ID。

消息 ([`Message`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A160%2C%22character%22%3A44%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 用户想要发送的消息（文本、图片、视频等）。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A178%2C%22character%22%3A62%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 表示操作是否成功。

### 加入或离开频道

允许用户加入或离开频道（聊天或群组）。

```tsx
joinGroup(userID: UUID, channelID: UUID): boolean
leaveGroup(userID: UUID, channelID: UUID): boolean
```

**参数**

用户 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A144%2C%22character%22%3A15%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 当前用户的 ID。

频道 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A144%2C%22character%22%3A15%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 用户想要加入或离开的频道（聊天或群组）的 ID。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A178%2C%22character%22%3A62%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition")): 表示操作是否成功。

## 高级设计

现在让我们对我们的系统进行高级设计。

### 架构

我们将使用 [微服务架构](https://karanpratapsingh.com/courses/system-design/monoliths-microservices#microservices)，因为它将使水平扩展和解耦我们的服务变得更容易。每个服务将拥有自己的数据模型。让我们尝试将我们的系统划分为一些核心服务。

**用户服务**

这是一个基于 HTTP 的服务，处理与用户相关的事务，如身份验证和用户信息。

**聊天服务**

聊天服务将使用 WebSockets 与客户端建立连接，以处理聊天和群组消息相关的功能。我们还可以使用缓存来跟踪所有活动连接，类似于会话，这将帮助我们确定用户是否在线。

**通知服务**

此服务将向用户发送推送通知。我们将在单独详细讨论它。

**在线状态服务**

在线状态服务将跟踪所有用户的 _最后上线_ 状态。我们将在单独详细讨论它。

**媒体服务**

此服务将处理媒体（图片、视频、文件等）的上传。我们将在单独详细讨论它。

**服务间通信和服务发现怎么办？**

由于我们的架构是基于微服务的，服务之间也将进行通信。通常，REST 或 HTTP 表现良好，但我们可以使用更轻量且高效的 [gRPC](https://karanpratapsingh.com/courses/system-design/rest-graphql-grpc#grpc) 来进一步提高性能。

[服务发现](https://karanpratapsingh.com/courses/system-design/service-discovery) 是我们需要考虑的另一个问题。我们还可以使用服务网格来实现对各个服务之间的通信进行管理、可观察和安全。

_注意：了解更多关于 [REST、GraphQL、gRPC](https://karanpratapsingh.com/courses/system-design/rest-graphql-grpc) 及其比较的信息。_

### 实时消息

我们如何高效地发送和接收消息？我们有两种不同的选择：

**拉取模型**

客户端可以定期向服务器发送 HTTP 请求，以检查是否有新消息。这可以通过类似 [长轮询](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#long-polling) 的方式实现。

**推送模型**

客户端与服务器建立一个长连接，一旦有新数据可用，它将被推送到客户端。我们可以使用 [WebSockets](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#websockets) 或 [服务器发送事件 (SSE)](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#server-sent-events-sse) 来实现这一点。

拉取模型方法不可扩展，因为它会在我们的服务器上创建不必要的请求开销，并且大多数时候响应将为空，从而浪费我们的资源。为了最小化延迟，使用 [WebSockets](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#websockets) 的推送模型是一个更好的选择，因为这样我们可以在数据可用时立即将其推送到客户端，只要与客户端的连接是打开的。此外，WebSockets 提供全双工通信，而 [服务器发送事件 (SSE)](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#server-sent-events-sse) 仅是单向的。

_注意：了解更多关于 [长轮询、WebSockets、服务器发送事件 (SSE)](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events) 的信息。_

### 最后上线

为了实现最后上线功能，我们可以使用 心跳>) 机制，客户端可以定期向服务器发送 ping 以指示其存活状态。由于这需要尽可能低的开销，我们可以将最后活动时间戳存储在缓存中，如下所示：

| 键      | 值                   |
| ------- | -------------------- |
| 用户 A  | 2022-07-01T14:32:50  |
| 用户 B  | 2022-07-05T05:10:35  |
| 用户 C  | 2022-07-10T04:33:25  |

这将给我们提供用户最后一次活动的时间。此功能将由在线状态服务结合 [Redis](https://redis.io) 或 [Memcached](https://memcached.org) 作为我们的缓存来处理。

另一种实现方式是跟踪用户的最新操作，一旦最后活动超过某个阈值，例如 _“用户在过去 30 秒内没有执行任何操作”_，我们可以显示用户为离线状态，并显示最后记录的时间戳。这将是一种懒更新方法，在某些情况下可能比心跳机制更有利。

### 通知

一旦在聊天或群组中发送消息，我们将首先检查接收者是否活跃，我们可以通过考虑用户的活动连接和最后上线时间来获取此信息。

如果接收者不活跃，聊天服务将添加一个事件到 [消息队列](https://karanpratapsingh.com/courses/system-design/message-queues)，并附加元数据，如客户端设备平台，这将在稍后用于将通知路由到正确的平台。

然后通知服务将从消息队列中消费事件，并根据客户端设备平台（Android、iOS、Web 等）将请求转发到 [Firebase Cloud Messaging (FCM)](https://firebase.google.com/docs/cloud-messaging) 或 [Apple Push Notification Service (APNS)](https://developer.apple.com/documentation/usernotifications)。我们还可以添加对电子邮件和短信的支持。

**为什么我们使用消息队列？**

由于大多数消息队列提供尽力而为的排序，确保消息通常按发送顺序交付，并且消息至少交付一次，这是我们服务功能的重要组成部分。

虽然这看起来像是经典的 [发布-订阅](https://karanpratapsingh.com/courses/system-design/publish-subscribe) 用例，但实际上并不是，因为移动设备和浏览器各自有自己的处理推送通知的方式。通常，通知通过 Firebase Cloud Messaging (FCM) 或 Apple Push Notification Service (APNS) 外部处理，不像我们在后端服务中常见的消息分发。我们可以使用类似 [Amazon SQS](https://aws.amazon.com/sqs) 或 [RabbitMQ](https://www.rabbitmq.com) 的服务来支持此功能。

### 已读回执

处理已读回执可能很棘手，对于此用例，我们可以等待某种 [确认 (ACK)](<https://en.wikipedia.org/wiki/Acknowledgement_(data_networks)>) 来自客户端，以确定消息是否已送达，并更新相应的 [`deliveredAt`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A294%2C%22character%22%3A261%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition") 字段。同样，当用户打开聊天时，我们将消息标记为已读，并更新相应的 [`seenAt`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F13_whatsapp.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A294%2C%22character%22%3A384%7D%7D%5D%2C%22a617b1ed-0fa9-453b-b765-dba3ef77cffd%22%5D "Go to definition") 时间戳字段。

### 设计

现在我们已经确定了一些核心组件，让我们进行系统设计的初稿。

![whatsapp-basic-design](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/whatsapp/whatsapp-basic-design.png)

## 详细设计

现在是详细讨论我们的设计决策的时候了。

### 数据分区

为了扩展我们的数据库，我们需要对数据进行分区。水平分区（也称为 [Sharding](https://karanpratapsingh.com/courses/system-design/sharding)）可以是一个很好的第一步。我们可以使用以下分区方案：

- 基于哈希的分区
- 基于列表的分区
- 基于范围的分区
- 复合分区

上述方法仍然可能导致数据和负载分布不均，我们可以使用 [一致性哈希](https://karanpratapsingh.com/courses/system-design/consistent-hashing) 来解决这个问题。

_更多详细信息，请参考 [Sharding](https://karanpratapsingh.com/courses/system-design/sharding) 和 [一致性哈希](https://karanpratapsingh.com/courses/system-design/consistent-hashing)。_

### 缓存

在消息应用程序中，我们必须小心使用缓存，因为我们的用户期望最新的数据，但许多用户将请求相同的消息，特别是在群聊中。因此，为了防止资源使用峰值，我们可以缓存较旧的消息。

一些群聊可能有成千上万条消息，通过网络发送这些消息将非常低效，为了提高效率，我们可以在系统 API 中添加分页功能。这个决定将对网络带宽有限的用户有帮助，因为他们不必检索旧消息，除非请求。

**使用哪种缓存驱逐策略？**

我们可以使用类似 [Redis](https://redis.io) 或 [Memcached](https://memcached.org) 的解决方案，并缓存每日流量的 20%，但哪种缓存驱逐策略最适合我们的需求？

[最近最少使用 (LRU)](<https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)>) 可以是我们系统的一个好策略。在这种策略中，我们首先丢弃最近最少使用的键。

**如何处理缓存未命中？**

每当发生缓存未命中时，我们的服务器可以直接访问数据库并使用新条目更新缓存。

_更多详细信息，请参考 [缓存](https://karanpratapsingh.com/courses/system-design/caching)。_

### 媒体访问和存储

如我们所知，大部分存储空间将用于存储媒体文件，如图像、视频或其他文件。我们的媒体服务将处理用户媒体文件的访问和存储。

但我们可以在哪里大规模存储文件呢？[对象存储](https://karanpratapsingh.com/courses/system-design/storage#object-storage) 是我们需要的。对象存储将数据文件分解成称为对象的片段，然后将这些对象存储在一个可以分布在多个网络系统中的单一存储库中。我们还可以使用分布式文件存储，如 [HDFS](https://karanpratapsingh.com/courses/system-design/storage#hdfs) 或 [GlusterFS](https://www.gluster.org)。

_有趣的事实：WhatsApp 在用户下载媒体后会从其服务器上删除媒体。_

我们可以使用类似 [Amazon S3](https://aws.amazon.com/s3)、[Azure Blob Storage](https://azure.microsoft.com/en-in/services/storage/blobs) 或 [Google Cloud Storage](https://cloud.google.com/storage) 的对象存储来实现这一用例。

### 内容分发网络 (CDN)

[内容分发网络 (CDN)](https://karanpratapsingh.com/courses/system-design/content-delivery-network) 增加了内容的可用性和冗余性，同时降低了带宽成本。通常，静态文件如图像和视频是从 CDN 提供的。我们可以使用 [Amazon CloudFront](https://aws.amazon.com/cloudfront) 或 [Cloudflare CDN](https://www.cloudflare.com/cdn) 等服务来实现这一用例。

### API 网关

由于我们将使用多种协议，如 HTTP、WebSocket、TCP/IP，为每种协议分别部署多个 L4（传输层）或 L7（应用层）类型的负载均衡器将会很昂贵。相反，我们可以使用支持多种协议的 [API 网关](https://karanpratapsingh.com/courses/system-design/api-gateway)，不会有任何问题。

API 网关还可以提供其他功能，如身份验证、授权、速率限制、流量控制和 API 版本管理，这将提高我们服务的质量。

我们可以使用 [Amazon API Gateway](https://aws.amazon.com/api-gateway) 或 [Azure API Gateway](https://azure.microsoft.com/en-in/services/api-management) 等服务来实现这一用例。

## 识别和解决瓶颈

![whatsapp-advanced-design](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/whatsapp/whatsapp-advanced-design.png)

让我们识别和解决设计中的瓶颈，如单点故障：

- “如果我们的某个服务崩溃了怎么办？”
- “我们将如何在组件之间分配流量？”
- “我们如何减少数据库的负载？”
- “如何提高缓存的可用性？”
- “API 网关不会成为单点故障吗？”
- “我们如何使通知系统更健壮？”
- “我们如何降低媒体存储成本？”
- “聊天服务的责任是否过多？”

为了使我们的系统更具弹性，我们可以采取以下措施：

- 运行每个服务的多个实例。
- 在客户端、服务器、数据库和缓存服务器之间引入[负载均衡器](https://karanpratapsingh.com/courses/system-design/load-balancing)。
- 为我们的数据库使用多个只读副本。
- 为我们的分布式缓存使用多个实例和副本。
- 我们可以有一个 API 网关的备用副本。
- 在分布式系统中，确保消息的“恰好一次”投递和消息排序是具有挑战性的，我们可以使用专用的[消息代理](https://karanpratapsingh.com/courses/system-design/message-brokers)（如 [Apache Kafka](https://kafka.apache.org) 或 [NATS](https://nats.io)）来使我们的通知系统更健壮。
- 我们可以为媒体服务添加媒体处理和压缩功能，以压缩大文件，类似于 WhatsApp，这将节省大量存储空间并降低成本。
- 我们可以创建一个独立于聊天服务的群组服务，以进一步解耦我们的服务。