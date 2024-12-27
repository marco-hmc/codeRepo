# Uber

让我们设计一个类似于 [Uber](https://uber.com) 的叫车服务，类似于 [Lyft](https://www.lyft.com)、[OLA Cabs](https://www.olacabs.com) 等服务。

## 什么是 Uber？

Uber 是一个移动服务提供商，允许用户预订车辆并由司机接送，类似于出租车服务。它可以在网页和移动平台（如 Android 和 iOS）上使用。

## 需求

我们的系统应满足以下需求：

### 功能需求

我们将为两类用户设计系统：客户和司机。

**客户**

- 客户应该能够看到附近所有的出租车，并获取预计到达时间和价格信息。
- 客户应该能够预订一辆车到达目的地。
- 客户应该能够看到司机的位置。

**司机**

- 司机应该能够接受或拒绝客户请求的行程。
- 一旦司机接受了行程，他们应该能够看到客户的接送地点。
- 司机应该能够在到达目的地后标记行程完成。

### 非功能需求

- 高可靠性。
- 高可用性和低延迟。
- 系统应具有可扩展性和高效性。

### 扩展需求

- 客户可以在行程结束后对行程进行评分。
- 支付处理。
- 指标和分析。

## 估算和约束

让我们从估算和约束开始。

_注意：确保与面试官确认任何与规模或流量相关的假设。_

### 流量

假设我们有 1 亿日活跃用户（DAU），其中有 100 万司机，平均每天完成 1000 万次行程。

如果平均每个用户执行 10 次操作（如请求查看可用车辆、查询价格、预订行程等），我们每天需要处理 10 亿次请求。

$$
100 \space million \times 10 \space actions = 1 \space billion/day
$$

**我们的系统每秒请求数（RPS）是多少？**

每天 10 亿次请求相当于每秒 12K 次请求。

$$
\frac{1 \space billion}{(24 \space hrs \times 3600 \space seconds)} = \sim 12K \space requests/second
$$

### 存储

如果我们假设每条消息平均为 400 字节，我们每天需要大约 400 GB 的数据库存储。

$$
1 \space billion \times 400 \space bytes = \sim 400 \space GB/day
$$

在 10 年内，我们将需要大约 1.4 PB 的存储空间。

$$
400 \space GB \times 10 \space years \times 365 \space days = \sim 1.4 \space PB
$$

### 带宽

由于我们的系统每天处理 400 GB 的数据输入，我们需要大约 5 MB 每秒的最小带宽。

$$
\frac{400 \space GB}{(24 \space hrs \times 3600 \space seconds)} = \sim 5 \space MB/second
$$

### 高级估算

以下是我们的高级估算：

| 类型                      | 估算        |
| ------------------------- | ----------- |
| 日活跃用户（DAU）         | 1 亿        |
| 每秒请求数（RPS）         | 12K/s       |
| 每日存储                  | ~400 GB     |
| 10 年存储                 | ~1.4 PB     |
| 带宽                      | ~5 MB/s     |

## 数据模型设计

这是反映我们需求的一般数据模型。

![uber-datamodel](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/uber/uber-datamodel.png)

我们有以下表格：

**customers**

此表将包含客户的信息，如 [`name`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A108%2C%22character%22%3A58%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")、[`email`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A108%2C%22character%22%3A66%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition") 和其他详细信息。

**drivers**

此表将包含司机的信息，如 [`name`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A108%2C%22character%22%3A58%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")、[`email`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A108%2C%22character%22%3A66%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")、[`dob`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A112%2C%22character%22%3A73%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition") 和其他详细信息。

**trips**

此表表示客户进行的行程，并存储行程的 [`source`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A116%2C%22character%22%3A78%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")、[`destination`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A19%2C%22character%22%3A46%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition") 和 [`status`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A116%2C%22character%22%3A107%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition") 等数据。

**cabs**

此表存储司机驾驶的车辆的注册号和类型（如 Uber Go、Uber XL 等）。

**ratings**

顾名思义，此表存储行程的 [`rating`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A124%2C%22character%22%3A45%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition") 和 [`feedback`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A124%2C%22character%22%3A58%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")。

**payments**

支付表包含与相应 [`tripID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A128%2C%22character%22%3A77%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition") 相关的支付数据。

### 我们应该使用哪种数据库？

虽然我们的数据模型看起来相当关系型，但我们不一定需要将所有内容存储在单个数据库中，因为这会限制我们的可扩展性并迅速成为瓶颈。

我们将数据分散到不同的服务中，每个服务拥有特定表的所有权。然后我们可以根据我们的用例使用关系数据库（如 [PostgreSQL](https://www.postgresql.org)）或分布式 NoSQL 数据库（如 [Apache Cassandra](https://cassandra.apache.org/_/index.html)）。

## API 设计

让我们为我们的服务做一个基本的 API 设计：

### 请求行程

通过此 API，客户将能够请求行程。

```tsx
requestRide(customerID: UUID, source: Tuple<float>, destination: Tuple<float>, cabType: Enum<string>, paymentMethod: Enum<string>): Ride
```

**参数**

客户 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A24%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 客户的 ID。

起点 (`Tuple<float>`): 包含行程起点纬度和经度的元组。

终点 (`Tuple<float>`): 包含行程终点纬度和经度的元组。

**返回**

结果 ([`Ride`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A140%2C%22character%22%3A14%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 行程的相关信息。

### 取消行程

此 API 将允许客户取消行程。

```tsx
cancelRide(customerID: UUID, reason?: string): boolean
```

**参数**

客户 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A24%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 客户的 ID。

原因 ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A24%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 取消行程的原因 _(可选)_。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A165%2C%22character%22%3A47%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 表示操作是否成功。

### 接受或拒绝行程

此 API 将允许司机接受或拒绝行程。

```tsx
acceptRide(driverID: UUID, rideID: UUID): boolean
denyRide(driverID: UUID, rideID: UUID): boolean
```

**参数**

司机 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A24%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 司机的 ID。

行程 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A24%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 客户请求的行程 ID。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A165%2C%22character%22%3A47%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 表示操作是否成功。

### 开始或结束行程

使用此 API，司机将能够开始和结束行程。

```tsx
startTrip(driverID: UUID, tripID: UUID): boolean
endTrip(driverID: UUID, tripID: UUID): boolean
```

**参数**

司机 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A24%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 司机的 ID。

行程 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A24%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 请求的行程 ID。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A165%2C%22character%22%3A47%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 表示操作是否成功。

### 评价行程

此 API 将使客户能够评价行程。

```tsx
rateTrip(customerID: UUID, tripID: UUID, rating: int, feedback?: string): boolean
```

**参数**

客户 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A24%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 客户的 ID。

行程 ID ([`UUID`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A24%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 完成的行程 ID。

评分 ([`int`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A221%2C%22character%22%3A49%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 行程的评分。

反馈 ([`string`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A145%2C%22character%22%3A93%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 客户对行程的反馈 _(可选)_。

**返回**

结果 ([`boolean`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A165%2C%22character%22%3A47%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")): 表示操作是否成功。

## 高级设计

现在让我们对我们的系统进行高级设计。

### 架构

我们将使用 [微服务架构](https://karanpratapsingh.com/courses/system-design/monoliths-microservices#microservices)，因为它将使水平扩展和解耦我们的服务变得更容易。每个服务将拥有自己的数据模型。让我们尝试将我们的系统划分为一些核心服务。

**客户服务**

此服务处理与客户相关的事务，如身份验证和客户信息。

**司机服务**

此服务处理与司机相关的事务，如身份验证和司机信息。

**行程服务**

此服务将负责行程匹配和四叉树聚合。我们将单独详细讨论它。

**旅行服务**

此服务处理系统中的旅行相关功能。

**支付服务**

此服务将负责处理系统中的支付。

**通知服务**

此服务将向用户发送推送通知。我们将单独详细讨论它。

**分析服务**

此服务将用于指标和分析用例。

**服务间通信和服务发现怎么办？**

由于我们的架构是基于微服务的，服务之间也将进行通信。通常，REST 或 HTTP 表现良好，但我们可以使用更轻量级和高效的 [gRPC](https://karanpratapsingh.com/courses/system-design/rest-graphql-grpc#grpc) 进一步提高性能。

[服务发现](https://karanpratapsingh.com/courses/system-design/service-discovery) 是我们需要考虑的另一个问题。我们还可以使用服务网格来实现各个服务之间的管理、可观察和安全通信。

_注意：了解更多关于 [REST、GraphQL、gRPC](https://karanpratapsingh.com/courses/system-design/rest-graphql-grpc) 以及它们之间的比较。_

### 服务预期如何工作？

以下是我们的服务预期工作方式：

![uber-working](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/uber/uber-working.png)

1. 客户通过指定起点、终点、车辆类型、支付方式等请求行程。
2. 行程服务注册此请求，找到附近的司机，并计算预计到达时间（ETA）。
3. 然后请求广播给附近的司机，供他们接受或拒绝。
4. 如果司机接受，客户将收到司机的实时位置和预计到达时间（ETA）的通知，同时等待接送。
5. 客户被接送后，司机可以开始行程。
6. 一旦到达目的地，司机将标记行程完成并收取费用。
7. 支付完成后，客户可以对行程进行评分和反馈。

### 位置跟踪

我们如何高效地从客户端（客户和司机）向我们的后端发送和接收实时位置数据？我们有两种不同的选择：

**拉取模型**

客户端可以定期发送 HTTP 请求到服务器，报告其当前位置并接收预计到达时间和价格信息。这可以通过类似 [长轮询](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#long-polling) 的方式实现。

**推送模型**

客户端与服务器建立一个长连接，一旦有新数据可用，它将被推送到客户端。我们可以使用 [WebSockets](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#websockets) 或 [服务器发送事件 (SSE)](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#server-sent-events-sse) 来实现这一点。

拉取模型方法不可扩展，因为它会在我们的服务器上创建不必要的请求开销，并且大多数时候响应将为空，从而浪费我们的资源。为了最小化延迟，使用 [WebSockets](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#websockets) 的推送模型是更好的选择，因为这样我们可以在数据可用时立即将其推送到客户端，只要与客户端的连接是打开的。此外，WebSockets 提供全双工通信，而 [服务器发送事件 (SSE)](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events#server-sent-events-sse) 仅是单向的。

此外，客户端应用程序应具有某种后台任务机制，以在应用程序在后台时发送 GPS 位置。

_注意：了解更多关于 [长轮询、WebSockets、服务器发送事件 (SSE)](https://karanpratapsingh.com/courses/system-design/long-polling-websockets-server-sent-events)。_

### 行程匹配

我们需要一种高效存储和查询附近司机的方法。让我们探索可以纳入我们设计的不同解决方案。

**SQL**

我们已经可以访问客户的纬度和经度，并且使用像 [PostgreSQL](https://www.postgresql.org) 和 [MySQL](https://www.mysql.com) 这样的数据库，我们可以执行查询以在给定的纬度和经度 (X, Y) 范围内找到附近的司机位置。

```sql
SELECT * FROM locations WHERE lat BETWEEN X-R AND X+R AND long BETWEEN Y-R AND Y+R
```

然而，这种方法不可扩展，在大数据集上执行此查询会非常慢。

**地理哈希**

[地理哈希](https://karanpratapsingh.com/courses/system-design/geohashing-and-quadtrees#geohashing) 是一种用于将地理坐标（如纬度和经度）编码为短字母数字字符串的 [地理编码](https://en.wikipedia.org/wiki/Address_geocoding) 方法。它由 [Gustavo Niemeyer](https://twitter.com/gniemeyer) 于 2008 年创建。

地理哈希是一种分层空间索引，使用 Base-32 字母编码，地理哈希中的第一个字符将初始位置标识为 32 个单元之一。这个单元还包含 32 个单元。这意味着要表示一个点，世界被递归地划分为越来越小的单元，每增加一位直到达到所需的精度。精度因子还决定了单元的大小。

![geohashing](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-IV/geohashing-and-quadtrees/geohashing.png)

例如，坐标为 `37.7564, -122.4016` 的旧金山可以用地理哈希表示为 [`9q8yy9mf`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fmarco%2FgitRepo%2FcodeRepo%2F1_notes%2F6_%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%2F2_frameworkDesign%2F0_businessDesign%2F11_uber.md%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A336%2C%22character%22%3A99%7D%7D%5D%2C%22d488ee98-517e-4c9e-9fe6-417e2a7db793%22%5D "Go to definition")。

现在，使用客户的地理哈希，我们可以通过简单地将其与司机的地理哈希进行比较来确定最近的可用司机。为了更好的性能，我们将司机的地理哈希索引并存储在内存中，以便更快地检索。

**四叉树**

[四叉树](https://karanpratapsingh.com/courses/system-design/geohashing-and-quadtrees#quadtrees) 是一种树数据结构，其中每个内部节点恰好有四个子节点。它们通常用于通过递归将二维空间划分为四个象限或区域来进行分区。每个子节点或叶节点存储空间信息。四叉树是用于分区三维空间的 [八叉树](https://en.wikipedia.org/wiki/Octree) 的二维类比。

![quadtree](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-IV/geohashing-and-quadtrees/quadtree.png)

四叉树使我们能够高效地在二维范围内搜索点，这些点定义为纬度/经度坐标或笛卡尔 (x, y) 坐标。

我们可以通过仅在达到某个阈值后细分节点来节省进一步的计算。

![quadtree-subdivision](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-IV/geohashing-and-quadtrees/quadtree-subdivision.png)

[四叉树](https://karanpratapsingh.com/courses/system-design/geohashing-and-quadtrees#quadtrees) 似乎非常适合我们的用例，我们可以在每次收到司机的新位置更新时更新四叉树。为了减少四叉树服务器的负载，我们可以使用像 [Redis](https://redis.io) 这样的内存数据存储来缓存最新的更新。通过应用 [Hilbert 曲线](https://en.wikipedia.org/wiki/Hilbert_curve) 等映射算法，我们可以执行高效的范围查询，以找到客户附近的司机。

**竞争条件怎么办？**

当大量客户同时请求行程时，竞争条件很容易发生。为避免这种情况，我们可以将我们的行程匹配逻辑包装在 互斥锁>) 中，以避免任何竞争条件。此外，每个操作都应具有事务性。

_有关更多详细信息，请参阅 [事务](https://karanpratapsingh.com/courses/system-design/transactions) 和 [分布式事务](https://karanpratapsingh.com/courses/system-design/distributed-transactions)。_

**如何找到附近最好的司机？**

一旦我们从四叉树服务器获得了附近司机的列表，我们可以根据平均评分、相关性、过去客户反馈等参数进行某种排序。这将使我们能够首先向最好的可用司机广播通知。

**应对高需求**

在高需求的情况下，我们可以使用动态定价的概念。动态定价是一种动态定价方法，当需求增加且供应有限时，价格会暂时上涨。这个动态价格可以添加到行程的基本价格中。

_有关更多详细信息，请了解 [Uber 的动态定价如何工作](https://www.uber.com/us/en/drive/driver-app/how-surge-works)。_

### 支付

在大规模处理支付是具有挑战性的，为简化我们的系统，我们可以使用第三方支付处理器，如 [Stripe](https://stripe.com) 或 [PayPal](https://www.paypal.com)。一旦支付完成，支付处理器将用户重定向回我们的应用程序，我们可以设置一个 [Webhook](https://en.wikipedia.org/wiki/Webhook) 来捕获所有与支付相关的数据。

### 通知

推送通知将是我们平台的重要组成部分。我们可以使用消息队列或消息代理（如 [Apache Kafka](https://kafka.apache.org)）与通知服务一起，将请求分发到 [Firebase Cloud Messaging (FCM)](https://firebase.google.com/docs/cloud-messaging) 或 [Apple Push Notification Service (APNS)](https://developer.apple.com/documentation/usernotifications)，这些服务将处理推送通知的发送到用户设备。

_更多详细信息，请参考 [WhatsApp](https://karanpratapsingh.com/courses/system-design/whatsapp#notifications) 系统设计，其中我们详细讨论了推送通知。_

## 详细设计

现在是详细讨论我们的设计决策的时候了。

### 数据分区

为了扩展我们的数据库，我们需要对数据进行分区。水平分区（也称为 [Sharding](https://karanpratapsingh.com/courses/system-design/sharding)）可以是一个很好的第一步。我们可以根据现有的 [分区方案](https://karanpratapsingh.com/courses/system-design/sharding#partitioning-criteria) 或区域对数据库进行分片。如果我们使用邮政编码将位置划分为区域，我们可以有效地将给定区域的所有数据存储在一个固定节点上。但这仍然可能导致数据和负载分布不均，我们可以使用 [一致性哈希](https://karanpratapsingh.com/courses/system-design/consistent-hashing) 来解决这个问题。

_更多详细信息，请参考 [Sharding](https://karanpratapsingh.com/courses/system-design/sharding) 和 [一致性哈希](https://karanpratapsingh.com/courses/system-design/consistent-hashing)。_

### 指标和分析

记录分析和指标是我们的扩展需求之一。我们可以从不同的服务中捕获数据，并使用 [Apache Spark](https://spark.apache.org) 运行数据分析，Apache Spark 是一个用于大规模数据处理的开源统一分析引擎。此外，我们可以在视图表中存储关键元数据，以增加数据点。

### 缓存

在基于位置服务的平台中，缓存非常重要。我们必须能够缓存客户和司机的最近位置，以便快速检索。我们可以使用 [Redis](https://redis.io) 或 [Memcached](https://memcached.org) 等解决方案，但哪种缓存驱逐策略最适合我们的需求？

**使用哪种缓存驱逐策略？**

[最近最少使用 (LRU)](<https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)>) 可以是我们系统的一个好策略。在这种策略中，我们首先丢弃最近最少使用的键。

**如何处理缓存未命中？**

每当发生缓存未命中时，我们的服务器可以直接访问数据库并使用新条目更新缓存。

_更多详细信息，请参考 [缓存](https://karanpratapsingh.com/courses/system-design/caching)。_

## 识别和解决瓶颈

![uber-advanced-design](https://raw.githubusercontent.com/karanpratapsingh/portfolio/master/public/static/courses/system-design/chapter-V/uber/uber-advanced-design.png)

让我们识别和解决设计中的瓶颈，如单点故障：

- “如果我们的某个服务崩溃了怎么办？”
- “我们将如何在组件之间分配流量？”
- “我们如何减少数据库的负载？”
- “如何提高缓存的可用性？”
- “我们如何使通知系统更健壮？”

为了使我们的系统更具弹性，我们可以采取以下措施：

- 运行每个服务的多个实例。
- 在客户端、服务器、数据库和缓存服务器之间引入[负载均衡器](https://karanpratapsingh.com/courses/system-design/load-balancing)。
- 为我们的数据库使用多个只读副本。
- 为我们的分布式缓存使用多个实例和副本。
- 在分布式系统中，确保消息的“恰好一次”投递和消息排序是具有挑战性的，我们可以使用专用的[消息代理](https://karanpratapsingh.com/courses/system-design/message-brokers)（如 [Apache Kafka](https://kafka.apache.org) 或 [NATS](https://nats.io)）来使我们的通知系统更健壮。