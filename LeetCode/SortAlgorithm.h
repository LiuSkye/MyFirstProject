/*
 * @Author: Skye
 * @Date: 2021-07-06 14:34:19
 * @LastEditTime: 2021-08-09 16:26:20
 * @Description: 各种排序算法
 * Skye:'Never stop!'
 */
#pragma once
#include "printf_tools.h"
#include <functional>
#include <vector>

using namespace std;

// 冒泡排序
template <typename T>
void BubbleSort(vector<T>& nums)
{
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}

// 选择排序
template <typename T>
void SelectSort(vector<T>& nums)
{
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (nums[j] < nums[min_index]) {
                min_index = j;
            }
        }
        swap(nums[i], nums[min_index]);
    }
}

// 插入排序
template <typename T>
void InsertSort(vector<T>& nums)
{
    int n = nums.size();
    for (int i = 1; i < n; ++i) {
        // 当前元素比有序表尾小,需要移动
        if (nums[i] < nums[i - 1]) {
            T temp = nums[i];
            int j = i - 1;
            while (j >= 0 && nums[j] > temp) {
                nums[j + 1] = nums[j];
                --j;
            }
            nums[j + 1] = temp;
        }
    }
}
template <typename T>
int Partition1(vector<T>& data, int begin, int end)
{
    if (data.empty() || begin < 0 || end > data.size()) {
        throw "Invalid Parameters";
        return -1;
    }
    int pivot = data[begin];
    int small = begin;
    int large = end - 1;
    while (small < large) {
        while (small < large && data[large] >= pivot) {
            --large;
        }
        while (small < large && data[small] <= pivot) {
            ++small;
        }
        if (small < large) {
            swap(data[small], data[large]);
        }
    }
    swap(data[small], data[begin]);
    return small;
}

template <typename T>
void QuickSort(vector<T>& nums, int begin, int end)
{
    if (begin >= end)
        return;
    int index = Partition1(nums, begin, end);
    if (index > begin)
        QuickSort(nums, begin, index);
    if (index < end)
        QuickSort(nums, index + 1, end);
    return;
    // function<void(int, int)> partition = [&](int left, int right)
    // {
    //     if (left >= right)
    //     {
    //         return;
    //     }
    //     int start = left, end = right;
    //     //选择基准
    //     int pivot = nums[start];
    //     while (start < end)
    //     {
    //         //小于pivot的放左边,大于pivot的放右边
    //         while (start < end && nums[end] >= pivot)
    //         {
    //             --end;
    //         }
    //         if (start < end)
    //             nums[start++] = nums[end];
    //         while (start < end && nums[start] <= pivot)
    //         {
    //             ++start;
    //         }
    //         if (start < end)
    //             nums[end--] = nums[start];
    //         //swap(nums[start], nums[end]);
    //     }
    //     nums[start] = pivot;
    //     partition(left, start - 1);
    //     partition(start + 1, right);
    // };
    // partition(0, nums.size() - 1);
}

void merge(vector<int>& data, vector<int>& temp, int start, int end)
{
    // 只有一个元素时，停止分割
    if (start >= end - 1)
        return;

    int mid = start + (end - start) / 2;
    merge(temp, data, start, mid);
    merge(temp, data, mid, end);
    // 合并
    int left = start, right = mid;
    int cur_index = start;
    while (left < mid && right < end) {
        if (data[left] < data[right]) {
            temp[cur_index++] = data[left++];
        } else if (data[left] >= data[right]) {
            temp[cur_index++] = data[right++];
        }
    }
    while (left < mid) {
        temp[cur_index++] = data[left++];
    }
    while (right < end) {
        temp[cur_index++] = data[right++];
    }
}
void MergeSort(vector<int>& nums)
{
    int n = nums.size();
    vector<int> temp(nums);
    merge(nums, temp, 0, n);
    temp.swap(nums);
    PrintfVec(temp);
}

class Heap {
public:
    Heap()
        : data(1)
        , size(0)
    {
    }

    void push(int val)
    {
        data.push_back(val);
        int index = data.size() - 1;
        int parent = index / 2;
        while (parent > 0) {
            if (data[parent] < data[index]) {
                swap(data[parent], data[index]);
                index = parent;
                parent = index / 2;
            } else {
                break;
            }
        }
    }
    int pop()
    {
        if (data.size() < 2) {
            throw "error";
            return -1;
        }

        swap(data[1], data.back());
        int res = data.back();
        int index = 1;
        int left = index * 2;
        int right = left + 1;
        int max_num = 0;
        if (left < data.size())
            max_num = data[left];
        if (right < data.size())
            max_num = max(max_num, data[right]);
        data.pop_back();
        while (data[index] < max_num) {
            if (left < data.size() && max_num == data[left]) {
                swap(data[index], data[left]);
                index = left;
            } else if (right < data.size()) {
                swap(data[index], data[right]);
                index = right;
            }
            left = index * 2;
            right = left + 1;
            max_num = 0;
            if (left < data.size())
                max_num = data[left];

            if (right < data.size())
                max_num = max(max_num, data[right]);
        }

        return res;
    }

private:
    vector<int> data;
    int size;
};
// 堆排序-构造小顶堆
void MakeHeap(vector<int>& nums)
{
    // 特点： 数组存储的一颗完全二叉树，第一个位置为空，从尾部插入，上浮到正确位置，交换到尾部弹出
    // vector<int> heap(1);
    Heap heap;
    for (int n : nums) {
        heap.push(n);
    }
    for (int i = nums.size() - 1; i >= 0; --i) {
        nums[i] = heap.pop();
    }
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] << ",";
    }
}