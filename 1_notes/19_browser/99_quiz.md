## 浏览器疑问

### 1. javaScript

#### 1.1 怎么理解变量提升？为什么要有变量提升？

变量提升（Hoisting）是 JavaScript 中的一个特性，它意味着无论变量在哪里声明，都会被提升到当前作用域的顶部。这个特性只适用于 var 声明的变量，let 和 const 声明的变量不会被提升。

这是一个例子：

```javascript
console.log(myVar); // 输出：undefined
var myVar = 5;
console.log(myVar); // 输出：5
```

在这个例子中，虽然 `myVar` 是在 `console.log(myVar);` 之后声明的，但是由于变量提升，`myVar` 在声明之前就已经存在了，只是它的值是 `undefined`。

变量提升的存在，主要是为了解决变量在声明之前就被引用的问题。但是，这也可能导致一些意想不到的问题，因为开发者可能会忘记或者不清楚变量提升的存在。因此，现代的 JavaScript 开发中，通常推荐使用 let 和 const 来声明变量，因为它们不会被提升，可以避免这种问题。

#### 1.2 怎么js的编译过程？
* 编译过程做了什么？
* 执行上下文，可执行代码是什么？
* 执行上下文包含哪些内容（变量环境，词法环境）
  * 执行上下文是 JavaScript 执行一段代码时的运行环境，比如调用一个函数，就会进入这个函数的执行上下文，确定该函数在执行期间用到的诸如 this、变量、对象以及函数等。

#### 1.3 为什么 JavaScript 代码会出现栈溢出

#### 1.4 代码中出现相同的变量或者函数怎么办？


```js
function showName() {
  console.log('极客邦')
}
showName()
function showName() {
  console.log('极客时间')
}
showName()
```

**一段代码如果定义了两个相同名字的函数，那么最终生效的是最后一个函数**。

### 1. 页面部分

#### 1.1 什么是dom?
DOM(Document Object Model)是一种编程接口,它允许 JavaScript 和其他脚本语言操作 HTML 和 XML 文档的内容/结构和样式.DOM 将文档解析为一个由节点和对象(包括属性和方法)组成的结构,使得编程语言可以操作文档的内容和结构.

在 JavaScript 中,DOM 是由以下几种类型的节点组成的:

- **文档节点**:代表整个文档,是 DOM 树的根节点.

- **元素节点**:代表 HTML 或 XML 文档中的元素,如 `<p>`/`<div>` 等.

- **属性节点**:代表元素的属性.

- **文本节点**:代表元素或属性中的文本内容.

这些节点都是对象,具有各自的属性和方法.通过这些属性和方法,我们可以读取和修改节点的内容,创建和删除节点,添加和删除节点的属性,等等.

例如,我们可以使用 `getElementById` 方法获取一个元素节点,然后使用 `innerHTML` 属性修改其内容,或者使用 `style` 属性修改其样式.

总的来说,DOM 是 JavaScript 操作网页内容的一种方式,它将网页转化为一个对象模型,使得我们可以像操作对象一样操作网页.

#### 1.2 如何将html转为dom树?
DOM(Document Object Model)将整个网页转化为一个对象模型的过程通常被称为"解析",这是浏览器的渲染引擎在加载网页时自动进行的.

当浏览器加载 HTML 文档时,它会从上到下逐行读取文档内容.对于每一个遇到的 HTML 标签,浏览器会创建一个对应的 DOM 对象(节点).这些对象包含了该标签的所有信息,如标签名/属性/父节点/子节点等.

这些 DOM 对象按照它们在 HTML 文档中的嵌套关系组织成一个树状结构,称为 DOM 树.在 DOM 树中,整个文档是一个"文档节点",HTML 标签是"元素节点",标签的属性是"属性节点",标签中的文本内容是"文本节点".

例如,对于以下的 HTML 文档:

```html
<!DOCTYPE html>
<html>
<head>
    <title>My Title</title>
</head>
<body>
    <h1>My Heading</h1>
    <p>My paragraph.</p>
</body>
</html>
```

浏览器会解析成如下的 DOM 树:

```
Document
└── HTML
    ├── HEAD
    │   └── TITLE
    │       └── "My Title"
    └── BODY
        ├── H1
        │   └── "My Heading"
        └── P
            └── "My paragraph."
```

通过这种方式,DOM 将网页转化为一个对象模型,使得 JavaScript 可以通过操作这些对象来操作网页的内容和结构.

#### 1.3 js是如何操作dom树的

JavaScript 操作 DOM 树主要通过以下几个步骤:

1. **获取节点**:首先,我们需要获取到我们想要操作的 DOM 节点.JavaScript 提供了多种方法来获取节点,如 `getElementById`/`getElementsByClassName`/`getElementsByTagName`/`querySelector` 和 `querySelectorAll` 等.

   ```javascript
   var element = document.getElementById('myElement');
   ```

2. **修改节点**:获取到节点后,我们可以使用节点的属性和方法来修改它.例如,我们可以修改元素节点的 `innerHTML` 属性来改变它的内容,或者修改 `style` 属性来改变它的样式.

   ```javascript
   element.innerHTML = 'New content';
   element.style.color = 'red';
   ```

