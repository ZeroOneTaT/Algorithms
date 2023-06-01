/*
 * @Author: ZeroOneTaT
 * @Date: 2023-05-21 16:44:07
 * @LastEditTime: 2023-05-21 17:25:50
 * @FilePath: \MyTest\sort\heapsort.cc
 * @Description:
 *
 * Copyright (c) 2023 by ZeroOneTaT, All Rights Reserved.
 */
#include <bits/stdc++.h>
using namespace std;

// 建立小根堆 / 大根堆
void heapify(vector<int> &arr, int start, int end)
{
    int i = start;     // 父结点
    int j = i * 2 + 1; // 子节点

    while (j <= end)
    {
        // 选择较大/小的子结点
        if (j + 1 <= end && arr[j] > arr[j + 1])
            ++j;
        // 父结点 >/< 子节点 不调整
        if (arr[i] < arr[j])
            return;
        //  需要调整
        else
        {
            swap(arr[i], arr[j]);
            // 继续向下调整
            i = j;
            j = 2 * i + 1;
        }
    }
}

// 堆排序
void heapsort(vector<int> &arr)
{
    // 初始化堆, 从最后一个父结点调整
    for (int i = arr.size() / 2 - 1; i >= 0; --i)
        heapify(arr, i, arr.size() - 1);
    // 交换堆顶并固定到最后一位，重新调整
    for (int i = arr.size() - 1; i >= 0; --i)
    {
        swap(arr[0], arr[i]);
        heapify(arr, 0, i - 1);
    }
}

// 堆排序
void heapsort_k(vector<int> &arr, int k)
{
    // 建立一个k大小的小根堆
    for (int i = k / 2 - 1; i >= 0; --i)
        heapify(arr, i, k - 1);
    // 调整后面的数据
    for (int i = k; i < arr.size(); ++i)
    {
        if (arr[i] > arr[0])
        {
            swap(arr[0], arr[i]);
            heapify(arr, 0, k - 1);
        }
    }
}

int main()
{
    vector<int> arr = {3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6};
    heapsort_k(arr, 9);
    // for (auto num : arr)
    //     cout << num << ' ';
    cout << arr[0] << endl;
    cout << endl;
    return 0;
}