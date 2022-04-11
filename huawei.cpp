
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: 上机编程题
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
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

int GetMinStep(std::vector<int> &floor)
{
    int n = floor.size();
    if (n <= 1)
    {
        return 0;
    }
    int cur_pos = 0;
    int cur_right = 0;
    int next_right = 0;
    int step = 0;
    while (cur_pos <= next_right)
    {
        if (cur_pos > cur_right)
        {
            step++;
            cur_right = next_right;
        }
        int arrive = cur_pos + floor[cur_pos];
        if (arrive > next_right)
        {
            next_right = arrive;
        }
        cur_pos++;
        if (next_right >= n - 1)
        {
            return step + 1;
        }
    }
    return -1;
}


class MiniMemoryPool {
public:
    MiniMemoryPool() {
        useful_memory[0] = 100;
    }
    ~MiniMemoryPool() {

    }
    // 返回分配的内存首地址,失败返回 -1
    int Request(int size)
    {
        if(size == 0) {
            return -1;
        }
        int addr = -1;
        for(auto& memo : useful_memory) {
            if(memo.second >= size) {
                addr = memo.first;
                useful_memory[addr + size] = memo.second - size;
                used[addr] = size;
                useful_memory.erase(addr);
                break;
            }
        }
        return addr;
    }
  
    // 释放内存地址, 成功返回 true, 失败返回 false
    bool Release(int startAddr)
    {
        if(used.count(startAddr)) {
            auto iter = useful_memory.lower_bound(startAddr);
            int next_start = iter->first;
            iter--;
            if(iter->first + iter->second == startAddr) {
                iter->second += used[startAddr];
                if(startAddr + used[startAddr] == next_start) {
                    iter->second += useful_memory[next_start];
                    useful_memory.erase(next_start);
                }
            }
            else {
                useful_memory[startAddr] = used[startAddr];
                if(startAddr + used[startAddr] == next_start) {
                    // 可以合并
                    useful_memory[startAddr] += useful_memory[next_start];
                    useful_memory.erase(next_start);
                }
            }
            used.erase(startAddr);
            return true;
        }
        return false;
    }
private:
    map<int,int> useful_memory;
    unordered_map<int,int> used;
};

int Solve25() { 
    int line_count = 0;
    cin >> line_count;
    unordered_map<string, pair<int,int>> memo_f_cnt;
    int result = 0;
    while(line_count--) {
        string y_m_d;
        cin >> y_m_d;
        string h_m_s_f;
        cin >> h_m_s_f;
        string ymdhms = y_m_d+h_m_s_f.substr(0,8);
        int fff = stoi(h_m_s_f.substr(9));
        if(memo_f_cnt.count(ymdhms) == 0) {
            memo_f_cnt[ymdhms] = make_pair(fff, 1);
            ++result;
        } 
        else {
            if(memo_f_cnt[ymdhms].first > fff) {
                result -= memo_f_cnt[ymdhms].second;
                memo_f_cnt[ymdhms] = make_pair(fff, 1);
                ++result;
            }
            else if(memo_f_cnt[ymdhms].first == fff) {
                memo_f_cnt[ymdhms].second++;
                ++result;
            }
        }
    }
    return result;
}


int LeastCommodity(const vector<vector<int>>& input) {
    if(input.empty()) 
        return -1;
    int m = input.size();
    vector<bool> flag(10, false);
    int min_ret = m;
    unordered_set<int> purchase;
    auto Is_Valid = [&]() {
        for(auto f : flag) {
            if(!f) {
                return false;
            }
        }
        return true;
    };
    function<void()> backTrace = [&]() {
        if(Is_Valid()) {
            min_ret = min((int)purchase.size(), min_ret);
            return;
        }
        if(purchase.size() == m) {
            //assert(0);
            return;
        }
        for(int i = 0; i < m; ++i) {
            if(purchase.count(i)) {
                continue;
            }
            purchase.insert(i);
            auto flag_backup = flag;
            for(auto index : input[i]) {
                flag[index] = true;
            }
            backTrace();
            flag = flag_backup;
            purchase.erase(i);
        }
    };
    backTrace();
    return min_ret;
}

class A {
public:
    double x{};
    double y{};
    double z{};
};

template<typename T>
void PrintfData(T&& a) { // 转发引用
    cout << a.x << ", " << a.y << ", " << a.z << endl;
}

int main()
{
    PrintfData(A());
    A a;
    PrintfData(a);
    array arrtest{0,1,2,3,4,5,6,7};
    vector vectest{923,32,234,3423};
    string s("hi\0world");
    cout << s << endl;
    cout << "hi\0word"s << "hi\0word"s.size() << endl;

    unsigned mask = 0b111'000'000;
    
    // vector<string> dirTreeLines = ReadCountedLines();
    // Solution solu;
    // auto delDirs = solu.DelAllDirectorys(dirTreeLines);
    // WriteVector(delDirs);
    //////////////////////////////////////////////////////////////////
    //int n = 0;
    //std::cin >> n;
    // std::vector<int> nums;
    // while (n--)
    // {
    //     int m = 0;
    //     std::cin >> m;
    //     nums.push_back(m);
    // }
    // cout << bitset<sizeof(int) * 8>(1) << endl;
    // std::cout << GetMinStep(nums);
    // set<char> init_res;
    // vector<char> result;
    // for_each(init_res.begin(), init_res.end(), [&](char it)
    //          { result.push_back(it); });
    ///////////////////////////////////////////////////////////////////

    //Solve25();
    return 0;
}
