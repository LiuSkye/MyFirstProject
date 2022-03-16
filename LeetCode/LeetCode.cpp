/*
 * @Author: Skye
 * @Date: 2020-10-23 10:41:24
 * @LastEditTime: 2022-03-16 17:49:15
 * @Description: LeetCode
 * Skye:'Never stop!'
 */

#define CRTDBG_MAP_ALLOC

#include "solution.h"
#include "printf_tools.h"
#include "BinarySearchTree.h"
#include "test.h"
#include "SortAlgorithm.h"
#include "ThreadPool.h"

#include <string>
#include <Windows.h>
#include <crtdbg.h>
#include <map>
#include <functional>
#include <bitset>
#include <algorithm>
#include <cstdio>
#include <array>
#include <iostream>

struct Info
{
    void Print()
    {
        printf("%d,%d,%d\n", &a, &b, &c);
    }
    uint8_t a;
    uint8_t b;
    uint32_t c; //相对结构体首地址的偏移是自身大小的整数倍
};

struct Info2
{
    Info info;
    double b;
};

int countVowelPermutation(int n)
{
    function<int(int)> calK = [&](int m)
    {
        // 计算以i结尾的可能长m序列数，
        if (m == 1)
            return 2;
        return 1;
    };
    function<int(int, int)> CalIPos = [&](int m, int start)
    {
        // 用m个i将序列分为m+1段, 最小间隔1
        // 第一段和最后一段长度可以为0
        if(m == 0) {
            if(start <= n) {
                return 4;
            } else {
                return 1;
            }
        }
        if(start >= n) {
            return 0;
        }
        int res = 0;
        for(int i = start; i < n; i++) {
            res += calK(i - start) * CalIPos(m-1, i+2);
        }
        return res;
    };
    int ret = 4;
    // 最多（n+1）/2个i
    for (int num_i = 1; num_i <= (n + 1) / 2; ++num_i)
    {
        ret += CalIPos(num_i, 0);
    }
    CalIPos(1,1);
    return ret;
}
int main()
{
    countVowelPermutation(3);
    vector<int> houses{1, 2, 3};
    vector<int> heater{2};

    vector<int> nums1{1, 7, 5};
    vector<int> nums2{2, 3, 5};
    // cout << minAbsoluteSumDiff(nums1, nums2) << endl;
    using std::vector;
    vector<int> data{9, 8, 7, 2, 5, 4, 5, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    MakeHeap(data);

    // ThreadPool pool(1);
    // pool.Start();
    // pool.AddTask(std::bind(minAbsoluteSumDiff, nums1, nums2));
    // if (!pool.AddTask([]()
    //                   { cout << "i am excuted in pool!" << endl; }))
    // {
    //     cout << "pool is full!" << endl;
    // }
    // return 0;

    Info info;
    info.Print();
    std::cout << sizeof(Info) << std::endl;
    std::cout << alignof(Info) << std::endl;
    std::cout << sizeof(Info2) << std::endl;
    std::cout << alignof(Info2) << std::endl;

    Solution solution;
    string big("mississippi");
    vector<string> smalls{"is", "ppi", "hi", "sis", "i", "ssippi"};
    solution.multiSearch(big, smalls);

    XCIs<string, Vec> myVec;

    vector<int> te{3, 1, 2, 5, 4, 8, 6, 7, 0};
    // quickSort(te, 0, te.size());
    // BubbleSort(te);
    // InsertSort(te);
    // SelectSort(te);
    // QuickSort(te, 0, te.size());
    MergeSort(te);
    PrintfVec(te);
    return 0;
    int a = -1;
    unsigned int b = (unsigned int)a;
    cout << bitset<32>(a) << "," << bitset<32>(b) << endl;
    unsigned int c = static_cast<unsigned int>(a);
    cout << bitset<32>(c) << endl;

    const int *sptr = &TestStaticConst::data;
    TestStaticConst tsc;
    cout << tsc.db << tsc.dd << endl;
    cout << TestStaticConst::dd << endl;

    Solution *ptr = nullptr;
    cout << &ptr;

    // BSTree<int> tree;
    // tree.insert(8);
    // tree.insert(6);
    // tree.insert(5);
    // tree.insert(7);
    // tree.insert(10);
    // tree.insert(9);
    // tree.insert(11);
    // auto p = tree.search(11);
    // cout << *p << endl;

    vector<int> nn{5, 7, 7, 8, 8, 10};
    auto iter = upper_bound(nn.begin(), nn.end(), 6);
    auto iter2 = lower_bound(nn.begin(), nn.end(), 6);
    cout << iter - iter2 << endl;
    cout << GetLowerBound(nn, 6) << endl;
    cout << GetUpperBound(nn, 6) << endl;

    int anum = -3;
    cout << anum % 2 << endl;
    // char ch1, ch2;
    // cout << "请输入两个字符：" << endl;
    // cin.get(ch1); //或ch1 = cin.get();
    // cin.get(ch2);
    // cout << ch1 << " " << ch2 << endl;
    // cout << (int)ch1 << " " << (int)ch2 << endl;

    // char *str = new char[50];
    // strcpy(str, "123456789047283915946754975847");
    // cout << sizeof str << endl;
    // char *temp = str + 15;
    // str[14] = '\0';
    // delete[] str; //没有内存泄漏
    // cout << temp << endl;
    //////////////////////////////////////
    // int a[8] = {1, 2, 3, 4, 5, 6, 7};
    // int *p = a;
    // p++;
    // cout << *(p + 1) * (p + 1)[2] << endl;

    // system("pause");

    int *nums = new int[20];
    _CrtDumpMemoryLeaks();
    return 0;
}
//test