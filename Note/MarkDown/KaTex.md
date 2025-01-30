# KaTex

## 一、内联公式和显式公式
1. 内联公式 ` $ 1 + 1 = 2 $` 显示为：$1 + 1 = 2$
2. 显式公式 ` $$ a^{2} + b^{2} = c^{2} $$` 显示为：$$ a^{2} + b^{2} = c^{2} $$
## 一、常用数学公式
|运算符|说明|举例|代码|
|-|-|-|-|
|+|加法|$1+1=2$|`$1+1=2$`|
|-|减法|$1-1=0$|`$1-1=0$`|
|*|乘法|$2*2=4$|`$2*2=4$`|
|/|除法|$2/2=1$|`$2/2=1$`|
|^|指数|$2^2=4$|`$2^2=4$`|

1. 极限
```KaTex
lim_{x \to 0} \frac{\sin x}{x} = 1\\
\lim_{n\_\infty} \sum_{k=1}^n \frac{1}{k^2} = \frac{\pi^2}{6}
```
$$ lim_{x \to 0} \frac{\sin x}{x} = 1 $$
$$ 
\lim_{n\_\infty} \sum_{k=1}^n \frac{1}{k^2} = \frac{\pi^2}{6}
$$
2. 符号表示
[typora-math-symbols](https://blog.csdn.net/wait_for_eva/article/details/84307306)
```KaTex
$$
\forall x \in \mathbf{R}:
\qquad 
x^2 \geq \theta
$$ 
$$
x ^2 \geq \theta 
\qquad 
\textrm{for all } x \in \mathbf{R}
$$
```
执行结果：
$$
\forall x \in \mathbf{R}:
\qquad 
x^2 \geq \theta
$$ 
$$
x ^2 \geq \theta 
\qquad 
\textrm{for all } x \in \mathbf{R}
$$

3. 不等式

|运算符|说明|代码|
|-|-|-|
|$\neq$|不等于|`$a \neq b$`|
|$\geq$|大于等于|`$a \geq b$`|
|$\leq$|小于等于|`$a \leq b$`|

4. 平方根
```katex
\sqrt{x} \qquad
\sqrt{x^x + y} \
\sqrt[3]{2} \\[3pt]\\
\surd[x^2 + y^2]
```
$$
\sqrt{x} \qquad
\sqrt{x^x + y} \qquad
\sqrt[3]{2} \\[3pt]\\
\surd[x^2 + y^2]
$$

5. 水平线
```katex
\overline{x^2 + y^2 = 1} \\
\underbrace{ a+b+\cdots +z}_{26}
```
$$
\overline{x^2 + y^2 = 1} \\
\underbrace{ a+b+\cdots +z}_{26}
$$

6. 导数
```katex
y=x^{2}
y'=2x 1
y''=2
```
$$
y=x^{2} \\
y'=2x \\
y''=2
$$

7. 向量
```katex
\vec a
\overrightarrow {AB}
```
$$ 
\vec a \\
\overrightarrow {AB}
$$

8. 点号
```katex
\cdot
```
$$
v_1 = {\sigma}_1 \cdot 2 \\
v_2 = \tau_2 \cdot 2
$$

9. 分数
```katex
\frac{a}{b} \qquad
\frac{1}{x^2+y^2+z^2} \qquad
x^{ \frac{2}{k+1}}
```
$$
\frac{a}{b} \qquad
\frac{1}{x^2+y^2+z^2} \qquad
x^{ \frac{2}{k+1}}
$$

10. 二项系数
```katex
\binom{n}{k} \qquad
\mathrm{C}_ n^k \qquad
\int f_N(x) \stackrel{!}{=}1 \qquad
\sum_ {i=1}^{n}x_ i \\[3px]
\int_ {0}^{\frac{\pi}{2}} \qquad
\prod_\epsilon \\
```
$$
\binom{n}{k} \qquad
\mathrm{C}_ n^k \qquad
\int f_N(x) \stackrel{!}{=}1 \qquad
\sum_ {i=1}^{n}x_ i \\[3px]
\int_ {0}^{\frac{\pi}{2}} \qquad
\prod_\epsilon \\
$$

11. 数学空格调整
```katex
\int\int \\
\int\!\int
```
$$
\int\int \\
\int\!\int
$$

12. 垂直对齐
```katex
\begin{array}{cc}
1 & 2 & 3 
\end{array}
```
```katex
\mathbf{X} = \left(
    \begin{array}{}
    x_{11} & x_{12} & \ldots & x_{1n} \\
    x_{21} & x_{22} & \ldots & x_{2n} \\
    \vdots & \vdots & \ddots & \vdots \\
    x_{m1} & x_{m2} & \ldots & x_{mn}
    \end{array}
\right)
```
$$
\mathbf{X} = \left(
    \begin{array}{}
    x_{11} & x_{12} & \ldots & x_{1n} \\
    x_{21} & x_{22} & \ldots & x_{2n} \\
    \vdots & \vdots & \ddots & \vdots \\
    x_{m1} & x_{m2} & \ldots & x_{mn}
    \end{array}
\right)
$$
```katex
\mathbf{X} = \left\{
    \begin{array}{}
    1 & 2 \\
    a+1  \\
    \textrm{all day }
    \end{array}
\right.
```
$$
\mathbf{X} = \left\{
    \begin{array}{}
    1 & 2 & \\
    a+1  \\
    \textrm{all day }
    \end{array}
\right.
$$

13. 公式编号
```katex
$$
abcd \tag{1}
$$
```
$$
abcd \tag{1}
$$

14. 缩进\quad
15. 粗体
$$
\mu,M \quad \mathbf{M} \quad
\boldsymbol{M}
$$

16. 符号大全 [typora-数学符号](https://blog.csdn.net/wait_for_eva/article/details/84307306)
$$
\alpha
$$
[csdn教学](https://blog.csdn.net/bingteng6859/article/details/104886224?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-4-104886224-blog-104561781.235^v43^pc_blog_bottom_relevance_base6&spm=1001.2101.3001.4242.3&utm_relevant_index=7)