# JAVA
[内容参考:菜鸟教程](https://www.runoob.com/java/java-object-classes.html)
- 编译：`javac HelloWorld.java`或`javac -encoding UTF-8 HelloWorld.java`
- 运行：`java HelloWorld`

## 一、Java基础
### 注意
- `大小写敏感`：标识符 Hello 与 hello 是不同的。
- `类名`：如果类名由若干单词组成，那么每个单词的首字母应该大写，例如 MyFirstJavaClass。
- `方法名`：所有的方法名都应该以小写字母开头。如果方法名含有若干单词，则后面的每个单词首字母大写。
- `源文件名`：源文件名必须和类名相同，文件名的后缀为 .java。（如果文件名和类名不相同则会导致编译错误）。
- `主方法入口`：所有的 Java 程序由 public static void main(String[] args) 方法开始执行。
### 标识符
- 所有的标识符都应该以字母（A-Z 或者 a-z）,美元符（$）、或者下划线（_）开始
- 首字符之后可以是字母（A-Z 或者 a-z）,美元符（$）、下划线（_）或数字的任何字符组合
- 关键字不能用作标识符
- 标识符是大小写敏感的
- 合法标识符举例：age、$salary、_value、__1_value
- 非法标识符举例：123abc、-salary

### 修饰符
- `访问控制修饰符` : default, public , protected, private
- `非访问控制修饰符` : final, abstract, static, synchronized

### 变量
- 局部变量
- 类变量（静态变量）
- 成员变量（非静态变量）

### 关键字
| 类别           | 关键字     | 说明                             |
|----------------|------------|----------------------------------|
| 访问控制       | private    | 私有的                           |
|                | protected  | 受保护的                         |
|                | public     | 公共的                           |
|                | default    | 默认                             |
| 类、方法和变量修饰符 | abstract | 声明抽象                         |
|                | class      | 类                               |
|                | extends    | 扩充、继承                       |
|                | final      | 最终值、不可改变的               |
|                | implements | 实现（接口）                     |
|                | interface  | 接口                             |
|                | native     | 本地、原生方法（非 Java 实现）   |
|                | new        | 创建                             |
|                | static     | 静态                             |
|                | strictfp   | 严格浮点、精准浮点               |
|                | synchronized | 线程、同步                     |
|                | transient  | 短暂                             |
|                | volatile   | 易失                             |
| 程序控制语句   | break      | 跳出循环                         |
|                | case       | 定义一个值以供 switch 选择       |
|                | continue   | 继续                             |
|                | do         | 运行                             |
|                | else       | 否则                             |
|                | for        | 循环                             |
|                | if         | 如果                             |
|                | instanceof | 实例                             |
|                | return     | 返回                             |
|                | switch     | 根据值选择执行                   |
|                | while      | 循环                             |
| 错误处理       | assert     | 断言表达式是否为真               |
|                | catch      | 捕捉异常                         |
|                | finally    | 有没有异常都执行                 |
|                | throw      | 抛出一个异常对象                 |
|                | throws     | 声明一个异常可能被抛出           |
|                | try        | 捕获异常                         |
| 包相关         | import     | 引入                             |
|                | package    | 包                               |
| 基本类型       | boolean    | 布尔型                           |
|                | byte       | 字节型                           |
|                | char       | 字符型                           |
|                | double     | 双精度浮点                       |
|                | float      | 单精度浮点                       |
|                | int        | 整型                             |
|                | long       | 长整型                           |
|                | short      | 短整型                           |
| 变量引用       | super      | 父类、超类                       |
|                | this       | 本类                             |
|                | void       | 无返回值                         |
| 保留关键字     | goto       | 是关键字，但不能使用             |
|                | const      | 是关键字，但不能使用             |
|||

`注意`：Java 的 null 不是关键字，类似于 true 和 false，它是一个字面常量，不允许作为标识符使用。
### 注释
- 单行注释：//
- 多行注释：/* */
- 文档注释：/** */ （之后会详细学习）

## 二、对象和类
Java 作为一种面向对象的编程语言，支持以下基本概念：

1、类（Class）：定义对象的蓝图，包括属性和方法。
2、对象（Object）：类的实例，具有状态和行为。
3、继承（Inheritance）：一个类可以继承另一个类的属性和方法。
4、封装（Encapsulation）：将对象的状态（字段）私有化，通过公共方法访问。
```java
private String name; 
public String getName() { return name; }
```
5、多态（Polymorphism）：对象可以表现为多种形态，主要通过方法重载和方法重写实现。
示例：

```java
// 方法重载：
public int add(int a, int b) { ... }
public double add(double a, double b) { ... }
// 方法重写：
@Override public void makeSound() { 
    System.out.println("Meow");
}
```
6、抽象（Abstraction）：使用抽象类和接口来定义必须实现的方法，不提供具体实现。
7、接口（Interface）：定义类必须实现的方法，支持多重继承。
```java
// 抽象类：
public abstract class Shape { abstract void draw(); }
// 接口：
public interface Animal { void eat(); }
```
8、方法（Method）：定义类的行为，包含在类中的函数。
9、方法重载（Method Overloading）：同一个类中可以有多个同名的方法，但参数不同。

### 类中的变量
- 局部变量：在方法、构造方法或者语句块中定义的变量被称为局部变量。变量声明和初始化都是在方法中，方法结束后，变量就会自动销毁。
- 成员变量：成员变量是定义在类中，方法体之外的变量。这种变量在创建对象的时候实例化。成员变量可以被类中方法、构造方法和特定类的语句块访问。
- 类变量：类变量也声明在类中，方法体之外，但必须声明为 static 类型。

### 构造方法
- 每个类都有构造方法。如果没有显式地为类定义构造方法，Java 编译器将会为该类提供一个默认构造方法。
- 在创建一个对象的时候，至少要调用一个构造方法。构造方法的名称必须与类同名，一个类可以有多个构造方法
```java
class Animal{
    public Animal(){
        name = "puppy";
    }
 
    public Animal(String name){
        // 这个构造器仅有一个参数：name
        this.name = name;
    }

    public String getName(){
        return name;
    }

    String name;
}
```
### 创建对象
对象是根据类创建的。在Java中，使用关键字 new 来创建一个新的对象。创建对象需要以下三步：
1. `声明`：声明一个对象，包括对象名称和对象类型。
2. `实例化`：使用关键字 new 来创建一个对象。
3. `初始化`：使用 new 创建对象时，会调用构造方法初始化对象。
### 源文件声明规则
当在一个源文件中定义多个类，并且还有import语句和package语句时，要特别注意这些规则。

- 一个源文件中只能有一个 public 类
- 一个源文件可以有多个非 public 类
- 源文件的名称应该和 public 类的类名保持一致。
- 如果一个类定义在某个包中，那么 package 语句应该在源文件的首行。
- 如果源文件包含 import 语句，那么应该放在 package 语句和类定义之间。如果没有 package 语句，那么
- import 语句应该在源文件中最前面。
- import 语句和 package 语句对源文件中定义的所有类都有效。在同一源文件中，不能给不同的类不同的包声明。

## 三、基本数据类型
### 内置数据类型
Java语言提供了八种基本类型。六种数字类型（四个整数型，两个浮点型），一种字符类型，还有一种布尔型。
| 数据类型 | 描述 | 默认值 |
|-|-|-|
| byte | 8 位有符号整数，范围是 -128 到 127 | 0 |
| short | 16 位有符号整数，范围是 -32768 到 32767 | 0 |
| int | 32 位有符号整数，范围是 -2147483648 到 2147483647 | 0 |
| long | 64 位有符号整数，范围是 -9223372036854775808 到 9223372036854775807 | 0L |
| float | 32 位单精度浮点数 | 0.0f |
| double | 64 位双精度浮点数 | 0.0d |
| char | 16 位 Unicode 字符,最小值是 \u0000（0）最大值是 \uffff（65535） | \u0000 |
| boolean | true 或 false | false |
| 引用类型（类、接口、数组） |  | null |

- `提示`：对于数值类型的基本类型的取值范围，我们无需强制去记忆，因为它们的值都已经以常量的形式定义在对应的包装类中了。[src/PrimitiveTypeTest](../src/PrimitiveTypeTest.java)
- 实际上，JAVA中还存在另外一种基本类型 void，它也有对应的包装类 java.lang.Void，不过我们无法直接对它们进行操作。

#### 类型转换
从容量大的类型转换为容量小的类型时必须使用强制类型转换。
```java
// 自动转换：
// 低  -------------------------->  高
// byte,short,char—> int —> long—> float —> double

// 强制转换：
    int i1 = 123;
    byte b = (byte)i1;//强制类型转换为byte

// 隐含强制类型转换
// 1、 整数的默认类型是 int。
// 2. 小数默认是 double 类型浮点型，在定义 float 类型时必须在数字后面跟上 F 或者 f。
```

### 引用数据类型
- 在Java中，引用类型指向一个对象，指向对象的变量是引用变量。这些变量在声明时被指定为一个特定的类型。变量一旦声明后，类型就不能被改变了。
- 对象、数组都是引用数据类型。
- 所有引用类型的默认值都是null。
- 一个引用变量可以用来引用任何与之兼容的类型。

### Java常量
常量在程序运行时是不能被修改的。在 Java 中使用 final 关键字来修饰常量，声明方式和变量类似
```java
final double PI = 3.1415927;
```
`整数常量`：前缀 0 表示 8 进制，而前缀 0x 代表 16 进制,

#### 字符串常量
```java
char a = '\u0001';
String a = "\u0001";
```
转义字符
| 符号   | 字符含义                      |
|--------|-------------------------------|
| `\n`     | 换行 (0x0a)                   |
| `\r`     | 回车 (0x0d)                   |
| `\f`     | 换页符(0x0c)                  |
| `\b`     | 退格 (0x08)                   |
| `\0`     | 空字符 (0x0)                  |
| `\s`     | 空格 (0x20)                   |
| `\t`     | 制表符                        |
| `\"`     | 双引号                        |
| `\'`     | 单引号                        |
| `\\`     | 反斜杠                        |
| `\ddd`   | 八进制字符 (ddd)              |
| `\uxxxx` | 16进制Unicode字符 (xxxx)      |

## 四、变量
- 局部变量（Local Variables）：局部变量是在方法、构造函数或块内部声明的变量，它们在声明的方法、构造函数或块执行结束后被销毁，局部变量在声明时需要初始化，否则会导致编译错误。
- 实例变量（Instance Variables）：实例变量是在类中声明，但在方法、构造函数或块之外，它们属于类的实例，每个类的实例都有自己的副本，如果不明确初始化，实例变量会被赋予默认值（数值类型为0，boolean类型为false，对象引用类型为null）。
- 静态变量或类变量（Class Variables）：类变量是在类中用 static 关键字声明的变量，它们属于类而不是实例，所有该类的实例共享同一个类变量的值，类变量在类加载时被初始化，而且只初始化一次。
- 参数变量（Parameters）：参数是方法或构造函数声明中的变量，用于接收调用该方法或构造函数时传递的值，参数变量的作用域只限于方法内部。

### Java参数变量
在调用方法时，我们必须为参数变量传递值，这些值可以是常量、变量或表达式。

方法参数变量的值传递方式有两种：`值传递`和`引用传递`。
- 值传递：在方法调用时，传递的是实际参数的值的副本。当参数变量被赋予新的值时，只会修改副本的值，不会影响原始值。Java 中的基本数据类型都采用值传递方式传递参数变量的值。
- 引用传递：在方法调用时，传递的是实际参数的引用（即内存地址）。当参数变量被赋予新的值时，会修改原始值的内容。Java 中的对象类型采用引用传递方式传递参数变量的值。

## 五、修饰符
### 访问修饰符
|范围| private | default | protected | public |
|-|-|-|-|-|
| 同包同类 | √ | √ | √ | √ |
| 同包不同类 |  | √ | √ | √ |
| 不同包子类 |  |  | √ | √ |
| 不同包非子类 |  |  |  | √ |

| 修饰符    | 当前类 | 同一包内 | 孙子类(同一包) | 孙子类(不同包) | 其他包 |
|-----------|-----------|-----------|-----------|-----------|--------|
| public    | Y      | Y        | Y              | Y              | Y      |
| protected | Y      | Y        | Y              | Y/N（说明）     | N      |
| default   | Y      | Y        | Y              | N              | N      |
| private   | Y      | N        | N              | N              | N      |

`说明`：[Java protected 关键字详解](https://www.runoob.com/w3cnote/java-protected-keyword-detailed-explanation.html)

### 非访问修饰符
##### static 修饰符
- 静态变量：static 关键字用来声明独立于对象的静态变量，无论一个类实例化多少对象，它的静态变量只有一份拷贝。 静态变量也被称为类变量。局部变量不能被声明为 static 变量。

- 静态方法：static 关键字用来声明独立于对象的静态方法。静态方法不能使用类的非静态变量。静态方法从参数列表得到数据，然后计算这些数据。

##### final 修饰符
- final 变量：final 表示"最后的、最终的"含义，变量一旦赋值后，不能被重新赋值。被 final 修饰的实例变量必须显式指定初始值。

    final 修饰符通常和 static 修饰符一起使用来创建类常量。

- final 方法: 父类中的 final 方法可以被子类继承，但是不能被子类重写。
- final 类: final 类不能被继承，没有类能够继承 final 类的任何特性。

##### abstract 修饰符
- 抽象类：抽象类不能用来实例化对象，声明抽象类的唯一目的是为了将来对该类进行扩充。
- 抽象方法: 是一种没有任何实现的方法，该方法的具体实现由子类提供。
    - 抽象方法不能被声明成 final 和 static。
    - 任何继承抽象类的子类必须实现父类的所有抽象方法，除非该子类也是抽象类。

##### synchronized 修饰符
- synchronized 关键字声明的方法同一时间只能被一个线程访问。
- synchronized 修饰符可以应用于四个访问修饰符。

##### transient 修饰符
- 序列化的对象包含被 transient 修饰的实例变量时，java 虚拟机(JVM)跳过该特定的变量。
- 该修饰符包含在定义变量的语句中，用来预处理类和变量的数据类型。

##### volatile 修饰符
- volatile 修饰的成员变量在每次被线程访问时，都强制从共享内存中重新读取该成员变量的值。而且，当成员变量发生变化时，会强制线程将变化值回写到共享内存。这样在任何时刻，两个不同的线程总是看到某个成员变量的同一个值。
- 一个 volatile 对象引用可能是 null。

## 六、运算符，循环，条件语句
### 运算符
| 类别   | 操作符                            | 关联性 |
|--------|-----------------------------------|--------|
| 后缀   | `() [] . (点操作符)`              | 左到右 |
| 一元   | `expr++ expr--`                   | 从左到右 |
| 一元   | `++expr --expr + - ～ ！`         | 从右到左 |
| 乘性   | `* /％`                           | 左到右 |
| 加性   | `+ -`                             | 左到右 |
| 移位   | `>> >>>  <<`                      | 左到右 |
| 关系   | `> >= < <=`                       | 左到右 |
| 相等   | `==  !=`                          | 左到右 |
| 按位与 | `＆`                              | 左到右 |
| 按位异或 | `^`                             | 左到右 |
| 按位或 | `|`                               | 左到右 |
| 逻辑与 | `&&`                              | 左到右 |
| 逻辑或 | `| |`                             | 左到右 |
| 条件   | `？：`                            | 从右到左 |
| 赋值   | `= + = - = * = / =％= >> = << =＆= ^ = | =` | 从右到左 |
| 逗号   | `，`                              | 左到右 |

#### instanceof 运算符
该运算符用于操作对象实例，检查该对象是否是一个特定类型（类类型或接口类型）。
```java
String name = "James";
boolean result = name instanceof String; // 由于 name 是 String 类型，所以返回真
```

### 循环
- while 循环
- do…while 循环
- for 循环
- 增强 for 循环
    ```java
        for(声明语句 : 表达式)
        {
            //代码句子
        }
    ```

### 条件语句
```java
if(条件){

}
else if(条件){

}
else{ 

}
switch(表达式){
    case 常量值1: 

        break;
    case 常量值2: 
        break;
    default: 
        break;
}
```

## 