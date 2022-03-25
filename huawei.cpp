
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: 上机编程题
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <vector>
#include <string>
#include <iostream>
#include <functional>
using namespace std;

struct TreeNode
{
    string dir_name;
    vector<TreeNode *> childs;
};

class Solution
{
public:
    // 待实现函数，在此函数中填入答题代码;
    vector<string> DelAllDirectorys(const vector<string> &dirTreeLines)
    {
        vector<string> result;
        // 重建树
        TreeNode *root = nullptr;
        for (auto &line : dirTreeLines)
        {
            string dir_name;
            int level;
            AnalyzeLine(line, dir_name, level);
            if (level == 0)
            {
                root = new TreeNode;
                root->dir_name = dir_name;
            }
            else if (root != nullptr)
            {
                TreeNode *cur = root;
                for (int i = 0; i < level - 1; ++i)
                {
                    if (cur->childs.empty())
                    {
                        break;
                    }
                    cur = cur->childs.back();
                }
                TreeNode *node = new TreeNode;
                node->dir_name = dir_name;
                cur->childs.push_back(node);
            }
        }
        // 后序遍历
        function<void(TreeNode *)> backTrace = [&](TreeNode *node)
        {
            if (node == nullptr)
            {
                return;
            }
            auto &childs = node->childs;
            for (TreeNode *cd : childs)
            {
                backTrace(cd);
            }
            result.push_back(node->dir_name);
            delete node;
            node = nullptr;
        };
        backTrace(root);
        return result;
    }
    void AnalyzeLine(const string &line, string &dir_name, int &level)
    {
        size_t pos = line.find_last_of('-');
        if (pos == string::npos)
        {
            level = 0;
            dir_name = line;
        }
        else
        {
            level = (pos + 1) / 2;
            dir_name = line.substr(pos + 1);
        }
    }
};

// 以下为考题输入输出框架，此部分代码不建议改动
inline string ReadLine()
{
    string line;
    getline(cin, line);
    return line;
}

inline vector<string> ReadLines(int size)
{
    vector<string> lines(size);
    for (int i = 0; i < size; ++i)
    {
        lines[i] = ReadLine();
    }
    return lines;
}

inline vector<string> ReadCountedLines()
{
    string numberLine = ReadLine();
    int count = stoi(numberLine);
    return ReadLines(count);
}

template <typename T>
inline void WriteVector(const vector<T> &objects, char delimeter = ' ')
{
    auto it = objects.begin();
    if (it == objects.end())
    {
        return;
    }
    cout << *it;
    for (++it; it != objects.end(); ++it)
    {
        cout << delimeter << *it;
    }
    cout << endl;
}

int GetMinStep(std::vector<int>& floor)
{
    int n = floor.size();
    if(n <= 1) {
        return 0;
    }
    int cur_pos = 0;
    int cur_right = 0;
    int next_right = 0;
    int step = 0;
    while(cur_pos <= next_right) {
        if(cur_pos > cur_right) {
            step++;
            cur_right = next_right;
        }
        int arrive = cur_pos + floor[cur_pos];
        if(arrive > next_right) {
            next_right = arrive;
        }
        cur_pos++;
        if(next_right >= n - 1) {
            return step+1;
        }
    }
    return -1;
}

int main()
{
    // vector<string> dirTreeLines = ReadCountedLines();
    // Solution solu;
    // auto delDirs = solu.DelAllDirectorys(dirTreeLines);
    // WriteVector(delDirs);
    int n = 0;
    std::cin >>n;
    std::vector<int> nums;
    while(n--) {
        int m = 0;
        std::cin >>m;
        nums.push_back(m);
    }
    std::cout << GetMinStep(nums);
    return 0;
}
