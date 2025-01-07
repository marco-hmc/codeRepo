### DevOps vs. SRE vs. 平台工程。有什么区别？

<p>
  <img src="images/devops-sre-platform.jpg" />
</p>

SRE，即站点可靠性工程，是由 Google 在 2000 年代初期提出的，旨在解决管理大规模复杂系统的运营挑战。Google 开发了 SRE 实践和工具，如 Borg 集群管理系统和 Monarch 监控系统，以提高其服务的可靠性和效率。

平台工程是一个较新的概念，建立在 SRE 工程的基础上。平台工程的具体起源不太明确，但通常被认为是 DevOps 和 SRE 实践的延伸，重点是提供一个全面的平台，支持整个业务视角的产品开发。

值得注意的是，虽然这些概念在不同的时间出现，但它们都与提高软件开发和运营中的协作、自动化和效率的趋势有关。

### 什么是 k8s（Kubernetes）？

K8s 是一个容器编排系统，用于容器的部署和管理。它的设计深受 Google 内部系统 Borg 的影响。

<p>
  <img src="images/k8s.jpeg" style="width: 680px" />
</p>

一个 k8s 集群由一组称为节点的工作机器组成，这些节点运行容器化的应用程序。每个集群至少有一个工作节点。

工作节点托管作为应用程序工作负载组件的 Pod。控制平面管理集群中的工作节点和 Pod。在生产环境中，控制平面通常跨多台计算机运行，而一个集群通常运行多个节点，以提供容错和高可用性。

- 控制平面组件
1. API 服务器
    API 服务器与 k8s 集群中的所有组件通信。所有对 Pod 的操作都是通过与 API 服务器通信来执行的。
2. 调度器
    调度器监视 Pod 的工作负载，并将负载分配给新创建的 Pod。
3. 控制器管理器
    控制器管理器运行控制器，包括节点控制器、作业控制器、EndpointSlice 控制器和 ServiceAccount 控制器。
4. Etcd
    etcd 是一个键值存储，用作 Kubernetes 的所有集群数据的后备存储。

- 节点
1. Pod
    Pod 是一组容器，是 k8s 管理的最小单位。Pod 具有一个单一的 IP 地址，应用于 Pod 内的每个容器。
2. Kubelet
    Kubelet 是在集群中每个节点上运行的代理。它确保容器在 Pod 中运行。
3. Kube Proxy
    Kube-proxy 是在集群中每个节点上运行的网络代理。它将进入节点的流量路由到服务，并将工作请求转发到正确的容器。

### Docker vs. Kubernetes。我们应该使用哪个？

<p>
  <img src="images/docker-vs-k8s.jpg" style="width: 680px" />
</p>

什么是 Docker？

Docker 是一个开源平台，允许你在隔离的容器中打包、分发和运行应用程序。它专注于容器化，提供封装应用程序及其依赖项的轻量级环境。

什么是 Kubernetes？

Kubernetes，通常简称为 K8s，是一个开源的容器编排平台。它提供了一个框架，用于自动化容器化应用程序在集群中的部署、扩展和管理。

两者有何不同？

Docker：Docker 在单个操作系统主机上操作单个容器。

你必须手动管理每个主机，并为多个相关容器设置网络、安全策略和存储可能会很复杂。

Kubernetes：Kubernetes 在集群级别操作。它管理跨多个主机的多个容器化应用程序，提供负载均衡、扩展和确保应用程序所需状态的自动化。

简而言之，Docker 专注于容器化和在单个主机上运行容器，而 Kubernetes 专注于在集群中管理和编排容器。

### Docker 如何工作？

下图显示了 Docker 的架构以及当我们运行 “docker build”、“docker pull”和“docker run” 时它是如何工作的。

<p>
  <img src="images/docker.jpg" style="width: 680px" />
</p>

Docker 架构中有 3 个组件：

- Docker 客户端
    Docker 客户端与 Docker 守护进程通信。

- Docker 主机
    Docker 守护进程监听 Docker API 请求，并管理 Docker 对象，如镜像、容器、网络和卷。

- Docker 注册表
    Docker 注册表存储 Docker 镜像。Docker Hub 是一个任何人都可以使用的公共注册表。

让我们以 “docker run” 命令为例。

1. Docker 从注册表中拉取镜像。
2. Docker 创建一个新的容器。
3. Docker 为容器分配一个读写文件系统。
4. Docker 创建一个网络接口，将容器连接到默认网络。
5. Docker 启动容器。