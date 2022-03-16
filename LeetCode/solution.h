/*
 * @Author: Skye_Liu 
 * @Date: 2021-05-27 16:21:55 
 * @Last Modified by: Skye_Liu
 * @Last Modified time: 2021-05-27 17:25:09
 */
#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <string>
#include <iostream>
#include <string.h>

using namespace std;

class Solution
{
public:
    vector<int> PartionLabels(string S);

    //1404.将二进制表示的数减到1的步骤数
    int NumSteps(string s);

    //前缀树---用于高效地存储和检索字符串数据集中的键
    class Trie
    {
    public:
        Trie()
        {
            is_end = false;
            sid = -1;
            cout << sizeof next << endl;
            memset(next, 0, sizeof next);
        }

        void insert(const string &word, int sid)
        {
            Trie *node = this;
            for (char c : word)
            {
                if (node->next[c - 'a'] == nullptr)
                {
                    node->next[c - 'a'] = new Trie();
                }
                node = node->next[c - 'a'];
            }
            node->is_end = true;
            node->sid = sid;
        }

        int search(const string &word, vector<vector<int>> &res, int pos)
        {
            Trie *node = this;
            for (char c : word)
            {
                node = node->next[c - 'a'];
                if (node == nullptr)
                {
                    return -1;
                }
                if (node->is_end)
                {
                    res[node->sid].push_back(pos);
                }
            }
            return node->sid;
        }

    private:
        Trie *next[26];
        bool is_end;
        int sid;
    };
    //面试题 17.17. 多次搜索
    vector<vector<int>> multiSearch(string big, vector<string> &smalls);
    //面试题 17.15. 最长单词
    string longestWord(vector<string> &words);
    //面试题 17.13. 恢复空格
    int respace(vector<string> &dictionary, string sentence);
    //477. 汉明距离总和
    int totalHammingDistance(vector<int> &nums);
    //面试题 08.14. 布尔运算
    int countEval(string s, int result);
    //525. 连续数组
    int findMaxLength(vector<int> &nums);
};

static int Partition(vector<int> &data, int begin, int end);
void quickSort(vector<int> &data, int begin, int end);

//正则表达式匹配
bool isMatch(string s, string p);

//表示数值的字符串
bool isNumber(string s);

// 字符串的全排列
vector<string> permutation(string s);

int countDigitOne(int n);

// 剑指 Offer 46. 把数字翻译成字符串
int translateNum(int num);

int GetLowerBound(const vector<int> &nums, int target);

int GetUpperBound(const vector<int> &nums, int target);

int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2);

class TestStaticConst
{

public:
    //static int data = 0; //静态成员禁止在类内初始化，这只是声明
    //static double doub = 0.0;
    static const int data = 0; //'静态''常量''整数类型'成员可在声明时赋初值，仍然只是声明不可以取地址
    //static const double doub = 0.0; //非整数类型不可以
    const double db = 0.0;
    static double dd; //只是声明
};

#endif