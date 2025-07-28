# HTML

## 基础语法

### 元素

- 开始标签（opening tag）：由元素的名称（本例中为段落的 p）包裹在开、闭角括号中组成。这个开始标签标志着元素开始或生效的位置。
- 内容（content）：这是元素的内容。在此示例中，就是段落的文本。
- 结束标签（closing tag）：这与开始标签相同，只是在元素名称前包含一个正斜杠。这标志着元素的结束。

#### 嵌套元素

```html
<p>我们的小猫脾气<strong>很</strong>暴躁。</p>
```

<p>我们的小猫脾气<strong>很</strong>暴躁。</p>

#### 空元素

```html
<img src="https://wpimg.wallstcn.com/f778738c-e4f8-4870-b634-56703b4acafe.gif" alt="图标" />
```

### 属性

- 一个在它和元素名之间的空格。（对于拥有多个属性的元素，属性之间也应该用空格分隔。）
- 属性名，后跟一个等号。
- 一个属性值，用开始和结束的引号包裹。

#### 布尔属性

某些属性不需要属性值，比如`disabled`属性。当属性值不存在时，布尔属性被假定为`true`。

```html
<input type="text" disabled="disabled" />
<input type="text" disabled />
<input type="text" />
```

<input type="text" disabled="disabled" />
<input type="text" disabled />
<input type="text" />

#### 省略属性值两边的引号

```html
<a href=https://www.bilibili.com/>bilibili官网</a>
```

#### 单引号和双引号

- 单独使用时两者等价
- 嵌套使用：可以在属性值内部包含另一种类型的引号

