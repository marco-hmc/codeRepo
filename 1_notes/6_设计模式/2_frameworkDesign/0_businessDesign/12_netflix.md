# Netflix

让我们设计一个类似 [Netflix](https://netflix.com) 的视频流媒体服务，类似于 [Amazon Prime Video](https://www.primevideo.com)、[Disney Plus](https://www.disneyplus.com)、[Hulu](https://www.hulu.com)、[YouTube](https://youtube.com)、[Vimeo](https://vimeo.com) 等服务。

## 什么是 Netflix？

Netflix 是一种基于订阅的流媒体服务，允许其会员在连接互联网的设备上观看电视节目和电影。它可以在 Web、iOS、Android、电视等平台上使用。

## 需求

我们的系统应满足以下需求：

### 功能需求

- 用户应该能够流式传输和分享视频。
- 内容团队（或在 YouTube 的情况下是用户）应该能够上传新视频（电影、电视剧集和其他内容）。
- 用户应该能够通过标题或标签搜索视频。
- 用户应该能够对视频发表评论，类似于 YouTube。

### 非功能需求

- 高可用性，延迟最小。
- 高可靠性，上传不应丢失。
- 系统应具有可扩展性和高效性。

### 扩展需求

- 某些内容应进行[地理封锁](https://en.wikipedia.org/wiki/Geo-blocking)。
- 从用户上次停止的地方恢复视频播放。
- 记录视频的指标和分析数据。

## 估算和约束

让我们从估算和约束开始。

_注意：确保与面试官确认任何与规模或流量相关的假设。_

### 流量

这是一个以读取为主的系统，我们假设我们有 10 亿总用户，其中 2 亿是日活跃用户（DAU），平均每个用户每天观看 5 个视频。这给我们每天 10 亿个视频观看量。

$$
200 \space million \times 5 \space videos = 1 \space billion/day
$$

假设读写比为 `200:1`，每天大约会上传 500 万个视频。

$$
\frac{1}{200} \times 1 \space billion = 5 \space million/day
$$

**我们的系统每秒请求数（RPS）是多少？**

每天 10 亿次请求转换为每秒 12K 次请求。

$$
\frac{1 \space billion}{(24 \space hrs \times 3600 \space seconds)} = \sim 12K \space requests/second
$$

### 存储

如果我们假设每个视频平均为 100 MB，我们每天将需要大约 500 TB 的存储空间。

$$
5 \space million \times 100 \space MB = 500 \space TB/day
$$

在 10 年内，我们将需要惊人的 1,825 PB 的存储空间。

$$
500 \space TB \times 365 \space days \times 10 \space years = \sim 1,825 \space PB
$$

### 带宽

由于我们的系统每天处理 500 TB 的输入，我们将需要大约 5.8 GB 每秒的最小带宽。

$$
\frac{500 \space TB}{(24 \space hrs \times 3600 \space seconds)} = \sim 5.8 \space GB/second
$$

### 高级估算

以下是我们的高级估算：

| 类型                      | 估算        |
| ------------------------- | ----------- |
| 日活跃用户（DAU）         | 2 亿        |
| 每秒请求数（RPS）         | 12K/s       |
| 每日存储量                | ~500 TB     |
| 10 年存储量               | ~1,825 PB   |
| 带宽                      | ~5.8 GB/s   |

## 数据模型设计

这是反映我们需求的一般数据模型。

![netflix-datamodel](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/netflix/netflix-datamodel.png)

我们有以下表格：

**users**

此表将包含用户的信息，如 [`name`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A103%2C%22character%22%3A54%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition")、[`email`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A103%2C%22character%22%3A62%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition")、[`dob`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A103%2C%22character%22%3A71%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition") 和其他详细信息。

**videos**

顾名思义，此表将存储视频及其属性，如 [`title`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A107%2C%22character%22%3A81%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition")、[`streamURL`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A107%2C%22character%22%3A90%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition")、[`tags`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A16%2C%22character%22%3A60%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition") 等。我们还将存储相应的 [`userID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A107%2C%22character%22%3A153%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition")。

**tags**

此表将简单地存储与视频相关的标签。

**views**

此表帮助我们存储视频收到的所有观看次数。

**comments**

此表存储视频收到的所有评论（类似于 YouTube）。

### 我们应该使用哪种数据库？

虽然我们的数据模型看起来相当关系型，但我们不一定需要将所有内容存储在单个数据库中，因为这会限制我们的可扩展性并迅速成为瓶颈。

我们将数据分散到不同的服务中，每个服务拥有特定表的所有权。然后我们可以使用关系数据库，如 [PostgreSQL](https://www.postgresql.org) 或分布式 NoSQL 数据库，如 [Apache Cassandra](https://cassandra.apache.org/_/index.html) 来满足我们的用例。

## API 设计

让我们为我们的服务做一个基本的 API 设计：

### 上传视频

给定一个字节流，此 API 使视频能够上传到我们的服务。

```tsx
uploadVideo(title: string, description: string, data: Stream<byte>, tags?: string[]): boolean
```

**参数**

标题 ([`string`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A136%2C%22character%22%3A19%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：新视频的标题。

描述 ([`string`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A136%2C%22character%22%3A19%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：新视频的描述。

数据 (`byte[]`)：视频数据的字节流。

标签 (`string[]`)：视频的标签 _(可选)_。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A136%2C%22character%22%3A86%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：表示操作是否成功。

### 流式传输视频

此 API 允许我们的用户以首选的编解码器和分辨率流式传输视频。

```tsx
streamVideo(videoID: UUID, codec: Enum<string>, resolution: Tuple<int>, offset?: int): VideoStream
```

**参数**

视频 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A158%2C%22character%22%3A21%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：需要流式传输的视频的 ID。

编解码器 (`Enum<string>`)：请求视频的所需[编解码器](https://en.wikipedia.org/wiki/Video_codec)，如 `h.265`、`h.264`、[`VP9`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A165%2C%22character%22%3A135%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition") 等。

分辨率 (`Tuple<int>`)：请求视频的[分辨率](https://en.wikipedia.org/wiki/Display_resolution)。

偏移量 ([`int`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A158%2C%22character%22%3A66%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：视频流的偏移量，以秒为单位，从视频的任何点开始流式传输数据 _(可选)_。

**返回**

流 ([`VideoStream`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A158%2C%22character%22%3A87%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：请求视频的数据流。

### 搜索视频

此 API 将使我们的用户能够根据标题或标签搜索视频。

```tsx
searchVideo(query: string, nextPage?: string): Video[]
```

**参数**

查询 ([`string`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A136%2C%22character%22%3A19%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：用户的搜索查询。

下一页 ([`string`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A136%2C%22character%22%3A19%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：下一页的令牌，可用于分页 _(可选)_。

**返回**

视频 (`Video[]`)：所有可用于特定搜索查询的视频。

### 添加评论

此 API 将允许我们的用户在视频上发表评论（类似于 YouTube）。

```tsx
comment(videoID: UUID, comment: string): boolean
```

**参数**

视频 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A158%2C%22character%22%3A21%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：用户想要评论的视频的 ID。

评论 ([`string`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A136%2C%22character%22%3A19%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：评论的文本内容。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A136%2C%22character%22%3A86%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition"))：表示操作是否成功。

## 高级设计

现在让我们对我们的系统进行高级设计。

### 架构

我们将使用[微服务架构](https://karanpratapsingh.com/courses/system-design/monoliths-microservices#microservices)，因为它将使水平扩展和解耦我们的服务变得更容易。每个服务将拥有自己的数据模型。让我们尝试将我们的系统划分为一些核心服务。

**用户服务**

此服务处理与用户相关的事务，如身份验证和用户信息。

**流服务**

流服务将处理视频流相关的功能。

**搜索服务**

此服务负责处理搜索相关的功能。我们将单独详细讨论。

**媒体服务**

此服务将处理视频上传和处理。我们将单独详细讨论。

**分析服务**

此服务将用于指标和分析用例。

**服务间通信和服务发现怎么办？**

由于我们的架构是基于微服务的，服务之间也将进行通信。通常，REST 或 HTTP 表现良好，但我们可以使用更轻量且高效的 [gRPC](https://karanpratapsingh.com/courses/system-design/rest-graphql-grpc#grpc) 进一步提高性能。

[服务发现](https://karanpratapsingh.com/courses/system-design/service-discovery) 是我们需要考虑的另一件事。我们还可以使用服务网格来实现各个服务之间的管理、可观察和安全通信。

_注意：了解更多关于 [REST、GraphQL、gRPC](https://karanpratapsingh.com/courses/system-design/rest-graphql-grpc) 及其比较的信息。_

### 视频处理

![video-processing-pipeline](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/netflix/video-processing-pipeline.png)

在处理视频时，有许多变量在起作用。例如，来自高端摄像机的两小时原始 8K 视频的平均数据大小可以轻松达到 4 TB，因此我们需要进行某种处理来减少存储和交付成本。

以下是内容团队（或在 YouTube 的情况下是用户）上传视频后，视频被排队处理的方式。

让我们讨论这是如何工作的：

- **文件分块**

![file-chunking](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/netflix/file-chunking.png)

这是我们处理管道的第一步。文件分块是将文件拆分为称为块的较小部分的过程。它可以帮助我们消除存储上的重复数据副本，并通过仅选择更改的块来减少通过网络发送的数据量。

通常，视频文件可以根据时间戳拆分为相等大小的块，但 Netflix 选择根据场景拆分块。这种细微的变化成为更好用户体验的巨大因素，因为每当客户端从服务器请求一个块时，中断的可能性较低，因为将检索到完整的场景。

- **内容过滤器**

此步骤检查视频是否符合平台的内容政策。这可以像 Netflix 一样根据媒体的[内容评级](https://en.wikipedia.org/wiki/Motion_picture_content_rating_system)预先批准，或者像 YouTube 一样严格执行。

整个过程由机器学习模型完成，该模型执行版权、盗版和 NSFW 检查。如果发现问题，我们可以将任务推送到[死信队列 (DLQ)](https://karanpratapsingh.com/courses/system-design/message-queues#dead-letter-queues)，由审核团队的成员进行进一步检查。

- **转码器**

[转码](https://en.wikipedia.org/wiki/Transcoding) 是一个过程，其中原始数据被解码为中间未压缩格式，然后编码为目标格式。此过程使用不同的[编解码器](https://en.wikipedia.org/wiki/Video_codec)执行比特率调整、图像降采样或重新编码媒体。

这会产生一个较小的文件，并为目标设备提供更优化的格式。可以使用独立解决方案（如 [FFmpeg](https://ffmpeg.org)）或基于云的解决方案（如 [AWS Elemental MediaConvert](https://aws.amazon.com/mediaconvert)）来实现管道的这一步骤。

- **质量转换**

这是处理管道的最后一步，顾名思义，此步骤处理将前一步骤中转码的媒体转换为不同的分辨率，如 4K、1440p、1080p、720p 等。

它允许我们根据用户的请求获取所需质量的视频，一旦媒体文件处理完成，它将被上传到分布式文件存储（如 [HDFS](https://karanpratapsingh.com/courses/system-design/storage#hdfs)、[GlusterFS](https://www.gluster.org)）或[对象存储](https://karanpratapsingh.com/courses/system-design/storage#object-storage)（如 [Amazon S3](https://aws.amazon.com/s3)）中，以便在流式传输期间进行检索。

_注意：我们可以将字幕和缩略图生成等其他步骤添加到我们的管道中。_

**为什么我们使用消息队列？**

将视频处理作为长时间运行的任务并使用[消息队列](https://karanpratapsingh.com/courses/system-design/message-queues)更有意义。它还将我们的视频处理管道与上传功能解耦。我们可以使用 [Amazon SQS](https://aws.amazon.com/sqs) 或 [RabbitMQ](https://www.rabbitmq.com) 来支持这一点。

### 视频流

从客户端和服务器的角度来看，视频流是一项具有挑战性的任务。此外，不同用户的互联网连接速度差异很大。为了确保用户不会重新获取相同的内容，我们可以使用[内容分发网络 (CDN)](https://karanpratapsingh.com/courses/system-design/content-delivery-network)。

Netflix 通过其 [Open Connect](https://openconnect.netflix.com) 计划更进一步。在这种方法中，他们与数千家互联网服务提供商 (ISP) 合作，以本地化其流量并更高效地交付其内容。

**Netflix 的 Open Connect 和传统的内容分发网络 (CDN) 有什么区别？**

Netflix Open Connect 是一个专门构建的[内容分发网络 (CDN)](https://karanpratapsingh.com/courses/system-design/content-delivery-network)，负责提供 Netflix 的视频流量。全球约 95% 的流量通过 Open Connect 和客户用来访问互联网的 ISP 之间的直接连接传递。

目前，他们在全球 1000 多个不同地点拥有 Open Connect 设备 (OCA)。在出现问题时，Open Connect 设备 (OCA) 可以故障转移，流量可以重新路由到 Netflix 服务器。

此外，我们可以使用[自适应比特率流](https://en.wikipedia.org/wiki/Adaptive_bitrate_streaming)协议，如[HTTP 实时流 (HLS)](https://en.wikipedia.org/wiki/HTTP_Live_Streaming)，该协议设计用于可靠性，并通过优化播放以适应可用的连接速度动态调整网络条件。

最后，为了从用户上次停止的地方播放视频（我们扩展需求的一部分），我们可以简单地使用我们存储在 [`views`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A113%2C%22character%22%3A2%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition") 表中的 [`offset`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A158%2C%22character%22%3A72%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition") 属性，在特定时间戳检索场景块并为用户恢复播放。

### 搜索

有时传统的 DBMS 性能不足，我们需要一些能够快速、近实时地存储、搜索和分析大量数据并在毫秒内返回结果的东西。[Elasticsearch](https://www.elastic.co) 可以帮助我们实现这一用例。

[Elasticsearch](https://www.elastic.co) 是一个分布式、免费和开放的搜索和分析引擎，适用于所有类型的数据，包括文本、数字、地理空间、结构化和非结构化数据。它构建在 [Apache Lucene](https://lucene.apache.org) 之上。

**我们如何识别热门内容？**

热门功能将基于搜索功能之上。我们可以缓存过去 [`N`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A313%2C%22character%22%3A136%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition") 秒内最频繁搜索的查询，并使用某种批处理机制每 [`M`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F12_netflix.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A313%2C%22character%22%3A170%7D%7D%5D%2C%2263ac956a-a592-4898-9153-9c4f7b7ec6a9%22%5D "Go to definition") 秒更新一次。

### 分享

分享内容是任何平台的重要组成部分，为此，我们可以设置某种 URL 缩短服务，为用户生成短链接以供分享。

_更多详细信息，请参考 [URL 缩短服务](https://karanpratapsingh.com/courses/system-design/url-shortener) 系统设计。_

## 详细设计

现在是详细讨论我们的设计决策的时候了。

### 数据分区

为了扩展我们的数据库，我们需要对数据进行分区。水平分区（也称为[分片](https://karanpratapsingh.com/courses/system-design/sharding)）可以是一个很好的第一步。我们可以使用以下分区方案：

- 基于哈希的分区
- 基于列表的分区
- 基于范围的分区
- 复合分区

上述方法仍可能导致数据和负载分布不均，我们可以使用[一致性哈希](https://karanpratapsingh.com/courses/system-design/consistent-hashing)来解决这个问题。

_更多详细信息，请参考 [分片](https://karanpratapsingh.com/courses/system-design/sharding) 和 [一致性哈希](https://karanpratapsingh.com/courses/system-design/consistent-hashing)。_

### 地理封锁

像 Netflix 和 YouTube 这样的平台使用[地理封锁](https://en.wikipedia.org/wiki/Geo-blocking)来限制某些地理区域或国家的内容。这主要是由于 Netflix 在与制作和发行公司达成协议时必须遵守的法律分发规定。在 YouTube 的情况下，这将由用户在发布内容时控制。

我们可以使用用户的 [IP](https://karanpratapsingh.com/courses/system-design/ip) 或其配置文件中的区域设置来确定用户的位置，然后使用支持地理限制功能的服务（如 [Amazon CloudFront](https://aws.amazon.com/cloudfront)）或具有[地理位置路由策略](https://docs.aws.amazon.com/Route53/latest/DeveloperGuide/routing-policy-geo.html)的 [Amazon Route53](https://aws.amazon.com/route53) 来限制内容，并在该特定区域或国家不可用时将用户重新路由到错误页面。

### 推荐

Netflix 使用机器学习模型，根据用户的观看历史预测用户可能想要观看的内容，可以使用类似[协同过滤](https://en.wikipedia.org/wiki/Collaborative_filtering)的算法。

然而，Netflix（像 YouTube 一样）使用自己的算法，称为 Netflix 推荐引擎，它可以跟踪多个数据点，如：

- 用户配置文件信息，如年龄、性别和位置。
- 用户的浏览和滚动行为。
- 用户观看标题的时间和日期。
- 用于流式传输内容的设备。
- 搜索次数和搜索的术语。

_更多详细信息，请参考 [Netflix 推荐研究](https://research.netflix.com/research-area/recommendations)。_

### 指标和分析

记录分析和指标是我们的扩展需求之一。我们可以从不同的服务中捕获数据，并使用 [Apache Spark](https://spark.apache.org) 运行数据分析，Apache Spark 是一个用于大规模数据处理的开源统一分析引擎。此外，我们可以在视图表中存储关键元数据，以增加数据点。

### 缓存

在流媒体平台中，缓存非常重要。我们必须能够缓存尽可能多的静态媒体内容，以改善用户体验。我们可以使用 [Redis](https://redis.io) 或 [Memcached](https://memcached.org) 等解决方案，但哪种缓存驱逐策略最适合我们的需求？

**使用哪种缓存驱逐策略？**

[最近最少使用 (LRU)](<https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)>) 可以是我们系统的一个好策略。在这种策略中，我们首先丢弃最近最少使用的键。

**如何处理缓存未命中？**

每当发生缓存未命中时，我们的服务器可以直接访问数据库并使用新条目更新缓存。

_更多详细信息，请参考 [缓存](https://karanpratapsingh.com/courses/system-design/caching)。_

### 媒体流和存储

由于我们的大部分存储空间将用于存储媒体文件，如缩略图和视频。根据我们之前的讨论，媒体服务将处理媒体文件的上传和处理。

我们将使用分布式文件存储，如 [HDFS](https://karanpratapsingh.com/courses/system-design/storage#hdfs)、[GlusterFS](https://www.gluster.org) 或 [对象存储](https://karanpratapsingh.com/courses/system-design/storage#object-storage)（如 [Amazon S3](https://aws.amazon.com/s3)）来存储和流式传输内容。

### 内容分发网络 (CDN)

[内容分发网络 (CDN)](https://karanpratapsingh.com/courses/system-design/content-delivery-network) 增加了内容的可用性和冗余性，同时降低了带宽成本。通常，静态文件如图像和视频是从 CDN 提供的。我们可以使用 [Amazon CloudFront](https://aws.amazon.com/cloudfront) 或 [Cloudflare CDN](https://www.cloudflare.com/cdn) 等服务来实现这一用例。

## 识别和解决瓶颈

![netflix-advanced-design](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/netflix/netflix-advanced-design.png)

让我们识别和解决设计中的瓶颈，如单点故障：

- “如果我们的某个服务崩溃了怎么办？”
- “我们将如何在组件之间分配流量？”
- “我们如何减少数据库的负载？”
- “如何提高缓存的可用性？”

为了使我们的系统更具弹性，我们可以采取以下措施：

- 运行每个服务的多个实例。
- 在客户端、服务器、数据库和缓存服务器之间引入[负载均衡器](https://karanpratapsingh.com/courses/system-design/load-balancing)。
- 为我们的数据库使用多个只读副本。
- 为我们的分布式缓存使用多个实例和副本。