## 如何做一个你自己的blog

网上以github pages + jekyll + blog为关键词网上搜索一下其实就已经有很多教程了。
但是这些教程大多都是说明书式的声明，对相关原理和概念的介绍比较少，这里我就以我所觉得有必要的概念进行介绍一下吧。

### 1. github pages是什么？
GitHub Pages 是 GitHub 提供的一项服务，允许你直接从 GitHub 仓库托管和发布网站。它的工作原理如下：

创建仓库：你需要在 GitHub 上创建一个新的仓库来存储你的网站文件。如果你想要使用你的 GitHub 用户名来创建一个用户网站，你的仓库的名字必须是 {username}.github.io。

添加网站文件：你可以添加 HTML、CSS、JavaScript、图片等文件到你的仓库。你也可以使用 Jekyll，这是一个静态网站生成器，它可以自动将 Markdown 文件转换为 HTML 文件。

推送到 GitHub：当你将你的文件推送到 GitHub 时，GitHub Pages 会自动构建和部署你的网站。如果你使用了 Jekyll，GitHub Pages 会自动运行 Jekyll 来构建你的网站。

访问网站：一旦你的网站被构建和部署，你就可以通过 {username}.github.io 来访问你的网站。如果你的仓库是一个项目仓库，你的网站的 URL 会是 {username}.github.io/{repository}。

总的来说，GitHub Pages 是一个简单的静态网站托管服务，它通过自动构建和部署你的 GitHub 仓库来生成网站。

所以，你只需要提供一些静态网站内容，推送到{username}.github.io命名的仓库，访问{username}.github.io这个域名，就可以看见你的博客了。

而这个过程中使用Jekyll，是为了自动生成静态网站内容，只需要给定markdown文件，就会转成html文件呢。

### 2. jekyll是如何将markdown文件转为html文件的？
Jekyll 使用一个名为 Liquid 的模板引擎来将 Markdown 文件转换为 HTML 文件。这个过程大致分为以下几个步骤：

1. **读取配置**：Jekyll 首先会读取 `_config.yml` 文件，获取网站的配置信息，如主题、插件、默认布局等。

2. **加载插件**：Jekyll 会加载在 `_config.yml` 文件中指定的插件。这些插件可以添加新的功能，如生成 RSS 订阅、优化 SEO 等。

3. **读取文件**：Jekyll 会读取所有的 Markdown 文件和其他文件（如 HTML、CSS、JavaScript 文件）。这些文件可以位于根目录、`_posts` 目录、`_drafts` 目录等。

4. **转换文件**：对于每个 Markdown 文件，Jekyll 会使用 Liquid 模板引擎将其转换为 HTML 文件。这个过程包括解析 YAML 头信息、处理 Liquid 标签和过滤器、将 Markdown 文本转换为 HTML 等。

5. **应用布局**：Jekyll 会将转换后的 HTML 内容插入到指定的布局文件中。布局文件是包含 HTML 结构和 Liquid 标签的文件，可以在 `_layouts` 目录中找到。

6. **生成静态文件**：最后，Jekyll 会将所有的 HTML 文件和其他文件写入到 `_site` 目录。这个目录包含了你的完整网站，可以直接部署到服务器。

总的来说，Jekyll 使用 Liquid 模板引擎和一系列的步骤来将 Markdown 文件转换为 HTML 文件，从而生成静态网站。

### 3. 什么是Liquid？
Liquid 是一个开源的模板语言，由 Shopify 创建。它在 Ruby 中实现，但可以被嵌入到许多不同的编程语言中。

Liquid 用于加载动态内容到静态 HTML 文件中。它有两种主要的语法：输出标记和标签。

- 输出标记 `{{ }}` 用于插入 Ruby 表达式的结果。例如，`{{ page.title }}` 会输出当前页面的标题。

- 标签 `{% %}` 用于执行逻辑操作，如条件判断和循环。例如，`{% if user %}Hello, {{ user.name }}{% endif %}` 会检查是否存在一个用户，如果存在，就输出用户的名字。

Liquid 还支持过滤器，可以用于修改输出标记的结果。例如，`{{ 'hello' | upcase }}` 会输出 "HELLO"。

Jekyll 和 GitHub Pages 都使用 Liquid 作为其模板语言，允许你在静态 HTML 文件中插入动态内容。

### 4. 什么是模板语言？liquid和html的关系是什么？
模板语言是一种设计用来生成文本输出的编程语言。模板语言通常用于将动态数据插入到静态文件中，如 HTML、XML 或 JSON 文件。模板语言通常包含变量、控制结构（如循环和条件判断）和函数等元素。

Liquid 是一种模板语言，由 Shopify 创建。它在 Ruby 中实现，但可以被嵌入到许多不同的编程语言中。Liquid 可以读取你提供的数据，然后根据这些数据生成 HTML、XML 或其他类型的文本文件。

HTML 是一种标记语言，用于描述网页的结构和内容。HTML 文件由一系列的标签组成，这些标签定义了网页的各个部分，如标题、段落、链接、图片等。

Liquid 和 HTML 的关系是，你可以在 HTML 文件中插入 Liquid 标签和变量。当你使用 Liquid 来处理这个 HTML 文件时，Liquid 会读取你提供的数据，然后替换掉 HTML 文件中的 Liquid 标签和变量，生成一个完整的 HTML 文件。

例如，你可以在 HTML 文件中使用 Liquid 输出标记 `{{ page.title }}` 来插入页面的标题。当你使用 Liquid 来处理这个 HTML 文件时，你需要提供一个包含 `title` 属性的 `page` 对象。Liquid 会读取 `page.title` 的值，然后替换掉 `{{ page.title }}`，生成一个包含实际标题的 HTML 文件。

总的来说，Liquid 是一种模板语言，可以用于在 HTML 文件中插入动态内容。

简单来说，一开始html文件可以有liquid，但是后端语言通过某个方式解析liquid后，最终生成的html文件，就不带liquid语言了。

而这个解析