要在相同类型的引号内使用引号（单引号或双引号），请使用[字符引用](https://developer.mozilla.org/zh-CN/docs/Glossary/Character_reference)。

### 完整的 HTML 文件

```html
<!DOCTYPE html>
<html lang="zh-CN">
  <head>
    <meta charset="utf-8" />
    <title>标题</title>
  </head>
  <body>
    <p>页面内容</p>
  </body>
</html>

1. <!doctype html>：文档类型声明（doctype）。
2. <html></html>：<html> 元素。这个元素包裹了页面上的所有内容。它有时被称为根元素。
3. <head></head>：<head> 元素。这个元素充当一个容器，用于存放你想包含在 HTML 页面中但不向页面浏览者显示的内容。这包括会出现在搜索结果中的关键字和页面描述、用于样式化内容的 CSS、字符集声明等等。
4. <meta charset="utf-8">：<meta> 元素。这个元素代表了不能由其他 HTML 元相关元素（如 <base>、<link>、<script>、<style> 或 <title>）表示的元数据。charset 属性将你的文档的字符编码指定为 UTF-8
5. <title></title>：<title> 元素。它设置了页面的标题。
6. <body></body>：内容
```

### 特殊字符

字符 <、>、"、' 和 & 是特殊字符。它们是 HTML 语法本身的一部分。

### 注释

```html
<!-- 这是被注释的内容 -->
```

## HTML head

- `<title>`标题
- `<meta>`: 元数据

```html
<!-- 字符编码 -->
<meta charset="utf-8" />
<!-- 作者 -->
<meta name="author" content="contentadfdashkjfa" />
```

### 自定义图标

1. 将其保存在与网站的索引页面相同的目录中，以 .ico 格式保存（大多数浏览器支持更通用的格式，如 .gif 或 .png）
2. 将以下行添加到 HTML 的 <head> 块中以引用它：

```html
<link rel="icon" href="favicon.ico" type="image/x-icon" />
```

不同的场景使用不同的图标,[参考](https://developer.mozilla.org/zh-CN/docs/Learn_web_development/Core/Structuring_content/Webpage_metadata)

### 在 HTML 中应用 CSS 和 JavaScript

```html
<link rel="stylesheet" href="my-css-file.css" />
<script src="my-js-file.js"></script>
```

### 设定主语言

```html
<html lang="zh-CN">
  …
</html>
```

## 标签

1. 标题: `<h1>` `<h2>` `<h3>` `<h4>` `<h5>` `<h6>`
2. 段落: `<p>`
3. 强调: `<em>` `<strong>`
4. 粗体、斜体、下划线：`<b>` `<i>` `<u>`
5. 列表：`<ul>` `<ol>` `<li>`

```html
<!-- 无序列表 -->
<ul>
  <li>语文</li>
  <li>数学</li>
  <li>英语</li>
</ul>

<!-- 有序列表 -->
<ol>
  <li>语文</li>
  <li>语文</li>
</ol>
<!-- 列表可以嵌套 -->
```

6. 描述列表：`<dl>` `<dt>` `<dd>`

```html
<dl>
  <dt>DT1</dt>
  <dd>DD1</dd>
  <dt>DT2</dt>
  <dd>DD2</dd>
  <dd>DD3</dd>
</dl>
```

<dl>
  <dt>DT1</dt>
  <dd>DD1</dd>
  <dt>DT2</dt>
  <dd>DD2</dd>
  <dd>DD3</dd>
</dl>

7. 无语义元素：`<div>` `<span>`
8. 换行与分割线：`<br>` `<hr>`

## 文档

基本组成：页眉、导航栏、内容、侧边栏、页脚

## 文本进阶

### 引用

1. 块引用

   用 `<blockquote>` 元素包裹起来表示，并且在 cite 属性里用 URL 来指向引用的资源。

2. 行内引用

   用 `<q>` 元素包裹起来表示，并且在 cite 属性里用 URL 来指向引用的资源。

3. 引文

   用 `<cite>` 元素包裹起来表示，并且在 cite 属性里用 URL 来指向引文的资源。

   引文默认的字体样式为斜体

### 缩略语

```html
<p>我们使用 <abbr title="超文本标记语言">HTML</abbr> 来组织网页文档。</p>
```

<p>我们使用 <abbr title = '超文本标记语言'>HTML</abbr> 来组织网页文档。</p>

### 标记联系方式

<address>
123
3214
</address>

### 上标和下标

`<sup> <sub>`

```html
<p>C<sub>8</sub>H<sub>10</sub>N<sub>4</sub>O<sub>2</sub></p>
<p>x<sup>2</sup></p>
```

<p>C<sub>8</sub>H<sub>10</sub>N<sub>4</sub>O<sub>2</sub></p>
<p>x<sup>2</sup></p>

### 计算机代码

- `<code></code>`: 表示计算机代码
- `<pre></pre>`: 预格式文本,用于保留空白字符（通常用于代码块
- `<kbd></kbd>`: 表示用户输入的键盘按键
- `<samp></samp>`: 表示计算机程序输出的样本
- `<var></var>`: 表示变量

### 标记时间和日期

<time datetime="2016-01-20">2016 年 1 月 20 日</time>

## 超链接

通过将文本或其他内容包裹在 `<a>` 元素内，并给它一个包含网址的 `href` 属性,另外可以添加`title`属性

```html
<a href="https://www.bilibili.com" title="https://www.bilibili.com">跳转到B站</a>
```

<a href="https://www.bilibili.com" title='https://www.bilibili.com'>跳转到 B 站</a>

目录相关请参考[统一资源定位符（URL）与路径（path）快速入门](https://developer.mozilla.org/zh-CN/docs/Learn_web_development/Core/Structuring_content/Creating_links)

文档内链接

```html
<h2 id="section-id">标题</h2>

<a href="#section-id">跳转到指定位置</a>
<!-- 为了链接到那个特定的 id，要将它放在 URL 的末尾，并在前面包含井号（#） -->
```

## 图片

```html
<img src="https://wpimg.wallstcn.com/f778738c-e4f8-4870-b634-56703b4acafe.gif" alt="图标" />
```

- 可以用 `width` 和 `height` 属性来指定你的图片的宽度和高度。它们的值是不带单位的整数，以像素为单位表示图像的宽度和高度。
- 可以添加`title`属性，鼠标移到图片上时显示的提示信息。

### 给图片搭配说明文字

- `<figure>` 元素用于把图片和说明文字组合在一起。
- `<figcaption>` 元素用于定义 `<figure>` 元素的标题。

```html
<figure>
  <img src="https://wpimg.wallstcn.com/f778738c-e4f8-4870-b634-56703b4acafe.gif" alt="test text" width="150" height="100" />

  <figcaption>A T-Rex on display in the Manchester University Museum.</figcaption>
</figure>
```

## 视频和音频

`<video>` 元素用于定义视频。

- `src`: 指定视频文件的位置
- `controls`: 添加控件

```html
<video src="rabbit320.webm" controls>
  <p>你的浏览器不支持 HTML 视频。可点击<a href="rabbit320.mp4">此链接</a>观看。</p>
</video>
```

### video 其他属性

- `controls`: 添加控件
- `width` `height`: 设置视频的宽度和高度
- `autoplay`: 自动播放
- `loop`: 循环播放
- `muted`: 静音播放
- `poster`: 添加封面图片
- `preload`: 预加载视频
  - `none`: 不预加载
  - `metadata`: 只预加载元数据
  - `auto`: 自动预加载

`<audio>` 标签用于添加音频文件

与 `<video>` 的差异如下：

- 不支持 width/heigth 属性
- 不支持 poster 属性——同样，因为没有视觉部件。

## 表格与表单

未学习
