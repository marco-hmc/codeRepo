## mermaid

> marco

[toc]

### 1. 时序图

```mermaid
sequenceDiagram

Alice->>John: Hello John, how are you?
loop Healthcheck
John->>John: Fight against hypochondria
end
Note right of John: Rational thoughts!
John-->>Alice: Great!
John->>Bob : How about you?
Bob-->>John : Jolly good!
```

### 2. 流程图

```mermaid
graph TB

id1(圆角矩形)--普通线-->id2[矩形];
subgraph 子图
id2==粗线==>id3{菱形}
id3-. 虚线.->id4>右向旗帜]
id3--无箭头---id5((圆形))

end
```

### 3. 甘特图

```mermaid
gantt

section Section
Completed: done, des1, 2014-01-06, 2014-01-08
Active : active, des2, 2014-01-07, 3d
Parallel 1 : des3, after des1, 1d
Parallel 2 : des4, after des1, 1d
Parallel 3 : des5, after des3, 1d
Parallel 4 : des6, after des4, 1d
```

### 4. 类图

```mermaid
classDiagram
class Animal {
        +name: string
        +age: int
        +eat(food: string): void
    }

class Dog {
        +sound: string
        +bark(): void
    }

class Cat {
        +climb(): void
    }
    
class Squre~Shape~{
    int id
    List~int~ position
    setPoints(List~int~ points)
    getPoints() List~int~
}

    Animal "99999" <|-- Dog : BlaBla
    Animal <|-- Cat : BlaBla
```

#### 附录

+ **类图属性**

  | 符号 | 意义             |
  | ---- | ---------------- |
  | `+`  | public           |
  | `-`  | private          |
  | `#`  | protected        |
  | `~`  | package/internal |
  | *    | virtual          |
  | $    | static           |

  
* **类图关系**
  | 类型  | 描述              |
  | ----- | ----------------- |
  | `<¦–` | (Inheritance)继承 |
  | `*--` | (Composition)组合 |
  | `o--` | (Aggregation)聚合 |
  | `-->` | (Association)关联 |
  | `--`  | (Link)实线连接    |
  | `..>` | (Dependency)依赖  |
  | `…¦>` | (Realization)实现 |
  | `..`  | (Link)虚线连接    |