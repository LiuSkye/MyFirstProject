/*
 * @Author: Skye
 * @Date: 2020-10-23 10:41:24
 * @LastEditTime: 2021-06-29 09:47:56
 * @Description: LeetCode
 * Skye:'Never stop!'
 */

#define CRTDBG_MAP_ALLOC

#include "solution.h"
#include "printf_tools.h"
#include "BinarySearchTree.h"

#include <string>
#include <Windows.h>
#include <crtdbg.h>
#include <map>
#include <functional>
#include <bitset>
#include "test.h"
#include <algorithm>
#include <cstdio>

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

int main()
{
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
    quickSort(te, 0, te.size());
    PrintfVec(te);

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

    BSTree<int> tree;
    tree.insert(8);
    tree.insert(6);
    tree.insert(5);
    tree.insert(7);
    tree.insert(10);
    tree.insert(9);
    tree.insert(11);
    auto p = tree.search(11);
    cout << *p << endl;

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

    //system("pause");
    int *nums = new int[20];
    _CrtDumpMemoryLeaks();
    return 0;
}