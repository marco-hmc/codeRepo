## 对象池

### 1. concepts

#### 1.1 对象池的意义
对象池（Object Pool Pattern）是一种创建型设计模式，其核心思想是预先创建一组对象并存储在池中，当需要使用对象时，不是通过新建实例的方式，而是从池中获取已经创建的对象实例。使用完毕后，对象被返回到池中以便再次使用。这种模式的主要优点包括：

1. **性能提升**：减少对象创建和销毁的开销，特别是在对象初始化成本高或创建频繁的场景下。
2. **资源利用率提高**：通过重用对象，减少内存分配和垃圾回收的压力。
3. **内存优化**：减少内存碎片，提高内存使用率。
4. **控制对象生命周期**：更精细地控制对象的创建和销毁时机。

#### 1.2 对象池适用场景
对象池适用于以下场景：
1. **对象创建成本高**：如数据库连接、网络连接、线程等。
2. **对象创建频繁**：如游戏中的子弹、敌人等。
3. **对象数量受限**：如某些资源受限的情况，需要控制最大并发数量。
4. **对象复用价值高**：对象可以被重复使用，且状态可以在使用后恢复。

#### 1.3 如何实现？实现的关键是什么？
实现对象池的关键步骤包括：
1. **对象创建与管理**：实现一个对象池类，负责对象的创建、存储和回收。
2. **线程安全**：确保对象池的操作在多线程环境下是安全的。
3. **对象状态管理**：确保返回池中的对象处于可重用状态。
4. **池的大小控制**：合理设置对象池的最大和最小容量。

实现的关键点：
- **对象池的初始化**：根据需要预创建一定数量的对象。
- **对象的获取与释放**：提供接口供外部获取和释放对象。
- **对象的有效性检查**：在对象被借出和归还时进行检查，确保对象状态。
- **池的监控与调整**：根据使用情况动态调整池的大小。

#### 1.4 对于不同对象类型，如何实现池化？
对于不同对象类型的池化，可以采用以下策略：

1. **泛型对象池**：使用泛型实现一个通用的对象池类，可以适用于多种类型的对象。
2. **工厂模式**：为每种类型的对象提供一个工厂类，用于创建和管理特定类型的对象。
3. **字典或映射管理**：使用字典或映射结构来管理不同类型的对象池，键为对象类型，值为对应的对象池实例。
4. **策略模式**：定义一个对象池接口，为每种类型的对象实现一个具体的策略类，实现特定的创建和销毁逻辑。

通过这些策略，可以实现一个灵活且可扩展的对象池系统，以适应不同类型对象的池化需求。

### 99. quiz
#### 1. 如何理解new的开销？如何理解placement new的开销？
* **`new` 的开销**
    1. **内存分配**：
    - `new` 操作符在堆上分配内存，这涉及到操作系统的内存管理机制。
    - 内存分配可能会导致内存碎片化，特别是在频繁分配和释放内存的情况下。
    2. **构造函数调用**：
    - `new` 操作符不仅分配内存，还会调用对象的构造函数进行初始化。
    - 构造函数的执行时间取决于对象的初始化逻辑。
    3. **线程安全**：
    - 在多线程环境中，内存分配需要进行线程同步，以确保分配操作的安全性。
    - 线程同步会增加额外的开销。

* **`placement new` 的开销**
    1. **内存分配**：
    - `placement new` 不会在堆上分配内存，而是使用预先分配好的内存。
    - 这避免了内存分配的开销，但需要确保预先分配的内存足够大且对齐正确。
    2. **构造函数调用**：
    - `placement new` 仍然会调用对象的构造函数进行初始化。
    - 构造函数的执行时间与普通 `new` 操作符相同。
    3. **内存管理**：
    - 使用 `placement new` 时，开发者需要手动管理内存，包括分配和释放。
    - 这增加了代码的复杂性，但可以提高性能。

* **总结**
    - **`new` 的开销**：
        - 内存分配：涉及操作系统的内存管理机制，可能导致内存碎片化。
        - 构造函数调用：初始化对象，执行时间取决于初始化逻辑。
        - 线程安全：在多线程环境中需要进行线程同步，增加额外开销。
    - **`placement new` 的开销**：
        - 内存分配：使用预先分配好的内存，避免了内存分配的开销。
        - 构造函数调用：仍然会调用对象的构造函数进行初始化。
        - 内存管理：需要手动管理内存，包括分配和释放，增加代码复杂性。