3. **添加和删除节点**:我们还可以使用 `appendChild`/`insertBefore`/`removeChild` 等方法来添加/移动或删除节点.

   ```javascript
   var newElement = document.createElement('div');
   document.body.appendChild(newElement);
   
   var oldElement = document.getElementById('oldElement');
   document.body.removeChild(oldElement);
   ```

4. **添加和删除事件监听器**:我们可以使用 `addEventListener` 和 `removeEventListener` 方法来添加或删除事件监听器,使得我们可以在用户与网页交互时执行特定的代码.

   ```javascript
   element.addEventListener('click', function() {
       alert('Element was clicked!');
   });
   ```

以上就是 JavaScript 操作 DOM 树的基本步骤.通过这些步骤,我们可以动态地修改网页的内容/结构和样式,以及响应用户的交互.


#### 1.4 js和html是如何一起工作的
实际上,当浏览器加载 HTML 文档时,它会读取 HTML 文档的文本内容,然后根据这些文本内容创建 DOM 树.这个过程被称为"解析".

在解析过程中,浏览器会逐行读取 HTML 文档的文本内容.对于每一个遇到的 HTML 标签,浏览器会创建一个对应的 DOM 对象(节点).这些对象包含了该标签的所有信息,如标签名/属性/父节点/子节点等.

然后,这些 DOM 对象按照它们在 HTML 文档中的嵌套关系组织成一个树状结构,称为 DOM 树.在 DOM 树中,整个文档是一个"文档节点",HTML 标签是"元素节点",标签的属性是"属性节点",标签中的文本内容是"文本节点".

这个 DOM 树就是一个 JavaScript 对象,JavaScript 可以通过操作这个对象来操作网页的内容和结构.所以,我们可以说,浏览器是将 HTML 文档的文本内容解析成一个 JavaScript 对象,然后 JavaScript 通过操作这个对象来操作 DOM 树.


### 附录
#### 1. terms
* MDN
    MDN,全称Mozilla Developer Network,是一个开放的社区和资源库,为开发者提供了大量关于开放网络技术(包括CSS/HTML和JavaScript)的文档和学习资源.

    MDN的JavaScript参考文档是一个非常重要的资源,它提供了关于JavaScript语言的深入信息,包括语言的函数/方法等详细解释和示例.这些信息对于理解和使用JavaScript非常有帮助.

* html/css/js
    HTML,CSS和JavaScript是构建网页和网站的三大核心技术.

    1. **HTML**:HTML(HyperText Markup Language,超文本标记语言)是用来描述网页内容的语言.它使用一系列元素(或称为标签)来标记和包裹网页的各个部分内容,如标题/段落/列表/链接/图片等.每个元素都有特定的含义和用途,告诉浏览器如何展示相关内容.

    2. **CSS**:CSS(Cascading Style Sheets,层叠样式表)是用来描述网页样式的语言.它可以定义网页中元素的布局/颜色/字体等视觉效果.CSS可以让你将样式信息与HTML内容分离,使得网页的结构和样式可以独立编辑和管理,提高了代码的可维护性.

    3. **JavaScript**:JavaScript是一种编程语言,用于实现网页的交互功能.通过JavaScript,你可以操作DOM(Document Object Model,文档对象模型)来动态修改网页的内容/结构和样式,可以处理用户的输入和操作,可以实现动画效果,可以与服务器进行通信等.

    这三种语言的关系是:HTML负责网页的结构,CSS负责网页的样式,JavaScript负责网页的行为.它们共同工作,构建出丰富/美观/交互的网页和网站.

* nodeJs
    Node.js是一个开源的/跨平台的JavaScript运行环境,它可以让JavaScript脱离浏览器环境,在服务器或其他计算机环境中运行.Node.js的设计目标是提供一种简单的构建可扩展网络应用的方法.
    Node.js 的解释和运行是由 Google 的 V8 JavaScript 引擎来完成的.
    Node.js 在 V8 的基础上,增加了一些 API 和功能,使得 JavaScript 可以进行文件操作/网络通信/操作系统交互等,这些在浏览器环境中无法做到的事情.这使得 JavaScript 可以用于服务器端编程,构建网络应用.

* v8引擎
    V8 引擎是 Google 开发的开源 JavaScript 引擎.它用于 Google Chrome 浏览器,也是 Node.js 的核心组成部分.

    V8 引擎的主要特性包括:

    1. **即时编译(JIT)**:V8 引擎将 JavaScript 代码直接编译成机器码来执行,而不是先编译成字节码或通过解释器解释执行.这使得 JavaScript 代码的运行效率非常高.

    2. **垃圾回收**:V8 引擎有一个高效的垃圾回收机制,可以自动回收不再使用的内存,防止内存泄漏.

    3. **调用堆栈跟踪**:V8 引擎可以提供详细的调用堆栈信息,帮助开发者调试代码.

    4. **高性能的 JavaScript 执行**:通过各种优化技术,如内联缓存(Inline Caching)/隐藏类(Hidden Classes)等,V8 引擎可以高效地执行 JavaScript 代码.

    V8 引擎的设计目标是提供高性能的 JavaScript 执行环境,同时保持代码的安全性和可移植性.因此,V8 引擎在浏览器和服务器端的 JavaScript 执行环境中都有广泛的应用.

* Dom
* Ajax
* Jquery
* Vue
* React