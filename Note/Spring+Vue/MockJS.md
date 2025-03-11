# MockJS
- Mock.js 是一款前端开发中拦截Ajax请求再生成随机数据响应的工具，可以用来模拟服务器响应.
- 优点是非常简单方便,无侵入性,基本覆盖常用的接口数据类型
- 支持生成随机的文本、数字、布尔值、日期、邮箱、链接、图片、颜色等。
- 安装:npm install mockjs

## 使用
1. 在项目中创建mock目录，新建index.js文件

- Mock.mock( rurl?,rtype?, template|function( options ))
- rurl，表示需要拦截的 URL，可以是 URL 字符串或 URL 正则
- rtype，表示需要拦截的 Ajax 请求类型。例如 GET、POST、PUT、DELETE 等
- template，表示数据模板，可以是对象或字符串
- function，表示用于生成响应数据的函数。
- 设置延时请求到数据
```js
//延时400ms请求到数据
Mock.setup({
    timeout:400
})
//延时200-600毫秒请求到数据
Mock.setup({
    timeout:"200-600"
})
```
2. 在main.js中导入即可
## 数据生成规则
- mock的语法规范包含两层规范:数据模板(DTD)、数据占位符(DPD)
- 数据模板中的每个属性由3 部分构成:属性名name、生成规则rule、属性值value: `'namelrule': value`
- 属性名和生成规则之间用竖线分隔，生成规则是可选的，有7种格式:
```js
'namelmin-max':value
'name|count':value
'name|min-max.dmin-dmax':value
'name|min-max.dcount': value
'name|count.dmin-dmax': value
'name|count.dcount': value
'name|+step': value
```