### 
未整理
对象池是一种设计模式，它会预先初始化一组可重用的实体，而不是按需销毁然后重建。在使用套接字描述符时，人们通常会将其池化。实际上，套接字描述符的数量通常比较少(最多上千个)，之所以要采用池的方式，是因为它们的初始化成本非常高。而在最近发表的一篇博文中，ClojureWerkz核心成员Alex Petrov探讨了另一种对象池应用场景，即将大量的存活期短且初始化成本低的对象池化，以降低内存分配和再分配成本，避免内存碎片。

Alex将对象池看作是减少GC压力的首选方法，同时也是最简单的方法。在下面两种分配模式下，可以选择使用对象池：

对象以固定的速度不断地分配，垃圾收集时间逐步增加，内存使用率随之增大；

对象分配存在爆发期，而每次爆发都会导致系统迟滞，并伴有明显的GC中断。

在绝大多数情况下，这些对象要么是数据容器，要么是数据封装器，其作用是在应用程序和内部消息总线、通信层或某些API之间充当一个信封。这很常见。例如，数据库驱动会针对每个请求和响应创建Request和Response对象，消息系统会使用Message和Event封装器，等等。对象池可以帮助保存和重用这些构造好的对象实例。

Alex介绍了两种基本的对象池回收模式：“借用(borrowing)”和引用计数。前者更清晰，而后者则意味着要实现自动回收。

借用非常像垃圾收集运行时之上的malloc/free。自然地，在使用这种方式时，开发人员需要面对早先使用非垃圾收集语言时面对的问题。如果某个对象已经释放并返回到池中，那么任何对它的修改或读取都会产生不可预见的结果。例如，在C语言中，对已释放的指针进行任何操作都会产生块错误。借用适用于有明确的开始/结束点的操作。绝大多数时候，都不要将它用于对象可以被多个线程同步访问的情况。借用最大的优点是，它不知道对象池的存在。被借用的对象本身要有某种reset机制，借用和返回操作都由对象消费者完成。

引用计数在实现方面稍微复杂些，但它对数据结构提供了更细粒度的控制。将对象池封装到一个函数式接口中，消费者就可以不必了解它，就像下面这个样子：

(pooledObject, pooledObjectConsumer) -> { pooledObject.retain(); pooledObjectConsumer.accept(pooledObject); pooledObject.release(); };

每当对象进入上述代码块，调用者就会retain该对象，并在执行块执行完毕后将其release。每个对象都持有一个内部计数器和一个指向池的引用。当计数器为0时，对象就会返回池中。

通常，引用计数用于同时有多个消费者访问已分配对象的情况，只有当所有的消费者都释放了对象引用时，对象才可以被回收。这种方式也适用于管道或嵌套处理。在这种情况下，开发者可以避免显式的开始/结束操作。

分配触发负责在池中对象不足时分配新资源。Alex介绍了如下三种分配触发方式：

空池触发：任何时候，只要池空了，就分配对象。这是一种最简单的方式。

水位线：空池触发的缺点是，某次对象请求会因为执行对象分配而中断。为了避免这种情况，可以使用水位线触发。当从池中请求新对象时，检查池中可用对象的数量。如果可用对象小于某个阈值，就触发分配过程。

Lease/Return速度：大多数时候，水位线触发已经足够，但有时候可能会需要更高的精度。在这种情况下，可以使用lease和return速度。例如，如果池中有100个对象，每秒有20个对象被取走，但只有10个对象返回，那么9秒后池就空了。开发者可以使用这种信息，提前做好对象分配计划。

增长策略用于指定分配过程被触发后需要分配的对象的数量。Alex也介绍了三种方式：

固定大小：这是最简单的对象池实现方式。对象一次性预分配，对象池后续不再增长。这种实现适用于对象数量相对确定的情况，但池大小固定可能会导致资源饥饿。

小步增长：为了避免出现资源饥饿，可以允许对象池小步增长，比如一次额外分配一个对象。

块增长：如果无法接受分配导致的中断，就需要保证池中任何时候都有可用的对象。这时，就必须使用块增长。例如，每当水位线到达25%时，就将对象池增大25%。不过，这种方式容易导致内存溢出。搭配Lease/Return速度分配触发策略，可以得出更准确的池大小。

当然，使用对象池就意味着开发者开始自己管理内存，所以需要注意以下问题：

引用泄露：对象在系统中某个地方注册了，但没有返回到池中。

