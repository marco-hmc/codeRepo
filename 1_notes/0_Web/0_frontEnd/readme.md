## frontEnd

- **MDN (Mozilla) JavaScript Reference**
    MDM is the main manual with examples and other information. It's great to get in-depth information about individual language functions, methods etc.

    You can find it at <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference>.

    Although, it's often best to use an internet search instead. Just use "MDN [term]" in the query, e.g. <https://google.com/search?q=MDN+parseInt> to search for the `parseInt` function.

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