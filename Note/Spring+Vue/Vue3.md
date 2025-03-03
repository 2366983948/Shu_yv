# Vue3
前端框架

[官方教程](https://cn.vuejs.org/guide/essentials/application.html)
## 入门
有多种写法，具体请看官方教程
```html
<!DOCTYPE html> 
<html lang = "en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0"></meta>
    <title>Document</title>
    <script src="https://unpkg.com/vue@3/dist/vue.global.js"></script>
</head>
<body>
    <div id="app">{{ message }}</div>

    <script>
        const { createApp, ref } = Vue

        createApp({
            setup() {
                const message = ref('Hello vue!')
                return {
                    message
                }
            }
        }).mount('#app')
    </script>
</body>
</html>
```

其他9种经典案例请查看[Vue案例](./Vue案例/)

## 组件
### NPM使用
- NPM (Node Package Manager)是一个NodeJS包管理和分发工具。
- NPM最常见的用法就是用于安装和更新依赖（功能类似Maven）。要使用NPM,首先要安装Node工具。
----
- Node.js是一个基于Chrome V8引擎的JavaScript运行时环境。
- Node中包含了NPM包管理工具。
- [下载地址:https://nodejs.org/zh-cn/]( https://nodejs.org/zh-cn/)

`npm install`:安装package.json文件中的依赖
### Vue CLI使用
- Vue CLI是Vue官方提供的构建I具，通常称为脚手架。
- 用于快速搭建一个带有热重载 (在代码修改后不必刷新页面即可呈现修改后的效果)及构建生产版本等功能的单页面应用。
- Vue CLI基于webpack构建，也可以通过项目内的配置文件进行配置。
- 安装: `npm install -g @vue/cli`(-g代表全局安装)

使用`vue create hello`指令创建一个项目
1. 选第三个
```
? Please pick a preset:
  Default ([Vue 3] babel, eslint)
  Default ([Vue 2] babel, eslint)
> Manually select features
```
2. 按space取消linter
```
Vue CLI v5.0.8
? Please pick a preset: Manually select features
? Check the features needed for your project: (Press <space> to select, <a> to toggle all, <i> to invert selection, and
<enter> to proceed)
>(*) Babel
 ( ) TypeScript
 ( ) Progressive Web App (PWA) Support
 ( ) Router
 ( ) Vuex
 ( ) CSS Pre-processors
 ( ) Linter / Formatter
 ( ) Unit Testing
 ( ) E2E Testing
```
3. 选择3.x
4. 选`In package.json`
5. 要不要创建快照
### 组件化开发

参考[components文件夹](../../hello/src/components/)

#### 组件传值
1. 直接使用自己 script 标签的 变量
2. 使用 props 外部传值
```html
<template>
  <div>
    <h1>{{ msg }}</h1>
    <h1>{{ title }}</h1>
  </div>
</template>

<script>
    export default {
        name: 'Movie',
        props: {
            msg: String
        },
        data:function(){
            return {
                title:'电影名'
            }
        }
    }
</script>
```
3. 两个组件之间传递数据
vux会单独介绍
### Element UI

- Element是国内饿了么公司提供的一套开源前端框架，简洁优雅，提供了Vue、React、Angular等多个版本。
- 文档地址: https://element.eleme.cn/#/zh-CN/
- 安装: `npm i element-ui`

```javascript
//这里是vue2 的程序
import Vue from 'vue'
import App from './App.vue'
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'

Vue.config.productionTip = false
Vue.use(ElementUI)
new Vue({
  render: h => h(App),
}).$mount('#app')

```
### 第三方图标库
- 由于Element Ul提供的字体图符较少，一-般会采用其他图表库，如著名的Font Awesome
- Font Awesome提供了675个可缩放的矢量图标，可以使用CSS所提供的所有特性对它们进行更改，包括大小、颜色、阴影或者其他任何支持的效果。
- 文档地址: http://fontawesome.dashgame.com/
- 安装: npm install font-awesome
- 使用: import 'font- awesome/css/font- awesome.min.css'

## Axios网络请求