过早回收：消费者已经决定将对象返还给对象池，但仍然持有它的引用，并试图执行写或读操作，这时会出现这种情况。

隐式回收：当使用引用计数时可能会出现这种情况。

大小错误：这种情况在使用字节缓冲区和数组时非常常见：对象应该有不同的大小，而且是以定制的方式构造，但返回对象池后却作为通用对象重用。

重复下单：这是引用泄露的一个变种，存在多路复用时特别容易发生：一个对象被分配到多个地方，但其中一个地方释放了该对象。

就地修改：对象不可变是最好的，但如果不具备那样做的条件，就可能在读取对象内容时遇到内容被修改的问题。

缩小对象池：当池中有大量的未使用对象时，要缩小对象池。

对象重新初始化：确保每次从池中取得的对象不含有上次使用时留下的脏字段。

最后，Alex指出：

对象池并不适合所有人。在应用程序开发的早期阶段就开始使用对象池是没有意义的，因为你那时候还不能确切地知道什么需要池化，也不确定如何池化。

Unity作为一款强大的游戏引擎，提供了丰富的框架和工具，其中对象池框架是开发中不可或缺的重要组成部分。对象池的概念在游戏开发中被广泛应用，其主要目的是提高性能和优化内存管理。本文将深入探讨Unity中的对象池框架，解释其重要性以及如何有效地使用它。

什么是对象池框架？

对象池是一种用于重复利用游戏对象的机制，而对象池框架则是在Unity中实现和管理这种机制的工具。在游戏中，特别是在需要频繁创建和销毁对象的情况下，小对象也不例外，使用对象池能够显著减轻垃圾回收的压力，提高游戏的性能。

对象池的工作原理

对象池框架的基本原理是在游戏启动时创建一定数量的对象实例并保存在池中。当需要使用对象时，不再重新创建新的对象，而是从池中取出一个空闲的对象并重置其状态，然后将其投放到场景中。完成使用后，对象并不被销毁，而是被重新放回对象池，等待下次使用。

为什么使用对象池框架？

性能优化： 避免频繁的对象创建和销毁，减少了垃圾回收的频率，提高了游戏的性能。
内存管理： 对象池有效地管理了对象的内存，避免了不必要的内存分配和释放操作。
减少资源消耗： 对象池框架可以降低游戏的资源消耗，使游戏更加流畅。
提高对象复用率： 通过对象池，可以更高效地重用已有的对象，减少了对象的创建成本。


使用细则
LIFO 驱逐策略
当前采用 LIFO 的驱逐策略，保证永远优先使用最常被使用的对象。之所以不采用 FIFO 是因为我们只有让热门的对象尽可能保持热门，而不是均衡每个对象的使用频率，才能够保证最大程度筛选出不常用的对象从而使其被驱逐。

避免频繁驱逐
某些情况下会出现不停创建新的对象，到了驱逐时间又被立马销毁的情况，从而使得对象池的大小出现不必要的频繁变动。这里我们可以通过 MinIdleTime 配置最小闲置时间，保证只有当对象闲置超过该时间后，才可能被驱逐。

对象校验
有一种情况是，一开始在池子里创建好了几个对象，但是当用户实际去取出来的时候，发现该对象其实已经被关闭或者失效了。所以在 Pool 内部需要每次取的对象都经过一次校验，如果校验不通过，则销毁对象，再次尝试去取。该策略还能保证当出现部分节点抖动时，会尽可能剔除不可用节点，提供稳定的对象。

同时为了避免当一些灾难情况下，永远无法成功创建对象（例如下游节点完全宕机），我们还需要设置 MaxValidateAttempts 以避免出现恶性循环。

预创建对象
在默认情况下，我们会在每次取对象的时候，判断是否需要创建新的，如需要再取实时创建。但如果创建操作比较费时，我们会希望在条件允许的情况下，池子里能够预留一部分空闲对象，以供未来调用。MinIdle 参数用以确保池子内最小能够拥有的空闲对象数。

超时取消
默认配置下，每次取对象如果当前池已满，且没有闲置对象，会阻塞住，直到能够获取到可用对象为止。我们使用 context 来实现获取超时取消的逻辑。一旦当触发 ctx.Done() 时候，会直接 return，并返回 ctx.Err() 。

高级扩展
Pond 是一个通用对象池，在此基础上，我们可以非常简单地实现诸如连接池，goroutine 池等多重应用。

以下示例展示了如何使用 Pond 创建一个简单的 goroutine 池：

