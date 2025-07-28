# CSS 基础

## 选择器

### 类型、类和 ID 选择器

1. 类型选择器

```css
h1 {
  color: red;
}
```

2. 类选择器

```css
.testclass {
  color: red;
}
```

3. ID 选择器

```css
#testid {
  color: red;
}
```

### 标签属性选择器

```css
/* 这组选择器根据一个元素上的某个标签的属性的存在以选择元素的不同方式 */
a[title] {
  color: red;
}

a[href="https://example.com"]
{
  color: red;
}
```

详细介绍请查看[属性选择器](https://developer.mozilla.org/zh-CN/docs/Learn_web_development/Core/Styling_basics/Attribute_selectors)

### 伪类与伪元素

[查询所有伪类](https://developer.mozilla.org/zh-CN/docs/Web/CSS/Pseudo-classes)

布局伪类

```css
/* 所有p 元素的第一个子元素 */
p:first-child {
  font-size: 120%;
  font-weight: bold;
}
```

- `:first-child`:第一个子元素
- `:last-child`:最后一个子元素
- `:nth-child(n)`:第 n 个子元素
- `only-child`:只有第一个子元素
- `invalid`:无效元素

用户行为伪类

- `:hover`:鼠标悬停
- `:active`:元素被激活
- `:focus`:元素被聚焦
- `:visited`:元素被访问

<strong>伪元素：不是向现有的元素上应用类。</strong>

```css
/* 只适用于第一个行 */
p::first-line {
  font-size: 120%;
  font-weight: bold;
}
```

### 关系选择器

1. 后代选择器：" "(空格)
2. 子代选择器：" > "（直接后代）
3. 相邻兄弟选择器：" + "
4. 通用兄弟选择器：" ~ "（不必要相邻）

## 盒模型

盒模型包含：内容（content）、内边距（padding）、边框（border）、外边距（margin）。

```
 -------------------------------
|           margin             |
|  --------------------------  |
|  |         border         |  |
|  |  --------------------  |  |
|  |  |     padding      |  |  |
|  |  |  --------------  |  |  |
|  |  |  |  content   |  |  |  |
|  |  |  --------------  |  |  |
|  |  --------------------  |  |
|  --------------------------  |
 -------------------------------
```

```css
.box {
  width: 350px;
  height: 150px;
  margin: 10px;
  padding: 25px;
  border: 5px solid black;
}
```

方框实际占用的空间宽为 410px（350 + 25 + 25 + 5 + 5），高为 210px（150 + 25 + 25 + 5 + 5）。

### 代替盒模型

要为某个元素使用替代模型，可对其设置 `box-sizing: border-box`：

```css
/* 这样后盒子的实际宽度就是350px */
.box {
  width: 350px;
  padding: 25px;
  box-sizing: border-box;
}
```

### 外边距、内边距和边框

margin、padding 和 border

都有 4 个方向：

- top
- right
- bottom
- left

设置所有边的宽度、样式或颜色，可以使用：

- border-width
- border-style
- border-color

想设置单个边的宽度、样式或颜色，可以和方向组合使用，共 12 种组合

## 层叠、优先级与继承

### 层叠

当应用两条同级别的规则到一个元素的时候，写在后面的就是实际使用的规则。

### 优先级

!important > id 选择器 > 类/属性/伪类选择器 > 元素/伪元素选择器 > 通配符/关系选择器

### 继承

- 一些设置在父元素上的 CSS 属性是可以被子元素继承的，有些则不能。
- 一些属性是不能继承的——举个例子如果你在一个元素上设置 width 为 50% ，所有的后代不会是父元素的宽度的 50% 。

不会被继承的：

- width，height
- padding，margin,border

控制继承：

- `inherit`：继承父元素的样式
- `initial`：使用默认值
- `unset`：将属性重置为自然值，也就是如果属性是自然继承那么就是 inherit，否则和 initial 一样
- `revert`：使用浏览器的默认样式，一般等同于 unset
- `revert-layer`：将应用于选定元素的属性值重置为在上一个层叠层中建立的值。

## 值和单位

- `em`:font-size 时表示“父元素的字体大小”
- `rem`:font-size 时表示“根元素（html）的字体大小”
- `lh`:line-height 时表示“行高”
- `rlh`:line-height 时表示“根元素（html）的行高”
- `%`:百分比

颜色

- `#000000`:十六进制颜色值
- `rgb(2 121 139)`:rgb 颜色值
- `rgb(2 121 139 / .3)`:rgba 颜色值,a 是 0.5

其他颜色的函数[参考](https://developer.mozilla.org/zh-CN/docs/Learn_web_development/Core/Styling_basics/Values_and_units)

`<image>` 值类型用于图像为有效值的任何地方。它可以是一个通过 url() 函数指向的实际图像文件，也可以是一个渐变。

```html
<div class="box image"></div>
<div class="box gradient"></div>
```

```css
.box {
  height: 150px;
  width: 300px;
  margin: 20px auto;
  border-radius: 0.5em;
}
.image {
  background-image: url(https://mdn.github.io/shared-assets/images/examples/big-star.png);
}

.gradient {
  background-image: linear-gradient(90deg, rgb(119 0 255 / 39%), rgb(0 212 255 / 100%));
}
```

位置

`<position>` 值类型表示一组二维坐标，用于定位背景图像等元素（通过 background-position）。它可以接受诸如 top、left、bottom、right 和 center 等关键字，将元素与二维盒子的特定边界对齐，同时还可以使用长度值来表示从盒子顶部和左侧边缘的偏移量。

```css
.box {
  height: 100px;
  width: 400px;
  background-image: url(https://mdn.github.io/shared-assets/images/examples/big-star.png);
  background-repeat: no-repeat;
  background-position: right 40px;
  margin: 20px auto;
  border-radius: 0.5em;
  border: 5px solid rebeccapurple;
}
```

字符串和标识符

- 标识符：上文提到过颜色`red` `goldenrod`关键字
- 字符串：`"hello world"`

函数

- `rgb()`
- `calc()`:加减乘除，[详细参考](https://developer.mozilla.org/zh-CN/docs/Web/CSS/calc)
- `max()` `min()` `clamp()`:最大值 最小值 中间值
- `sin()` `cos()` `tan()`：三角函数
- 等

## 大小

1. 原始尺寸或固有尺寸
2. 指定具体尺寸：果内容的数量超出了元素可容纳的空间，则设置的高度会导致内容溢出。
3. min- 和 max-
4. 视口单位：vw vh vmin vmax，1vh 等于视口高度的 1%，1vw 则为视口宽度的 1%

## 背景与边框

- 背景颜色：background-color
- 背景图片：background-image

```css
.a {
  background-image: url(https://picsum.photos/200/200?random=2);
}
```

控制背景平铺行为:`background-repeat`

- no-repeat——阻止背景重复平铺。
- repeat-x——仅水平方向上重复平铺。
- repeat-y——仅垂直方向上重复平铺。
- repeat——默认值，在水平和垂直两个方向重复平铺。

背景图像的大小:`background-size`

- cover——背景图片会缩放，直到填充整个元素。
- contain——背景图片会缩放，直到它完全显示在元素内。
- auto——背景图片会缩放，直到它完全显示在元素内。
- 值：`<length>` `<percentage>` `cover` `contain` `auto`

背景图像定位:`background-position` (其中方框的左上角是 (0,0)，方框沿水平（x）和垂直（y）轴定位。默认值是 (0,0)。)

- top center right bottom left 等关键字
- 长度和百分比

```css
/* 例：定位在距顶部 20px 和右侧 10px 处 */
.box {
  background-image: url(image.png);
  background-repeat: no-repeat;
  background-position: top 20px right 10px;
}
```

### 渐变背景

```css
.a {
  background-image: linear-gradient(105deg, rgb(0 249 255 / 100%) 39%, rgb(51 56 57 / 100%) 96%);
}

.b {
  background-image: radial-gradient(circle, rgb(0 249 255 / 100%) 39%, rgb(51 56 57 / 100%) 96%);
  background-size: 100px 50px;
}
```

- `linear-gradient`: 线性渐变
- `radial-gradient`: 径向渐变
  - `circle`: 圆形
  - `ellipse`: 椭圆

### 多个背景图片

中间用`,`隔开。需要注意的是图片叠在一起的

```css
a. {
  background-image: url(image1.png), url(image2.png), url(image3.png), url(image4.png);
  background-repeat: no-repeat, repeat-x, repeat;
  background-position: 10px 20px, top right;
}
```

### 背景附加

`background-attachment`：

- `scroll`: 滚动
- `fixed`: 固定
- `local`: 局部

### 边框

```css
/* 下面两段代码等价 */
.box {
  border-top: 1px solid black;
}
.box {
  border-top-width: 1px;
  border-top-style: solid;
  border-top-color: black;
}
```

参数：

- `style`：边框样式
  - `none`: 无边框
  - `hidden`: 隐藏边框
  - `dotted`: 点状边框
  - `dashed`: 虚线边框
  - `solid`: 实线边框
  - `double`: 双线边框
  - `groove`: 槽边框
  - `ridge`: 脊边框
  - `inset`: 凹边框
  - `outset`: 凸边框
- `border-radius`: 边框圆角
- `box-shadow`: 边框阴影
  - `offset-x`: 阴影的 x 坐标偏移量
  - `offset-y`: 阴影的 y 坐标偏移量
  - `blur-radius`: 阴影的模糊半径
  - `spread-radius`: 阴影的扩展半径
  - `color`: 阴影的颜色
  - `inset`: 内阴影
  - `none`: 无阴影
  - `hidden`: 隐藏阴影
  - `initial`: 初始值
  - `inherit`: 继承父元素
  - `transparent`: 透明
  - `currentColor`: 当前颜色
  - `rgb(r, g, b)`: 颜色值

# 文字

## 字体

```css
/* arial字体在任何电脑中都能找到 */
p {
  font-family: arial;
}
```

默认字体：CSS 定义了 5 个常用的字体名称：serif, sans-serif, monospace, cursive, 和 fantasy

字体栈：由于你无法保证你想在你的网页上使用的字体的可用性 (甚至一个网络字体可能由于某些原因而出错), 你可以提供一个字体栈 (font stack)，这样的话，浏览器就有多种字体可以选择了。只需包含一个 font-family 属性，其值由几个用逗号分离的字体名称组成。

```css
p {
  font-family: 'Times New Roman', Times, serif;
}
```

字体大小 `font-size`：

- 绝对单位：px
- 相对单位：
  - em：相对于当前元素
  - rem：相对于根元素

4 种常用的属性:

- `font-style`:斜体
  - `normal`:
  - `italic`: 应用字体的斜体，如果不可以，则使用 oblique
  - `oblique`: 将普通文本倾斜
- `font-weight`:粗体
  - `normal`:
  - `bold`:加粗
  - `bolder`：比父元素更粗
  - `lighter`: 比父元素更细
- `text-transform`: 字母大小写
  - `none`: 不转换
  - `uppercase`: 大写
  - `lowercase`: 小写
  - `capitalize`: 首字母大写
  - `full-width`: 全宽(全角)
- `text-decoration`: 装饰
  - `none`: 无
  - `udnderline`: 下划线
  - `line-through`: 删除线
  - `overline`: 上划线

`text-decoration` 是一个缩写形式，它由`text-decoration-line`, `text-decoration-style` 和 `text-decoration-color` 构成。你可以使用这些属性值的组合来创建有趣的效果，比如 `text-decoration: line-through red wavy`

## 阴影

```css
p {
  text-shadow: 4px 4px 5px red;
}
/* 可以有多个阴影，中间用逗号隔开 */
p {
  text-shadow: -1px -1px 1px #aaa, 0px 4px 1px rgba(0, 0, 0, 0.5), 4px 4px 5px rgba(0, 0, 0, 0.7), 0px 0px 7px rgba(0, 0, 0, 0.4);
}
```

1. x 轴偏移量
2. y 轴偏移量
3. 阴影的模糊半径
4. 阴影的颜色

## 文本布局

- 对齐`text-align`
  - `left`: 左对齐
  - `right`: 右对齐
  - `center`: 居中对齐
  - `justify`: 两端对齐
- 行高`line-height`
  - `line-height: 1.5`:1.5 倍行高
- 字母间距和单词间距 `letter-spacing` `word-spacing`

[其他一些值得看一下的属性](https://developer.mozilla.org/zh-CN/docs/Learn_web_development/Core/Text_styling/Fundamentals#%E5%85%B6%E4%BB%96%E4%B8%80%E4%BA%9B%E5%80%BC%E5%BE%97%E7%9C%8B%E4%B8%80%E4%B8%8B%E7%9A%84%E5%B1%9E%E6%80%A7)

# 排版

## 正常布局

出现在另一个元素下面的元素被描述为块元素，与出现在另一个元素旁边的内联元素不同，内联元素就像段落中的单个单词一样。

display 属性：

- block：块元素，元素前后会带有换行符。
- inline：内联元素，元素前后不会带有换行符。
- inline-block：内联块元素，元素前后不会带有换行符，但是元素内部可以有换行符。
- flex：弹性布局元素。
- grid：网格布局元素。
