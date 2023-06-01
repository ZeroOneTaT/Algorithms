/*
 * @Author: ZeroOneTaT
 * @Date: 2023-05-31 22:26:41
 * @LastEditTime: 2023-06-01 14:01:26
 * @FilePath: \MyTest\sort\mergesort.cc
 * @Description:  归并排序 MergeSort
 *
 * Copyright (c) 2023 by ZeroOneTaT, All Rights Reserved.
 */

#include <bits/stdc++.h>
using namespace std;

// 1. 递归版归并排序
void merge_sort_recursive(vector<int> &arr, vector<int> &reg, int start, int end)
{
    if (start >= end)
        return;
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    // 分解
    merge_sort_recursive(arr, reg, start1, end1);
    merge_sort_recursive(arr, reg, start2, end2);
    // 合并
    int i = start;
    while (start1 <= end1 && start2 <= end2)
    {
        reg[i++] = arr[start1] <= arr[start2] ? arr[start1++] : arr[start2++];
    }
    while (start1 <= end1)
        reg[i++] = arr[start1++];
    while (start2 <= end2)
        reg[i++] = arr[start2++];
    // 复制到原数组
    for (i = start; i <= end; ++i)
        arr[i] = reg[i];
}

// 2. 迭代版归并排序
void merge_sort_iterative(vector<int> &arr)
{
    int len = arr.size();
    vector<int> reg(len);

    // 从两两排序到，全部一起排序
    for (int seg = 1; seg < len; seg += seg)
    {
        // 从头到尾依次排序
        for (int start = 0; start < len; start += seg + seg)
        {
            int low = start;
            int mid = min(start + seg, len);
            int high = min(start + seg + seg, len);

            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;

            // 依次比较大小，并放入新数组b
            while (start1 < end1 && start2 < end2)
                reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
            while (start1 < end1)
                reg[k++] = arr[start1++];
            while (start2 < end2)
                reg[k++] = arr[start2++];
        }

        // 交换arr,b数组
        vector<int> temp = move(arr);
        arr = move(reg);
        reg = move(temp);
    }

    reg.clear();
}

// 3. 时间换空间，原地归并
void merge_sort_opt1(vector<int> &arr)
{
    int len = arr.size();
    for (int seg = 1; seg < len; seg *= 2) // 当前合并子序列大小， 1——>n/2
    {
        for (int start = 0; start < len; start += 2 * seg) // 标记子数组起点
        {
            int mid = min(start + seg, len);
            int end = min(start + seg + seg, len);

            // 归并
            int k = start;
            int start1 = start, end1 = mid;
            int start2 = mid, end2 = end;

            while (start1 < end1 && start2 < end2)
            {
                // arr[start1] <= arr[start2]， start1 后移
                if (arr[start1] <= arr[start2])
                {
                    ++start1;
                }
                // 否则右移 [start1, start2)数据，arr[start1] = arr[start2]
                else
                {
                    int value = arr[start2];
                    int index = start2;
                    while (index != start1)
                    {
                        arr[index] = arr[--index];
                    }

                    arr[start1] = value;

                    ++start1;
                    ++start2;
                    ++mid;
                }
            }
        }
    }
}

// 4.原地合并，一个数表示两个数
void merge_combine(vector<int> &arr, int left, int mid, int right, int maxval)
{
    int i = left, j = mid + 1;
    int index = left; // 记录归并排序后保存数据的位置
    while (i <= mid && j <= right)
    {
        // arr[i] <= arr[j] ---> ++i, ++index
        if (arr[i] % maxval <= arr[j] % maxval)
        {
            arr[index] = arr[index++] + (arr[i++] % maxval) * maxval;
        }
        // arr[i] > arr[j] ---> ++j, ++index
        else
        {
            arr[index] = arr[index++] + (arr[j++] % maxval) * maxval;
        }
    }
    // 检查剩余部分
    while (i <= mid)
    {
        arr[index] = arr[index++] + (arr[i++] % maxval) * maxval;
    }
    while (j <= right)
    {
        arr[index] = arr[index++] + (arr[j++] % maxval) * maxval;
    }
    // 转换成原始数据，即求 arr[xx]/maxval
    for (i = left; i <= right; ++i)
    {
        arr[i] /= maxval;
    }
}

void merge_sort_rec(vector<int> &arr, int left, int right, int maxval)
{
    if (left >= right)
        return;

    int mid = left + ((right - left) >> 1);
    // 分解
    merge_sort_rec(arr, left, mid, maxval);
    merge_sort_rec(arr, mid + 1, right, maxval);
    // 合并
    merge_combine(arr, left, mid, right, maxval);
}

void merge_sort_opt2(vector<int> &arr)
{
    //  寻找数组最大值
    int maxval = *max_element(arr.begin(), arr.end()) + 1;
    merge_sort_rec(arr, 0, arr.size() - 1, maxval);
}

// 主函数
int main()
{

    vector<int> arr = {4, 5, 6, 7, 8, 4, 9, 3, 1, 2};
    vector<int> reg(arr.size());

    // merge_sort_recursive(arr, reg, 0, arr.size() - 1);
    merge_sort_opt2(arr);

    for (auto num : arr)
        cout << num << " ";

    return 0;
}