# RMQ （Range Minimum/Maximum Query）

[文章链接](https://www.cnblogs.com/stelayuri/p/12683318.html)

## 区间最值查询问题的一般解法
1. 常见解法有朴素算法——O(n)预处理、O(n)查询，总体复杂度O(n+nq)
2. 线段树——O(nlogn)预处理、O(logn)查询，总体复杂度O((n+q)logn)
3. ST算法——O(nlogn)预处理、O(1)查询，总体复杂度O(nlogn+q)
4. 树状数组——O(nlogn)预处理、O(logn)查询，总体复杂度O(nlogn+q)
5. 离散化——O(nlogn)预处理、O(1)查询，总体复杂度O(nlogn+q)

## ST算法
ST算法是基于倍增算法与动态规划的一个解决静态区间RMQ的算法

忽略朴素算法，与线段树进行对比:
- 优点是查询的时间复杂度为线性，对于查询多的题型有利
- 缺点是只支持对静态区间的查询（初始化后就不能修改值），且空间复杂度在大部分情况下比线段树要大（线段树保守情况为O(4n)，ST算法为O(nlogn)）

