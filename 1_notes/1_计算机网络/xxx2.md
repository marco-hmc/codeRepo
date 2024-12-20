### 4. Cookies 和 Session

#### 4.1 cookies
- **Cookies**：
  - Cookies 是服务器发送到用户浏览器并保存在浏览器上的一种数据，它可以让服务器记住用户的信息。
  - 用途：会话管理、个性化设置、跟踪用户行为等。

* 概念

  * HTTP 协议是无状态的，主要是为了让 HTTP 协议尽可能简单，使得它能够处理大量事务.**HTTP/1.1 引入 Cookie 来保存状态信息**
  * **Cookie 是服务器发送到用户浏览器并保存在本地的一小块数据**，**它会在浏览器之后向同一服务器再次发起请求时被携带上，用于告知服务端两个请求是否来自同一浏览器.由于之后每次请求都会需要携带 Cookie 数据，因此会带来额外的性能开销**(尤其是在移动环境下)
  * Cookie 曾一度用于客户端数据的存储，因为当时并没有其它合适的存储办法而作为唯一的存储手段，但现在随着现代浏览器开始支持各种各样的存储方式，**Cookie 渐渐被淘汰**.新的浏览器 API 已经允许开发者直接将数据存储到本地，如使用 Web storage API(本地存储和会话存储)或 IndexedDB

* 用途

  * 会话状态管理(如**用户登录状态/购物车/游戏分数或其它需要记录的信息**)
  * 个性化设置(如用户自定义设置/主题等)
  * 浏览器行为跟踪(如跟踪分析用户行为等)

* 创建过程

  * **服务器发送的响应报文包含 Set-Cookie 首部字段，客户端得到响应报文后把 Cookie 内容保存到浏览器中**

    ```http
    HTTP/1.0 200 OK
    Content-type: text/html
    Set-Cookie: yummy_cookie=choco
    Set-Cookie: tasty_cookie=strawberry
    
    [page content]
    ```

  * 客户端之后对同一个服务器发送请求时，会从浏览器中取出 Cookie 信息并通过 Cookie 请求首部字段发送给服务器

    ```http
    GET /sample_page.html HTTP/1.1
    Host: www.example.org
    Cookie: yummy_cookie=choco; tasty_cookie=strawberry
    ```

* 分类
  * **会话期 Cookie:浏览器关闭之后它会被自动删除，也就是说它仅在会话期内有效**
  * **持久性 Cookie:指定过期时间(Expires)或有效期(max-age)之后就成为了持久性的 Cookie**

    ```http
    Set-Cookie: id=a3fWa; Expires=Wed， 21 Oct 2015 07:28:00 GMT;
    ```

* Secure
  * 标记为 Secure 的 Cookie **只能通过被 HTTPS 协议加密过的请求**发送给服务端.**但即便设置了 Secure 标记，敏感信息也不应该通过 Cookie 传输，因为 Cookie 有其固有的不安全性，Secure 标记也无法提供确实的安全保障**

![cookie的实体](./img/cookies.png "cookies实体，键值")

> Cooke通过客户端记录信息确定用户身份
> Session通过在服务器端记录信息来确定用户身份

cookie存储在客户端的Cookies文件夹内📁(物理位置)<br>
cookie存储的类型限制是字符串(类型限制🚫)<br>
当前请求上下文，上下文都能访问Cookie，Cookie对每个用户来说都是独立的(状态使用范围)<br>
每个cookie都有自己的过期时间，超过过期时间就会失效(生命周期)<br>
存储在客户端，安全性差，对于敏感数据建议加密🔐后存储(安全与性能)<br>
可以方便地管理网站和用户，长久保存用户设置<br>
以上是cookie的总结点，那么cookie存储的结构是什么呢？Key-Value结构，多个key用"&"连接。<br>
要好好了解一下cookie，我们带着一个问题去看。 **浏览器禁止cookie时，服务器与客户端浏览器能否保持session连接❓**<br>
鉴于这个问题，我们来看看这两对报文<br>
第一次请求
```
Http request:

GET /cluster/index.jsp HTTP/1.1

Accept: image/gif， image/jpeg， image/pjpeg， image/pjpeg， application/x-shockwave-flash， application/vnd.ms-excel， application/vnd.ms-powerpoint， application/msword， application/x-ms-application， application/x-ms-xbap， application/vnd.ms-xpsdocument， application/xaml+xml， */*

Accept-Language: zh-cn

User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; InfoPath.2; CIBA; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022)

Accept-Encoding: gzip， deflate

Host: localhost:8080

Connection: Keep-Alive
```
第一次响应返回
```
Http response:

HTTP/1.1 200 OK

Server: Apache-Coyote/1.1

Set-Cookie: JSESSIONID=4918D6ED22B81B587E7AF7517CE24E25.server1; Path=/cluster

Content-Type: text/html;charset=ISO-8859-1

Content-Length: 377

Date: Tue， 02 Mar 2010 02:58:32 GMT
```
当第一次请求一个网址时的请求和响应消息，客户端没有该网址的cookie，首先看response消息，我们看到一个Set-cookie，这行其实就是在告诉客户端浏览器，把这一段cookie保存下来，根据cookie的存活时间，这段cookie信息有可能只存在在内存中，也可能保存在文件中。<br>

在这里我插一段set-cookie的属性值的说明

属性|说明
|--|--|
NAME=VALUE|赋予Cookie的名称和其值(必须项)
expires|Cookie的有效期(若不明确指明，则默认浏览器关闭前为止)
path=PATH|将服务器上的文件目录作为Cookie得到适用对象(若不能指定则默认为文档的所在文件目录)
domain=域名|作为Cookie适用对象的域名(若不指定则默认为创建cookie的服务器域名)
secure|仅在HTTPS安全通信时才会发送Cookie
HttpOnly|加以限制，使Cookie不能被JS脚本访问 安全🔐防止跨站攻击
Max-Age|在cookie失效之前需要经过的秒数


