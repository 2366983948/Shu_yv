- Axios在浏览器端使用XMLHttpRequests发送网络请求，并能自动完成JSON数据的转换。
- 安装: npm install axios
- 地址: https://www.axios-http.cn/
- 官方文档: https://www.axios-http.cn/docs/intro

# axios使用
```js
import axios from 'axios'
```
所有方法：
```js
// 发起一个post请求
axios({
  method: 'post',
  url: '/user/12345',
  data: {
    firstName: 'Fred',
    lastName: 'Flintstone'
  }
});
// 以下方法是封装的
axio.get(url[,config])
axios.post(url[,data[,config]])
axios.put(url[,data[,config]])
axios.delete(url[,config])
axios.head(url[,config])
axios.options(url[,config])
axios.patch(url[,data[,config]])
```
## 生命周期
```html
<script>
export default {
  name: 'App',
  created: function () {
    console.log('创建')
  },
  mounted: function () {
    console.log('挂载')
  }，

  components: {
    HelloWorld,
  }
}
```
### Vue生命周期钩子函数

| 函数        | 描述                   |
|-----------------|----------------------------------|
| beforeCreate()  | Vue实例创建了，但是el和data还没有创建 （准备创建data）               |
| created()       | data数据创建了，但是el挂载点还没有创建 (准备创建el)                  |
| beforeMount()   | el挂载点创建了，但是data数据还没有渲染（准备渲染中）                 |
| mounted()       | data数据 第一次 渲染完毕 (完成初始渲染)                              |
| beforeUpdate()  | 检测到data数据变化，但是还没有开始重新渲染 (data变了，准备重新渲染中) 会执行多次 |
| updated()       | 变化后的data数据 ，完成渲染到页面 （完成重新渲染）会执行多次         |
| beforeDestroy() | Vue实例销毁即将销毁(解除data与el的关联),之后修改data，页面不会被渲染 |
| destroyed()     | Vue实例已经销毁                                                      |

## 后端接口
### 跨域问题
- 为了保证浏览器的安全，不同源的客户端脚本在没有明确授权的情况下，不能读写对方资源，称为同源策略，同源策略是浏览器安全的基石
- 同源策略(Sameoriginpolicy) 是一种约定, 它是浏览器最核心也最基本的安全功能
- 所谓同源(即指在同一个域)就是两个页面具有相同的协议(protocol) ，主机(host) 和端口号(port)
- 当一个请求urI的协议、域名、端口三者之间任意: -个与当前页面urI不同即为跨域，此时无法读取非同源网页的Cookie,无法向非同源地址发送AJAX请求

解决跨域问题：
- CORS(Cross-Origin Resource Sharing)可以在不破坏即有规则的情况下，通过后端服务器实现CORS接口，从而实现跨域通信。

#### 简单请求
- 请求方法: GET、POST、 HEAD
- 除了以下的请求头字段之外，没有自定义的请求头:
    - Accept
    - Accept- Language
    - Content-Language、
    - Last- Event-lD
    - Content-Type
- Content-Type的值只有以下三种: .
    - text/ plain
    - multipart/form-data
    - applicationx-www-form-urlencoded
- 对于简单请求，CORS的策略是请求时在请求头中增加一个Origin字段,
- 服务器收到请求后，根据该字段判断是否允许该请求访问，如果允许，则在HTTP头信息中添加Access-Control-Allow-Origin字段。

#### 非简单请求
- 对于非简单请求的跨源请求，浏览器会在真实请求发出前增加一次OPTION请求,称为预检请求(preflight request)
- 预检请求将真实请求的信息，包括请求方法、自定义头字段、源信息添加到HTTP头信息字段中，询问服务器是否允许这样的操作。
- --
- 服务器收到预检请求后，根据请求头中的Origin字段，判断是否允许该请求访问，如果允许，则返回一个HTTP头信息字段，
- 服务器收到请求时，需要分别对Origin、 Access-Control-Request-Method、
Access-Control-Request-Headers进行验证，验证通过后，会在返回HTTP头
信息中添加:
```
Access-Control-Allow-Origin: http: / /www. test. com
Access-Control-Allow-Methods: GET, POST, PUT,s DELETE
Access-Control-Allow-Headers: X-Cus tom- Header
Access-Control-Al low-Credentials: true
Access-Control-Max-Age: 1 728000
```
- Access-Control-Allow-Methods、Access-Control-Allow-Headers: 真实请求允许的方法、允许使用的字段
- Access-Control-Allow-Credentials:是否允许用户发送、处理cookie
- Access-Control-Max-Age:预检请求的有效期，单位为秒，有效期内不会重新发送预检请求。

#### 后端服务器配置类
方法一
```java
@Configuration
public class CorsConfig implements WebMvcConfigurer {
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        WebMvcConfigurer.super.addCorsMappings(registry);
        registry.addMapping("/**") //允许跨域访问的路径
        .allowedOrigins("*") //允许跨域访问的源
        .allowedMethods ("POST", "GET", "PUT", "OPTIONS", "DELETE") //允许请求方法
        .maxAge (168000)//预检间隔时间
        .allowedHeaders("*") //允许头部设置
        .allowCredentials(true); //是否发送cookie
    }
}
```
方法二
- 直接在控制器前加 `@CrossOrigin`

## 与Vue的结合
```js
//配置请求根路径
axios.defaults.baseURL = 'http://loacalhost:8080'
//将axios作为全局的自定义属性，每个组件可以在内部直接访问(Vue3)
app.config.g1obalProperties.$http = axios
//将axios作为全局的自定义属性，每个组件可以在内部直接访问(Vue2)
Vue.prototype.$http = axios
```
