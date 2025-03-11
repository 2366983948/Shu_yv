# VueRouter
[官网](https://router.vuejs.org/zh/guide/)
- Vue路由vue-router是官方的路由插件，能够轻松的管理 SPA 项目中组件的切换。
- Vue的单页面应用是基于路由和组件的，路由用于设定访问路径，并将路径和组件映射起来。
- vue-router 目前有 3.x的版本和 4.x的版本，vue-router 3.x 只能结合 vue2进行使用，vue-router 4.x 只能结合 vue3 进行使用
- 安装:npm install vue-router@4

## 使用步骤
1. 完成各个页面,并在app.vue中引入(不需要把组件引入到app.vue中)
```html
<template>
  <div id="app">
    <router-link to="/test1">前往测试1</router-link>
    <router-link to="/test2">前往测试2</router-link>
    <router-view></router-view>
  </div>
</template>
```
2. 在项目下创建router文件夹，在router文件夹下创建index.js文件
```js
// index.js
// 其中名称可以随意，如果是index的话，在别的地方导入的时候就不需要再写index了
import Vue from 'vue'
import VueRouter from 'vue-router'

Vue.use(VueRouter)


const router = new VueRouter({
  routes: [
    {
        path: '/',
        redirect: '/test1',
    },
    {
      path: '/test1',
      name: 'test1',
      component: () => import('../components/View/test1.vue')
    },
    {
      path: '/test2',
      name: 'test2',
      component: () => import('../components/View/test2.vue')
    }
  ]
})

export default router
```
3. 在main.js中引入router
```js
import routers from './router'
new Vue({
  render: h => h(App),
  router: routers   // 如果key,val一致，可以直接写成router
}).$mount('#app')
```

## 重定向
```js
    {
        path: '/',
        redirect: '/test1',
    },
```
## 嵌套路由
```js
{
    path: '/test1',
    name: 'test1',
    component: () => import('../components/View/test1.vue'),
    children:[
        {
            path: '/test1/test1_1',
            name: 'test1_1',
            component: () => import('../components/View/test1_1.vue')
        },
        {
            path: '/test1/test1_2',
            name: 'test1_2',
            component: () => import('../components/View/test1_2.vue')
        },
    ]
},
```

## 动态路由
```html
<template>
    <div>
        <H1 >test2</H1>
        <router-link to="/test2/1">前往1</router-link>
        <router-link to="/test2/2">前往2</router-link>
        <router-link to="/test2/3">前往3</router-link>
        <router-link to="/test2/4">前往4</router-link>
        <router-view></router-view>
    </div>
</template>
```
```js
    {
        path: '/test2',
        name: 'test2',
        component: () => import('../components/View/test2.vue'),
        children:[
            {
                path: ':id',
                name: 'goods',
                component: () => import('../components/View/goods.vue')
            }
        ]
    }

    // 在goods.vue中，可以通过 {{$route.params.id}} 获取到路由参数
```

### 简化方式
```js
{
    path: ':id',
    name: 'goods',
    component: () => import('../components/View/goods.vue'),
    props: true
}
```
```js
export default {
    props: [id]
}
//这样就可以用 this.id 获取到路由参数了
```
## 编程式路由
声明式
```html
<router-link to="/test2/1">前往1</router-link>
```
编程式
```js
this.$router.push('/test2/1')
```
## 路由守卫
- 导航守卫可以控制路由的访问权限。（类似后端的拦截器）

你可以使用 router.beforeEach 注册一个全局前置守卫：
```js
router.beforeEach((to, from [,next])=> {
  if(to.path === '/test2' && !isLogin ){
    next("/login")  // 跳转到登录页面
  }else{
    next() // 执行默认行为，即前往 to 的目标
  }
  // 返回 false 以取消导航
  return false
})
```