#include "st.hpp"  // 假设你的IntervalMinMax类定义在名为IntervalMinMax.h的头文件中

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>

void testConstruction(const std::vector<int>& nums) {
    IntervalMinMax im(nums);
    std::cout << "Constructed IntervalMinMax with input vector: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void testUpdate(const std::vector<int>& nums) {
    IntervalMinMax im(nums);

    int randomIndex = rand() % nums.size();
    int newValue = rand() % 100;

    std::cout << "Updating element at index " << randomIndex << " from "
              << nums[randomIndex] << " to " << newValue << std::endl;
    im.update(randomIndex, newValue);

    std::cout << "Updated IntervalMinMax:" << std::endl;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i == randomIndex) {
            std::cout << "[" << i << "]: " << newValue << " (updated)";
        } else {
            std::cout << "[" << i << "]: " << nums[i];
        }
        std::cout << " | Range [" << i << ", " << i << "]: (" << im.queryRange(i, i).first << ", " << im.queryRange(i, i).second << ")" << std::endl;
    }
}

void testQueryRange(const std::vector<int>& nums) {
    IntervalMinMax im(nums);

    int left = rand() % nums.size();
    int right = rand() % nums.size();
    if (left > right) {
        std::swap(left, right);
    }

    std::cout << "Querying range [" << left << ", " << right << "] on IntervalMinMax:" << std::endl;
    std::pair<int, int> rangeMinMax = im.queryRange(left, right);
    std::cout << "Min: " << rangeMinMax.first << ", Max: " << rangeMinMax.second << std::endl;

    int manualMin = INT_MAX;
    int manualMax = INT_MIN;
    for (size_t i = left; i <= right; ++i) {
        manualMin = std::min(manualMin, nums[i]);
        manualMax = std::max(manualMax, nums[i]);
    }
    std::cout << "Manual calculation: Min: " << manualMin << ", Max: " << manualMax << std::endl;
    assert(rangeMinMax == std::make_pair(manualMin, manualMax));
}

int main() {
    srand(time(nullptr));

    std::vector<int> nums = {3, 7, 5, 9, 8, 4, 6, 1, 2};

    std::cout << "Testing IntervalMinMax class..." << std::endl;
    std::cout << "-----------------------------" << std::endl;

    testConstruction(nums);
    testUpdate(nums);
    testQueryRange(nums);

    std::cout << "All tests passed." << std::endl;

    return 0;
}