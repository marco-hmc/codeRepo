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