# MybatisPlus
`数据库账户`：root
`密码`：123456
## ORM 基本概念
- ORM (Object Relational Mapping,对象关系映射)是为了解决面向对象与关系数据库存在的互不匹配现象的一种技术。
- ORM通过使用描述对象和数据库之间映射的元数据将程序中的对象自动持久化到关系数据库中。
- ORM框架的本质是简化编程中操作数据库的编码。

## Mybatis-Plus介绍
- MyBatis是一款优秀的数据持久层ORM框架，被广泛地应用于应用系统。
- MyBatis能够非常灵活地实现动态SQL，可以使用XML或注解来配置和映射原生信息，能够轻松地将Java的POJO (Plain Ordinary Java Object,普通的Java对象)与数据库中的表和字段进行映射关联。
- MyBatis-Plus是一个MyBatis的增强工具，在MyBatis的基础上做了增强，简化了开发。

### 全局配置
```xml
<!-- MyBatisPlus依赖 (使用spring2.x 版本)-->
<dependency>
    <groupId>com.baomidou</groupId>
    <artifactId>mybatis-plus-boot-starter</artifactId>
    <version>3.4.2</version>
</dependency>
<!-- MyBatisPlus依赖 (使用spring3.x 版本)-->
<dependency>
    <groupId>com.baomidou</groupId>
    <artifactId>mybatis-plus-spring-boot3-starter</artifactId>
    <version>3.5.7</version>
</dependency>

<!-- mysq1驱动依赖 -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>5.1.47</version>
</dependency>
<!-- 数据连接池druid -->
<dependency>
    <groupId>com.alibaba</groupId>
    <artifactId>druid-spring-boot-starter </artifactId>
    <version>1.1.20</version>
</dependency>
```
```properties
# 指定数据库连接池
spring.datasource.type=com.alibaba.druid.pool.DruidDataSource
# 指定数据库驱动
spring.datasource.driver-class-name=com.mysql.jdbc.Driver
# 指定数据库连接地址
spring.datasource.url=jdbc:mysql://localhost:3306/mydb?useSSL=false
# 指定数据库用户名 密码
spring.datasource.username=root
spring.datasource.password=123456
# 指定日志输出格式
mybatis-plus.configuration.log-impl=org.apache.ibatis.logging.stdout.StdOutImpl
```

### 添加@MapperScan注解
```java
@SpringBootApplication
@MapperScan("com.xxx.mapper")
public class MybatisPlusApplication {
    public static void main(String[] args) {
        SpringApplication.run(MybatisPlusApplication.class, args);
    }
}

//数据库相关操作都要放到mapper包下
//MapperScan("com.xxx.mapper") 指明mappper包在何处
```
## Mybatis-Plus CURD
简单的说，Mybatis-Plus就是一个接口，供Controller层调用，实现数据库的增删改查。

使用步骤：
1. 按照上面添加配置和依赖
2. 创建一个mapper包（存放所有mapper接口）。并在启动类前添加注解
```java
// 这个注解是扫描mapper包下的所有接口
@MapperScan("com.example.demo.mapper")
public class DemoApplication {
	public static void main(String[] args) {
		SpringApplication.run(DemoApplication.class, args);
	}
}
```
3. 创建mappper接口

|注解|作用|
|----|----|
|@Insert|插入数据|
|@Delete|删除数据|
|@Update|修改数据|
|@Select|查询数据|
|@Result|实现结果封装集|
|@Results|封装多个结果集|
|@One|一对一结果集封装|
|@Many|一对多结果集封装|

```java
// 数据库中已有user表，有id,username,password三个字段
// 注意：mybatis-plus 默认user类内的属性和数据库字段名一致，可以手动修改exist属性为false表示数据库中没有该字段；

public interface UserMapper{
    @Insert("insert into user values(#{id},#{username},#{password})")
    public int insert(User user);
    @Delete("delete from user where id=#{id}")
    public int delete(int id);
    @Update("update user set username=#{username},password=#{password} where id=#{id}")
    public int update(User user);
    @Select("select * from user where id=#{id}")
    public User select(int id);
    @Select("select * from user")
    public List<User> selectAll();
}

//以上是mybatis的写法。
//Mybatis-Plus的写法
public interface UserMapper extends BaseMapper<User>{

}
// BaseMapper 提供了增删改查的方法，前提是要有和User同名的数据库
```
4. 在Controller层注入mapper接口
```java
    @Autowired
    private UserMapper userMapper;
    // @Autowired 是spring的功能，它可以自动注入对象，不需要我们自己new对象。

    //下面是使用接口
    @GetMapping("/users")
    public String Search(){
        List<User> list = userMapper.selectAll();
        return "查询用户";
    }
```
