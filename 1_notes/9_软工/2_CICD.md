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

### Monorepo vs. Microrepo

哪种方式更好？为什么不同公司选择不同的选项？

  ![text](_imgs/monorepo-microrepo.jpg)

Monorepo 并不是新概念；Linux 和 Windows 都是使用 Monorepo 创建的。为了提高可扩展性和构建速度，Google 开发了内部专用工具链，以更快地扩展，并制定了严格的代码质量标准以保持一致性。

Amazon 和 Netflix 是微服务哲学的主要倡导者。这种方法自然地将服务代码分离到不同的存储库中。它扩展得更快，但可能会导致后期的治理问题。

在 Monorepo 中，每个服务是一个文件夹，每个文件夹都有一个 BUILD 配置和 OWNERS 权限控制。每个服务成员负责自己的文件夹。

另一方面，在 Microrepo 中，每个服务负责其存储库，构建配置和权限通常设置为整个存储库。

在 Monorepo 中，依赖项在整个代码库中共享，因此当有版本升级时，所有代码库都会升级其版本。

在 Microrepo 中，依赖项在每个存储库中受到控制。业务根据自己的时间表选择何时升级版本。

Monorepo 有一个标准的提交流程。Google 的代码审查过程以高标准著称，确保 Monorepo 的一致质量标准，无论业务如何。

Microrepo 可以设置自己的标准或通过采用最佳实践来共享标准。它可以更快地扩展业务，但代码质量可能会有所不同。Google 工程师构建了 Bazel，Meta 构建了 Buck。还有其他开源工具，包括 Nx、Lerna 等。

多年来，Microrepo 有更多支持的工具，包括 Java 的 Maven 和 Gradle，NodeJS 的 NPM，以及 C/C++ 的 CMake 等。

