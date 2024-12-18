# Twitter

让我们设计一个类似 [Twitter](https://twitter.com) 的社交媒体服务，类似于 [Facebook](https://facebook.com)、[Instagram](https://instagram.com) 等服务。

## 什么是 Twitter？

Twitter 是一种社交媒体服务，用户可以阅读或发布短消息（最多 280 个字符），称为推文。它可以在网页和移动平台（如 Android 和 iOS）上使用。

## 需求

我们的系统应满足以下需求：

### 功能需求

- 应该能够发布新的推文（可以是文本、图片、视频等）。
- 应该能够关注其他用户。
- 应该有一个新闻推送功能，包含用户关注的人的推文。
- 应该能够搜索推文。

### 非功能需求

- 高可用性，延迟最小。
- 系统应具有可扩展性和高效性。

### 扩展需求

- 指标和分析。
- 转推功能。
- 收藏推文。

## 估算和约束

让我们从估算和约束开始。

_注意：确保与面试官确认任何与规模或流量相关的假设。_

### 流量

这是一个以读取为主的系统，我们假设我们有 10 亿总用户，其中 2 亿是每日活跃用户（DAU），平均每个用户每天发 5 条推文。这给我们带来了每天 10 亿条推文。

$$
200 \space million \times 5 \space tweets = 1 \space billion/day
$$

推文还可以包含媒体，如图片或视频。我们可以假设 10% 的推文是用户分享的媒体文件，这给我们带来了额外的 1 亿个文件需要存储。

$$
10 \space percent \times 1 \space billion = 100 \space million/day
$$

**我们的系统每秒请求数（RPS）是多少？**

每天 10 亿次请求转换为每秒 12K 次请求。

$$
\frac{1 \space billion}{(24 \space hrs \times 3600 \space seconds)} = \sim 12K \space requests/second
$$

### 存储

如果我们假设每条消息平均为 100 字节，我们每天将需要大约 100 GB 的数据库存储。

$$
1 \space billion \times 100 \space bytes = \sim 100 \space GB/day
$$

我们还知道，根据我们的需求，每天大约 10% 的消息（1 亿条）是媒体文件。如果我们假设每个文件平均为 50 KB，我们每天将需要 5 TB 的存储。

$$
100 \space million \times 50 \space KB = 5 \space TB/day
$$

在 10 年内，我们将需要大约 19 PB 的存储。

$$
(5 \space TB + 0.1 \space TB) \times 365 \space days \times 10 \space years = \sim 19 \space PB
$$

### 带宽

由于我们的系统每天处理 5.1 TB 的输入，我们将需要大约 60 MB 每秒的最小带宽。

$$
\frac{5.1 \space TB}{(24 \space hrs \times 3600 \space seconds)} = \sim 60 \space MB/second
$$

### 高级估算

以下是我们的高级估算：

| 类型                      | 估算        |
| ------------------------- | ----------- |
| 每日活跃用户（DAU）       | 2 亿        |
| 每秒请求数（RPS）         | 12K/s       |
| 存储（每天）              | ~5.1 TB     |
| 存储（10 年）             | ~19 PB      |
| 带宽                      | ~60 MB/s    |

## 数据模型设计

这是反映我们需求的一般数据模型。

![twitter-datamodel](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/twitter/twitter-datamodel.png)

我们有以下表格：

**users**

此表将包含用户的信息，如 [`name`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A108%2C%22character%22%3A54%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")、[`email`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A108%2C%22character%22%3A62%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")、[`dob`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A108%2C%22character%22%3A71%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition") 和其他详细信息。

**tweets**

顾名思义，此表将存储推文及其属性，如 [`type`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A112%2C%22character%22%3A81%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")（文本、图片、视频等）、[`content`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A112%2C%22character%22%3A116%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition") 等。我们还将存储相应的 [`userID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A112%2C%22character%22%3A169%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")。

**favorites**

此表将推文与用户映射，以实现我们应用中的收藏推文功能。

**followers**

此表将关注者和被关注者（followees）映射，因为用户可以相互关注（N:M 关系）。

**feeds**

此表存储与相应 [`userID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A112%2C%22character%22%3A169%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition") 相关的推送属性。

**feeds_tweets**

此表将推文和推送映射（N:M 关系）。

### 我们应该使用哪种数据库？

虽然我们的数据模型看起来相当关系型，但我们不一定需要将所有内容存储在单个数据库中，因为这会限制我们的可扩展性并迅速成为瓶颈。

我们将数据分散到不同的服务中，每个服务拥有特定表的所有权。然后我们可以使用关系数据库，如 [PostgreSQL](https://www.postgresql.org) 或分布式 NoSQL 数据库，如 [Apache Cassandra](https://cassandra.apache.org/_/index.html) 来满足我们的需求。

## API 设计

让我们为我们的服务做一个基本的 API 设计：

### 发布推文

此 API 将允许用户在平台上发布推文。

```tsx
postTweet(userID: UUID, content: string, mediaURL?: string): boolean
```

**参数**

用户 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A18%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")): 用户的 ID。

内容 ([`string`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A33%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")): 推文的内容。

媒体 URL ([`string`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A33%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")): 附加媒体的 URL _(可选)_。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A61%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")): 表示操作是否成功。

### 关注或取消关注用户

此 API 将允许用户关注或取消关注其他用户。

```tsx
follow(followerID: UUID, followeeID: UUID): boolean
unfollow(followerID: UUID, followeeID: UUID): boolean
```

**参数**

关注者 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A18%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")): 当前用户的 ID。

被关注者 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A18%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")): 我们想要关注或取消关注的用户的 ID。

媒体 URL ([`string`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A33%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")): 附加媒体的 URL _(可选)_。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A61%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")): 表示操作是否成功。

### 获取新闻推送

此 API 将返回要在给定新闻推送中显示的所有推文。

```tsx
getNewsfeed(userID: UUID): Tweet[]
```

**参数**

用户 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A18%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")): 用户的 ID。

**返回**

推文 (`Tweet[]`): 要在给定新闻推送中显示的所有推文。

## 高级设计

现在让我们对我们的系统进行高级设计。

### 架构

我们将使用 [微服务架构](https://karanpratapsingh.com/courses/system-design/monoliths-microservices#microservices)，因为它将使水平扩展和解耦我们的服务变得更容易。每个服务将拥有自己的数据模型。让我们尝试将我们的系统划分为一些核心服务。

**用户服务**

此服务处理与用户相关的事务，如身份验证和用户信息。

**新闻推送服务**

此服务将处理用户新闻推送的生成和发布。我们将单独详细讨论它。

**推文服务**

推文服务将处理与推文相关的用例，如发布推文、收藏等。

**搜索服务**

此服务负责处理与搜索相关的功能。我们将单独详细讨论它。

**媒体服务**

此服务将处理媒体（图片、视频、文件等）的上传。我们将单独详细讨论它。

**通知服务**

此服务将向用户发送推送通知。

**分析服务**

此服务将用于指标和分析用例。

**服务间通信和服务发现怎么办？**

由于我们的架构是基于微服务的，服务之间也将进行通信。通常，REST 或 HTTP 表现良好，但我们可以使用更轻量且高效的 [gRPC](https://karanpratapsingh.com/courses/system-design/rest-graphql-grpc#grpc) 来进一步提高性能。

[服务发现](https://karanpratapsingh.com/courses/system-design/service-discovery) 是我们需要考虑的另一个问题。我们还可以使用服务网格来实现各个服务之间的管理、可观察和安全通信。

_注意：了解更多关于 [REST、GraphQL、gRPC](https://karanpratapsingh.com/courses/system-design/rest-graphql-grpc) 及其比较的信息。_

### 新闻推送

当涉及到新闻推送时，似乎很容易实现，但有很多事情可能会影响这个功能的成败。所以，让我们将问题分为两部分：

**生成**

假设我们想为用户 A 生成推送，我们将执行以下步骤：

1. 检索用户 A 关注的所有用户和实体（标签、主题等）的 ID。
2. 获取每个检索到的 ID 的相关推文。
3. 使用排名算法根据相关性、时间、参与度等参数对推文进行排名。
4. 以分页方式将排名后的推文数据返回给客户端。

推送生成是一个密集的过程，尤其是对于关注很多人的用户来说，可能需要相当多的时间。为了提高性能，可以预生成推送并将其存储在缓存中，然后我们可以有一个机制定期更新推送并将我们的排名算法应用于新推文。

**发布**

发布是根据每个特定用户推送推送数据的步骤。这可能是一个相当繁重的操作，因为一个用户可能有数百万的朋友或关注者。为了解决这个问题，我们有三种不同的方法：

- 拉取模型（或负载时扇出）

![newsfeed-pull-model](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/twitter/newsfeed-pull-model.png)

当用户创建推文并且关注者重新加载他们的新闻推送时，推送会被创建并存储在内存中。只有当用户请求时，才会加载最新的推送。这种方法减少了数据库上的写操作次数。

这种方法的缺点是，用户在“拉取”数据之前无法查看最新的推送，这将增加服务器上的读取操作次数。

- 推送模型（或写入时扇出）

![newsfeed-push-model](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/twitter/newsfeed-push-model.png)

在这种模型中，一旦用户创建推文，它会立即“推送”到所有关注者的推送中。这防止系统必须遍历用户的整个关注者列表以检查更新。

然而，这种方法的缺点是会增加数据库上的写操作次数。

- 混合模型

第三种方法是拉取和推送模型之间的混合模型。它结合了上述两种模型的有益特性，并尝试在两者之间提供平衡的方法。

混合模型允许只有较少关注者的用户使用推送模型。对于关注者较多的用户，如名人，则使用拉取模型。

### 排名算法

正如我们所讨论的，我们需要一个排名算法来根据每个特定用户的相关性对每条推文进行排名。

例如，Facebook 曾经使用 [EdgeRank](https://en.wikipedia.org/wiki/EdgeRank) 算法。这里，每个推送项的排名由以下公式描述：

$$
Rank = Affinity \times Weight \times Decay
$$

其中，

[`Affinity`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A289%2C%22character%22%3A7%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")：是用户与边创建者的“亲密度”。如果用户经常点赞、评论或消息边创建者，那么亲密度的值会更高，从而导致帖子获得更高的排名。

[`Weight`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A289%2C%22character%22%3A23%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")：是根据每个边分配的值。评论的权重可能比点赞更高，因此评论更多的帖子更有可能获得更高的排名。

[`Decay`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A289%2C%22character%22%3A37%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition")：是边创建的时间的度量。边越旧，衰减值越小，最终排名越低。

如今，算法更加复杂，排名是使用可以考虑数千个因素的机器学习模型完成的。

### 转推

转推是我们的扩展需求之一。要实现此功能，我们可以简单地创建一个新推文，使用转推原始推文的用户 ID，然后修改新推文的 [`type`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A112%2C%22character%22%3A81%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition") 枚举和 [`content`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A112%2C%22character%22%3A116%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition") 属性以链接到原始推文。

例如，[`type`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A112%2C%22character%22%3A81%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition") 枚举属性可以是推文类型，类似于文本、视频等，而 [`content`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A112%2C%22character%22%3A116%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition") 可以是原始推文的 ID。这里第一行表示原始推文，而第二行表示我们如何表示转推。

| id                  | userID              | type  | content                      | createdAt     |
| ------------------- | ------------------- | ----- | ---------------------------- | ------------- |
| ad34-291a-45f6-b36c | 7a2c-62c4-4dc8-b1bb | text  | Hey, this is my first tweet… | 1658905644054 |
| f064-49ad-9aa2-84a6 | 6aa2-2bc9-4331-879f | tweet | ad34-291a-45f6-b36c          | 1658906165427 |

这是一个非常基本的实现。为了改进这一点，我们可以创建一个单独的表来存储转推。

### 搜索

有时传统的 DBMS 性能不足，我们需要一些能够快速、近实时地存储、搜索和分析大量数据并在毫秒内给出结果的东西。[Elasticsearch](https://www.elastic.co) 可以帮助我们实现这一用例。

[Elasticsearch](https://www.elastic.co) 是一个分布式、免费且开放的搜索和分析引擎，适用于所有类型的数据，包括文本、数字、地理空间、结构化和非结构化数据。它构建在 [Apache Lucene](https://lucene.apache.org) 之上。

**我们如何识别热门话题？**

热门功能将基于搜索功能。我们可以缓存最近 [`N`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A120%2C%22character%22%3A119%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition") 秒内最频繁搜索的查询、标签和话题，并使用某种批处理机制每 [`M`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F10_twiteer.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A120%2C%22character%22%3A121%7D%7D%5D%2C%22f3881375-f8b3-48bd-ad59-3145029a808a%22%5D "Go to definition") 秒更新它们。我们的排名算法也可以应用于热门话题，以赋予它们更多权重并为用户个性化。

### 通知

推送通知是任何社交媒体平台的重要组成部分。我们可以使用消息队列或消息代理，如 [Apache Kafka](https://kafka.apache.org) 与通知服务一起分发请求到 [Firebase Cloud Messaging (FCM)](https://firebase.google.com/docs/cloud-messaging) 或 [Apple Push Notification Service (APNS)](https://developer.apple.com/documentation/usernotifications)，它们将处理推送通知的传递到用户设备。

_有关更多详细信息，请参阅 [WhatsApp](https://karanpratapsingh.com/courses/system-design/whatsapp#notifications) 系统设计，我们在其中详细讨论了推送通知。_

## 详细设计

现在是详细讨论我们的设计决策的时候了。

### 数据分区

为了扩展我们的数据库，我们需要对数据进行分区。水平分区（也称为 [Sharding](https://karanpratapsingh.com/courses/system-design/sharding)）可以是一个很好的第一步。我们可以使用以下分区方案：

- 基于哈希的分区
- 基于列表的分区
- 基于范围的分区
- 复合分区

上述方法仍然可能导致数据和负载分布不均，我们可以使用 [一致性哈希](https://karanpratapsingh.com/courses/system-design/consistent-hashing) 来解决这个问题。

_有关更多详细信息，请参阅 [Sharding](https://karanpratapsingh.com/courses/system-design/sharding) 和 [一致性哈希](https://karanpratapsingh.com/courses/system-design/consistent-hashing)。_

### 共同好友

对于共同好友，我们可以为每个用户构建一个社交图。图中的每个节点将表示一个用户，定向边将表示关注者和被关注者。之后，我们可以遍历用户的关注者以找到并建议共同好友。这需要一个图数据库，如 [Neo4j](https://neo4j.com) 或 [ArangoDB](https://www.arangodb.com)。

这是一个相当简单的算法，为了提高我们的建议准确性，我们需要将机器学习推荐模型作为我们算法的一部分。

### 指标和分析

记录分析和指标是我们的扩展需求之一。由于我们将使用 [Apache Kafka](https://kafka.apache.org) 发布各种事件，我们可以处理这些事件并使用 [Apache Spark](https://spark.apache.org) 在数据上运行分析，Apache Spark 是一个开源的统一分析引擎，用于大规模数据处理。

### 缓存

在社交媒体应用中，我们必须小心使用缓存，因为我们的用户期望最新的数据。因此，为了防止资源使用激增，我们可以缓存前 20% 的推文。

为了进一步提高效率，我们可以在系统 API 中添加分页功能。这个决定将对网络带宽有限的用户有帮助，因为他们不必检索旧消息，除非请求。

**使用哪种缓存驱逐策略？**

我们可以使用 [Redis](https://redis.io) 或 [Memcached](https://memcached.org) 等解决方案，并缓存每日流量的 20%，但哪种缓存驱逐策略最适合我们的需求？

最近最少使用（LRU）>) 可以是我们系统的一个好策略。在这种策略中，我们首先丢弃最近最少使用的键。

**如何处理缓存未命中？**

每当发生缓存未命中时，我们的服务器可以直接访问数据库并使用新条目更新缓存。

_有关更多详细信息，请参阅 [Caching](https://karanpratapsingh.com/courses/system-design/caching)。_


### 媒体访问和存储

如我们所知，大部分存储空间将用于存储媒体文件，如图像、视频或其他文件。我们的媒体服务将处理用户媒体文件的访问和存储。

但我们可以在哪里大规模存储文件呢？[对象存储](https://karanpratapsingh.com/courses/system-design/storage#object-storage) 是我们需要的。对象存储将数据文件分解成称为对象的片段，然后将这些对象存储在一个可以分布在多个网络系统中的单一存储库中。我们还可以使用分布式文件存储，如 [HDFS](https://karanpratapsingh.com/courses/system-design/storage#hdfs) 或 [GlusterFS](https://www.gluster.org)。

### 内容分发网络 (CDN)

[内容分发网络 (CDN)](https://karanpratapsingh.com/courses/system-design/content-delivery-network) 增加了内容的可用性和冗余性，同时降低了带宽成本。通常，静态文件如图像和视频是从 CDN 提供的。我们可以使用 [Amazon CloudFront](https://aws.amazon.com/cloudfront) 或 [Cloudflare CDN](https://www.cloudflare.com/cdn) 等服务来实现这一用例。

## 识别和解决瓶颈

![twitter-advanced-design](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/twitter/twitter-advanced-design.png)

让我们识别和解决设计中的瓶颈，如单点故障：

- “如果我们的某个服务崩溃了怎么办？”
- “我们将如何在组件之间分配流量？”
- “我们如何减少数据库的负载？”
- “如何提高缓存的可用性？”
- “我们如何使通知系统更健壮？”
- “我们如何降低媒体存储成本？”

为了使我们的系统更具弹性，我们可以采取以下措施：

- 运行每个服务的多个实例。
- 在客户端、服务器、数据库和缓存服务器之间引入[负载均衡器](https://karanpratapsingh.com/courses/system-design/load-balancing)。
- 为我们的数据库使用多个只读副本。
- 为我们的分布式缓存使用多个实例和副本。
- 在分布式系统中，确保消息的“恰好一次”投递和消息排序是具有挑战性的，我们可以使用专用的[消息代理](https://karanpratapsingh.com/courses/system-design/message-brokers)（如 [Apache Kafka](https://kafka.apache.org) 或 [NATS](https://nats.io)）来使我们的通知系统更健壮。
- 我们可以为媒体服务添加媒体处理和压缩功能，以压缩大文件，这将节省大量存储空间并降低成本。