下面👇进行第二次请求和响应

```
Http request:

GET /cluster/user_details.jsp HTTP/1.1

Accept: image/gif， image/jpeg， image/pjpeg， image/pjpeg， application/x-shockwave-flash， application/vnd.ms-excel， application/vnd.ms-powerpoint， application/msword， application/x-ms-application， application/x-ms-xbap， application/vnd.ms-xpsdocument， application/xaml+xml， */*

Accept-Language: zh-cn

User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; InfoPath.2; CIBA; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022)

Accept-Encoding: gzip， deflate

Host: localhost:8080

Connection: Keep-Alive

Cookie: JSESSIONID=4918D6ED22B81B587E7AF7517CE24E25.server1
```
客户端包含了Cookie的值，放在HTTP请求报文中发送给服务器

```
Http response

HTTP/1.1 200 OK

Server: Apache-Coyote/1.1

Set-Cookie: JSESSIONID=4918D6ED22B81B587E7AF7517CE24E25.server1; Expires=Tue， 02-Mar-2010 22:15:38 GMT

Content-Type: text/html

Content-Length: 252

Date: Tue， 02 Mar 2010 05:35:38 GMT
```
服务器响应同样的内容。那么这两个报文告诉我们什么呢？一个用户的所有请求操作都应该属于同一个会话，而另一个用户的所有请求操作都属于另一个会话。我们知道HTTP是一个渣男，无状态的协议，一旦数据交换完毕，客户端和服务器端的连接就会关闭，再次交换新的数据就需要建立新的连接🔗。这就意味着服务器端无法从连接上跟踪会话，那怎么着？只能靠cookie。客户端请求服务器，如果需要记录该用户状态，就是用response向客户端颁发一个Cookie。客户端浏览器会把Cookie保存起来。当浏览器再请求该网站时，就会把请求的网址和Cookie一同提交给服务端。这时候，服务端检查Cookie，辨别用户的状态，服务器还可以根据需要修改Cookie的内容。<br>
cookie的内容主要包括:名字，值，过期时间，路径和域名<br>


#### 4.2 session

session是另一种记录客户状态的机制，与不同的是Cookie保存在客户端浏览器中，而Session保存在服务器上。他也是为了无状态的协议实现状态记录📝，客户端浏览器在访问服务器的时候，服务器把客户端信息以某种形式记录在服务器上，什么形式呢？也是键值对的形式，但是可能还需要计算，也有过期时间。客户端浏览器再次访问时只需要从该Session中查找该客户的状态即可。<br>
所以JSESSIONID和真实的session对象之间的关联关系，而这个JSESSIONID字符串就是通过http协议的cookie功能实现的。<br>

那么，在浏览器禁用cookie时，会发生什么呢？无非就是cookie没有了呗，第二次请求就不会发送cookie的信息了呗。那么服务器就会认为这个请求是一个新的请求，又创建一个服务器session...如此循环♻️往复。<br>
那么，能保持session连接吗？如果按上面的来说，就是不能保持，但是有方法实现吗？很多种形式，只要服务器认你这个token即可，例如可以通过URL传，可以通过indexdb传，可以通过request body传，只要服务器可以认得，就能保证你的客户端的状态。<br>
这样就能保持session状态连接。<br>

- **Session**：
  - Session 是服务器端用来保存用户状态的一种机制。
  - Session 数据通常保存在服务器内存或数据库中，通过 Session ID 进行标识和访问。

* 除了可以将用户信息通过 Cookie 存储在用户浏览器中，**也可以利用 Session 存储在服务器端，存储在服务器端的信息更加安全**
* Session 可以存储在服务器上的文件/数据库或者内存中.**也可以将 Session 存储在 Redis 这种内存型数据库中**，效率会更高
* 使用 Session **维护用户登录状态**的过程如下
  * 用户进行登录时，**用户提交包含用户名和密码的表单，放入 HTTP 请求报文中**
  * **服务器验证该用户名和密码，如果正确则把用户信息存储到 Redis 中，它在 Redis 中的 Key 称为 Session ID**
  * **服务器返回的响应报文的 Set-Cookie 首部字段包含了这个 Session ID，客户端收到响应报文之后将该 Cookie 值存入浏览器中**
  * **客户端之后对同一个服务器进行请求时会包含该 Cookie 值，服务器收到之后提取出 Session ID，从 Redis 中取出用户信息，继续之前的业务操作**
* 应该注意 Session ID 的安全性问题，不能让它被恶意攻击者轻易获取，那么就不能产生一个容易被猜到的 Session ID 值.此外，还需要**经常重新生成 Session ID**.在对安全性要求极高的场景下，例如转账等操作，**除了使用 Session 管理用户状态之外，还需要对用户进行重新验证，比如重新输入密码，或者使用短信验证码等方式**

* **session和cookie的关系**

  * cookie只是实现session的其中一种方案.虽然是最常用的，但并不是唯一的方法.禁用cookie后还有其他方法存储，比如放在url中
  * 现在大多都是Session + Cookie，但是只用session不用cookie，或是只用cookie，不用session在理论上都可以保持会话状态.可是实际中因为多种原因，一般不会单独使用
  * 用session只需要在客户端保存一个id，**实际上大量数据都是保存在服务端**.如果全部用cookie，数据量大的时候客户端是没有那么多空间的.
  * 如果只用cookie不用session，**那么账户信息全部保存在客户端**，一旦被劫持，全部信息都会泄露.并且客户端数据量变大，网络传输的数据量也会变大
