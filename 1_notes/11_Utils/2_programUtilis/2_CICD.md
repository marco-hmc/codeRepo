## CI/CD

### 1. concepts

#### 1.1 什么是CI/CD
![alt text](_imgs/2_CICD_image-1.png)

![alt text](_imgs/2_CICD_image.png)

### 规划
Netflix 工程团队使用 JIRA 进行规划，并使用 Confluence 进行文档编写。

### 编码
Java 是后端服务的主要编程语言，同时也使用其他语言来应对不同的使用场景。

### 构建
主要使用 Gradle 进行构建，并且构建了支持各种使用场景的 Gradle 插件。

### 打包
将包和依赖项打包成 Amazon Machine Image (AMI) 以进行发布。

### 测试
测试强调生产文化中的混沌工具构建。

### 部署
Netflix 使用自建的 Spinnaker 进行金丝雀发布部署。

### 监控
监控指标集中在 Atlas 中，并使用 Kayenta 检测异常。

### 事件报告
事件根据优先级进行分派，并使用 PagerDuty 处理事件。