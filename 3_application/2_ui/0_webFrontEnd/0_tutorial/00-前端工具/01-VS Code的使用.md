## 前言

## 一、VS Code 的介绍

### 18、Vetur

Vue 多功能集成插件，包括：语法高亮，智能提示，emmet，错误提示，格式化，自动补全，debugger。VS Code 官方钦定 Vue 插件，Vue 开发者必备。

### 19、ES7 React/Redux/GraphQL/React-Native snippets

React/Redux/react-router 的语法智能提示。

### 20、minapp：小程序支持

小程序开发必备插件。

### 22、ESLint：代码格式校验

日常开发中，建议用可以用 Prettier 做代码格式化，然后用 eslint 做校验。

### 24、JavaScript(ES6) code snippets

ES6 语法智能提示，支持快速输入。

### 25、Search node_modules 【荐】

`node_modules`模块里面的文件夹和模块实在是太多了，根本不好找。好在安装 `Search node_modules` 这个插件后，输入快捷键「Cmd + Shift + P」，然后输入 `node_modules`，在弹出的选项中选择 `Search node_modules`，即可搜索 node_modules 里的模块。

![](http://img.smyhvae.com/20200618_2100.png)

### 32、Auto Close Tag、Auto Rename Tag

自动闭合标签、自动对标签重命名。

### 34、CSS Peek

增强 HTML 和 CSS 之间的关联，快速查看该元素上的 CSS 样式。

### 35、Vue CSS Peek

CSS Peek 对 Vue 没有支持，该插件提供了对 Vue 文件的支持。

### 39、Import Cost

在项目开发过程中，我们会引入很多 npm 包，有时候可能只用到了某个包里的一个方法，却引入了整个包，导致代码体积增大很多。`Import Cost`插件可以在代码中友好的提示我们，当前引入的包会增加多少体积，这很有助于帮我们优化代码的体积。



### sftp：文件传输


输入快捷键「ctrl+shift+P」，弹出指令窗口，输入`sftp:config`，回车，当前工作工程的`.vscode`文件夹下就会自动生成一个`sftp.json`文件，我们需要在这个文件里配置的是：

- `host`：服务器的IP地址

- `username`：工作站自己的用户名

- `privateKeyPath`：存放在本地的已配置好的用于登录工作站的密钥文件（也可以是ppk文件）

- `remotePath`：工作站上与本地工程同步的文件夹路径，需要和本地工程文件根目录同名，且在使用sftp上传文件之前，要手动在工作站上mkdir生成这个根目录

- `ignore`：指定在使用sftp: sync to remote的时候忽略的文件及文件夹，注意每一行后面有逗号，最后一行没有逗号


举例如下：(注意，其中的注释不能保留)

```json
{
    "host": "",     //服务器ip
    "port": 22,     //端口，sftp模式是22
    "username": "", //用户名
    "password": "", //密码
    "protocol": "sftp", //模式
    "agent": null,
    "privateKeyPath": null,
    "passphrase": null,
    "passive": false,
    "interactiveAuth": false,
    "remotePath": "/root/node/build/",  //服务器上的文件地址
    "context": "./server/build",        //本地的文件地址

    "uploadOnSave": true,   //监听保存并上传
    "syncMode": "update",
    "watcher": {            //监听外部文件
        "files": false,     //外部文件的绝对路径
        "autoUpload": false,
        "autoDelete": false
    },
    "ignore": [             //忽略项
        "**/.vscode/**",
        "**/.git/**",
        "**/.DS_Store"
    ]
}
```

### Express

在本地开启Node服务器：

![](http://img.smyhvae.com/20180611_2230.png)

然后在浏览器的地址栏输入`http://localhost/` + 文件的相对路径，就可以通过服务器的形式打开这个文件。

## Vue 相关的插件

### vetur：vue 文件的基本语法高亮

安装完 vetur 后还需要加上这样一段配置下：

```
"emmet.syntaxProfiles": {
  "vue-html": "html",
  "vue": "html"
}
```

参考链接：
- <https://www.clarencep.com/2017/03/18/edit-vue-file-via-vscode/>
- <https://github.com/varHarrie/varharrie.github.io/issues/10>
