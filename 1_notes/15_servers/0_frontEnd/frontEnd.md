## frontEnd

- **MDN (Mozilla) JavaScript Reference**
    It's great to get in-depth information about individual language functions, methods etc.

    You can find it at <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference>.

    Although, it's often best to use an internet search instead. 
    
    Just use "MDN [term]" in the query, e.g. <https://google.com/search?q=MDN+parseInt> to search for the `parseInt` function.

* For instance, [Node.js](https://wikipedia.org/wiki/Node.js) supports functions that allow JavaScript to read/write arbitrary files, perform network requests, etc.

* - Send requests over the network to remote servers, download and upload files (so-called [AJAX](https://en.wikipedia.org/wiki/Ajax_(programming)) and [COMET](https://en.wikipedia.org/wiki/Comet_(programming)) technologies).

* Today, JavaScript can execute not only in the browser, but also on the server, or actually on any device that has a special program called [the JavaScript engine](https://en.wikipedia.org/wiki/JavaScript_engine).
  The browser has an embedded engine sometimes called a "JavaScript virtual machine".
  Different engines have different "codenames". For example:
  - [V8](https://en.wikipedia.org/wiki/V8_(JavaScript_engine)) -- in Chrome, Opera and Edge.
  - [SpiderMonkey](https://en.wikipedia.org/wiki/SpiderMonkey) -- in Firefox.
  - ...There are other codenames like "Chakra" for IE, "JavaScriptCore", "Nitro" and "SquirrelFish" for Safari, etc.
  The terms above are good to remember because they are used in developer articles on the internet. We'll use them too. For instance, if "a feature X is supported by V8", then it probably works in Chrome, Opera and Edge.

* 
  ```html
  <script src="file.js"></script>
  <script>
    alert(1);
  </script>
  ```

* emmet

2004年,JavaScript命运开始改变.那一年,**谷歌公司开始带头使用Ajax技术**,Ajax技术就是JavaScript的一个应用.并且,那时候人们逐渐开始提升用户体验了.Ajax有一些应用场景.比如,当我们在百度搜索框搜文字时,输入框下方的智能提示,可以通过Ajax实现.

2010年,人们更加了解**HTML5技术**,**HTML5推出了一个东西叫做Canvas**(画布),工程师可以在Canvas上进行游戏制作,利用的就是JavaScript.

2011年,**Node.js诞生**,使JavaScript能够开发服务器程序了.

如今,**WebApp**已经非常流行,就是用**网页技术开发手机应用**.手机系统有iOS/安卓.比如公司要开发一个"携程网"App,就需要招聘三队人马,比如iOS工程师10人,安卓工程师10人,前端工程师10人.共30人,开发成本大;而且如果要改版,要改3个版本.现在,假设公司都用web技术,用html+css+javascript技术就可以开发App.也易于迭代(网页一改变,所有的终端都变了).

虽然目前WebApp(Web应用)在功能和性能上的体验远不如Native App(原生应用),但是"在原生App中内嵌一部分H5页面"已经是一种趋势.

### 什么是jit
JIT是"Just-In-Time"编译的缩写,是一种将程序代码在运行时(而非事先)编译为机器代码的技术.这种技术可以提高程序的运行速度.

在传统的解释型语言(如Python或JavaScript)中,程序代码在运行时会被解释器逐行解释为机器代码并立即执行.这种方式的优点是灵活性高,可以在运行时动态修改代码,但缺点是运行速度较慢.

在传统的编译型语言(如C或C++)中,程序代码在运行前会被编译器全部编译为机器代码.这种方式的优点是运行速度快,因为机器代码可以直接被CPU执行,但缺点是灵活性较低,不能在运行时修改代码.

JIT编译技术试图结合解释型语言和编译型语言的优点.它在程序运行时将代码编译为机器代码,但只编译正在执行的部分,而不是全部代码.这样,它既可以在运行时动态修改代码,又可以通过编译为机器代码来提高运行速度.

JIT编译技术在许多现代语言和运行时系统中都有应用,如Java的HotSpot虚拟机/.NET的CLR/Python的PyPy/JavaScript的V8等.

### 什么是dom?
DOM(Document Object Model)是一种编程接口,它允许 JavaScript 和其他脚本语言操作 HTML 和 XML 文档的内容/结构和样式.DOM 将文档解析为一个由节点和对象(包括属性和方法)组成的结构,使得编程语言可以操作文档的内容和结构.

在 JavaScript 中,DOM 是由以下几种类型的节点组成的:

- **文档节点**:代表整个文档,是 DOM 树的根节点.

- **元素节点**:代表 HTML 或 XML 文档中的元素,如 `<p>`/`<div>` 等.

- **属性节点**:代表元素的属性.

- **文本节点**:代表元素或属性中的文本内容.

这些节点都是对象,具有各自的属性和方法.通过这些属性和方法,我们可以读取和修改节点的内容,创建和删除节点,添加和删除节点的属性,等等.

例如,我们可以使用 `getElementById` 方法获取一个元素节点,然后使用 `innerHTML` 属性修改其内容,或者使用 `style` 属性修改其样式.

总的来说,DOM 是 JavaScript 操作网页内容的一种方式,它将网页转化为一个对象模型,使得我们可以像操作对象一样操作网页.

### 如何将html转为dom树?
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

### js是如何操作dom树的

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


### js和html是如何一起工作的
实际上,当浏览器加载 HTML 文档时,它会读取 HTML 文档的文本内容,然后根据这些文本内容创建 DOM 树.这个过程被称为"解析".

在解析过程中,浏览器会逐行读取 HTML 文档的文本内容.对于每一个遇到的 HTML 标签,浏览器会创建一个对应的 DOM 对象(节点).这些对象包含了该标签的所有信息,如标签名/属性/父节点/子节点等.

然后,这些 DOM 对象按照它们在 HTML 文档中的嵌套关系组织成一个树状结构,称为 DOM 树.在 DOM 树中,整个文档是一个"文档节点",HTML 标签是"元素节点",标签的属性是"属性节点",标签中的文本内容是"文本节点".

这个 DOM 树就是一个 JavaScript 对象,JavaScript 可以通过操作这个对象来操作网页的内容和结构.所以,我们可以说,浏览器是将 HTML 文档的文本内容解析成一个 JavaScript 对象,然后 JavaScript 通过操作这个对象来操作 DOM 树.