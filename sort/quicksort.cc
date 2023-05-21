#include <bits/stdc++.h>
using namespace std;

// 快速排序基础版本
void quicksort_0(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;
    // 1. 选择pivot, 这里选最左边
    int pivot = arr[left];
    // 2. 划分子序列
    int i = left;
    int j = right;
    while (i < j)
    {
        while (i < j && arr[j] > pivot)
            --j;
        while (i < j && arr[i] <= pivot)
            ++i;
        if (i < j)
            swap(arr[i], arr[j]);
    }

    // 3. 基准复位
    swap(arr[left], arr[i]);
    // 4. 递归划分子序列
    quicksort_0(arr, left, i - 1);
    quicksort_0(arr, i + 1, right);
}

// 快速排序随机基准改进
void quicksort_1(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;
    // 1. 选择pivot, 这里随机选择
    srand(time(NULL));
    int idx = rand() % (right - left) + left;
    swap(arr[left], arr[idx]);
    int pivot = arr[left];

    // 2. 划分子序列
    int i = left;
    int j = right;
    while (i < j)
    {
        while (i < j && arr[j] > pivot)
            --j;
        while (i < j && arr[i] <= pivot)
            ++i;
        if (i < j)
            swap(arr[i], arr[j]);
    }

    // 3. 基准复位
    swap(arr[left], arr[i]);
    // 4. 递归划分子序列
    quicksort_1(arr, left, i - 1);
    quicksort_1(arr, i + 1, right);
}

// 快速排序随机三元取中改进
void quicksort_2(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;
    // 1. 选择pivot, 这里采用三元取中方法选取
    int mid = left + (right - left) / 2; // 数组中间元素的下标
    if (arr[left] > arr[right])          // 保证左端较小
        swap(arr[left], arr[right]);
    if (arr[mid] > arr[right]) // 保证中间较小
        swap(arr[mid], arr[right]);
    if (arr[mid] > arr[left]) // 保证左端最小
        swap(arr[left], arr[mid]);
    // 此时arr[left]已经为整个序列左中右三个关键字的中间值
    int pivot = arr[left];

    // 2. 划分子序列
    int i = left;
    int j = right;
    while (i < j)
    {
        while (i < j && arr[j] > pivot)
            --j;
        while (i < j && arr[i] <= pivot)
            ++i;
        if (i < j)
            swap(arr[i], arr[j]);
    }

    // 3. 基准复位
    swap(arr[left], arr[i]);
    // 4. 递归划分子序列
    quicksort_2(arr, left, i - 1);
    quicksort_2(arr, i + 1, right);
}

// 快速排序随机三元取中+插入排序改进
void quicksort_3(vector<int> &arr, int left, int right)
{
    // 插入排序优化
    if (right - left + 1 < 10)
    {
        for (int i = left; i <= right; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }

    // 1. 选择pivot, 这里采用三元取中方法选取
    int mid = left + (right - left) / 2; // 数组中间元素的下标
    if (arr[left] > arr[right])          // 保证左端较小
        swap(arr[left], arr[right]);
    if (arr[mid] > arr[right]) // 保证中间较小
        swap(arr[mid], arr[right]);
    if (arr[mid] > arr[left]) // 保证左端最小
        swap(arr[left], arr[mid]);
    // 此时arr[left]已经为整个序列左中右三个关键字的中间值
    int pivot = arr[left];

    // 2. 划分子序列
    int i = left;
    int j = right;
    while (i < j)
    {
        while (i < j && arr[j] > pivot)
            --j;
        while (i < j && arr[i] <= pivot)
            ++i;
        if (i < j)
            swap(arr[i], arr[j]);
    }

    // 3. 基准复位
    swap(arr[left], arr[i]);
    // 4. 递归划分子序列
    quicksort_3(arr, left, i - 1);
    quicksort_3(arr, i + 1, right);
}

// 快速排序随机三元取中+插入排序+双路快排改进
void quicksort_4(vector<int> &arr, int left, int right)
{
    // 插入排序优化
    if (right - left + 1 < 10)
    {
        for (int i = left; i <= right; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }

    // 1. 选择pivot, 这里采用三元取中方法选取
    int mid = left + (right - left) / 2; // 数组中间元素的下标
    if (arr[left] > arr[right])          // 保证左端较小
        swap(arr[left], arr[right]);
    if (arr[mid] > arr[right]) // 保证中间较小
        swap(arr[mid], arr[right]);
    if (arr[mid] > arr[left]) // 保证左端最小
        swap(arr[left], arr[mid]);
    // 此时arr[left]已经为整个序列左中右三个关键字的中间值
    int pivot = arr[left];

    // 2. 划分子序列
    int i = left + 1;
    int j = right;
    while (i <= j)
    {
        while (i <= j && arr[j] > pivot)
            --j;
        while (i <= j && arr[i] < pivot)
            ++i;
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            --j;
            ++i;
        }
    }

    // 3. 基准复位
    // Note: 这里要注意交换的位置，如果是从右往左搜索，最终停留位置在 i, swap(arr[left], arr[i]);
    // 如果是从左往右搜索，最终停留位置在 j, swap(arr[left], arr[j]);
    // 否则会陷入死循环
    swap(arr[left], arr[i]);
    // 4. 递归划分子序列
    quicksort_4(arr, left, i - 1);
    quicksort_4(arr, i + 1, right);
}

// 快速排序随机三元取中+插入排序+三路快排改进
void quicksort_5(vector<int> &arr, int left, int right)
{
    // 插入排序优化
    if (right - left + 1 < 10)
    {
        for (int i = left; i <= right; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }

    // 1. 选择pivot, 这里采用三元取中方法选取
    int mid = left + (right - left) / 2; // 数组中间元素的下标
    if (arr[left] > arr[right])          // 保证左端较小
        swap(arr[left], arr[right]);
    if (arr[mid] > arr[right]) // 保证中间较小
        swap(arr[mid], arr[right]);
    if (arr[mid] > arr[left]) // 保证左端最小
        swap(arr[left], arr[mid]);
    // 此时arr[left]已经为整个序列左中右三个关键字的中间值
    int pivot = arr[left];

    // 2. 划分子序列
    int l = left, r = right;
    int i = left + 1;
    while (i <= r)
    {
        if (arr[i] < pivot) // 跟==v的第一个交换， 维持l为==v的入口位置
            swap(arr[l++], arr[i++]);
        else if (arr[i] == pivot)
            ++i;
        else if (arr[i] > pivot) // 维持r为==v的出口位置
            swap(arr[i], arr[r--]);
    }

    // 3. 递归划分子序列
    quicksort_5(arr, left, l - 1);
    quicksort_5(arr, r + 1, right);
}

int main()
{
    srand(time(nullptr));
    const int N = 1000000;
    vector<int> v(N);
    for (int i = 0; i < N; ++i)
    {
        v[i] = rand() % N;
    }
    cout << "Start sorting..." << endl;
    clock_t start = clock();
    // sort(v.begin(), v.end());
    quicksort_5(v, 0, N - 1);
    clock_t end = clock();
    double seconds = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000);
    cout << "Sort finished in " << seconds << "ms." << endl;
    return 0;
}