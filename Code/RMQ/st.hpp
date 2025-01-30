#include <vector>
#include<Limits.h>
#include<iostream>

class IntervalMinMax {
public:
    // 构造函数，根据输入数组初始化区间树
    IntervalMinMax(const std::vector<int>& nums) {
        size_t n = nums.size();
        tree.resize(2 * n);
        buildTree(nums, 1, 0, n - 1);
    }

    // 在数组中指定位置更新元素值
    void update(int index, int value) {
        updateTree(index, value, 1, 0, tree.size() / 2 - 1);
    }

    // 查询数组指定区间 [left, right] 内的最大值和最小值
    std::pair<int, int> queryRange(int left, int right) const {
        return queryRangeTree(left, right, 1, 0, tree.size() / 2 - 1);
    }

private:
    std::vector<int> tree;  // 区间树

    // 递归构建区间树
    void buildTree(const std::vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
            return;
        }
        int mid = start + (end - start) / 2;
        buildTree(nums, 2 * node, start, mid);
        buildTree(nums, 2 * node + 1, mid + 1, end);
        tree[node] = std::min(tree[2 * node], tree[2 * node + 1]);
    }

    // 递归更新区间树节点
    void updateTree(int index, int value, int node, int start, int end) {
        if (start == end) {
            tree[node] = value;
            return;
        }
        int mid = start + (end - start) / 2;
        if (index <= mid) {
            updateTree(index, value, 2 * node, start, mid);
        } else {
            updateTree(index, value, 2 * node + 1, mid + 1, end);
        }
        tree[node] = std::min(tree[2 * node], tree[2 * node + 1]);
    }

    // 递归查询指定区间内最大值和最小值
    std::pair<int, int> queryRangeTree(int left, int right, int node, int start, int end) const {
        if (left > end || right < start) {
            return {INT_MAX, INT_MIN};  // 空区间返回默认最大值和最小值
        }
        if (left <= start && right >= end) {
            return {tree[node], tree[node]};  // 当前节点完全覆盖查询区间
        }
        int mid = start + (end - start) / 2;
        auto leftQuery = queryRangeTree(left, right, 2 * node, start, mid);
        auto rightQuery = queryRangeTree(left, right, 2 * node + 1, mid + 1, end);
        return {std::min(leftQuery.first, rightQuery.first), std::max(leftQuery.second, rightQuery.second)};
    }
};