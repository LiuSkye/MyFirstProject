
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
#include <any>
#include <chrono>
#include <stack>
#include <utility>
#include <bitset>
#include <numeric>
// #include <execution>
#include <fstream>
#include <sstream>
#include <math.h>
#include "LeetCode/printf_tools.h"
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


    // 待实现函数，在此函数中填入答题代码;
    string CharacterSort(const string &inputStr)
    {
        string result = inputStr;
        int len = result.size();
        vector<int> num_pos;
        vector<int> let_pos;
        for(int i = 0; i < len; ++i) {
            if(result[i] >= '0' && result[i] <= '9') {
                num_pos.push_back(i);
            }
            else {
                let_pos.push_back(i);
            }
        }
        for(int j = 0; j < num_pos.size(); ++j) {
            int i = 0;
            while(i < num_pos.size() - 1) {
                if(result[num_pos[i]] > result[num_pos[i + 1]]) {
                    swap(result[num_pos[i]], result[num_pos[i+1]]);
                }
                ++i;
            }            
        }
        auto needSwap = [](char c1, char c2)->bool {
            if(c1 < c2) {
                return (c1 < 'a' && c2 < 'a') || (c1 >= 'a' && c2 >= 'a');
            }
            if(c1 > c2) {
                return !((c1 < 'a' && c2 < 'a') || (c1 >= 'a' && c2 >= 'a'));
            }
            return false;
        };
        for(int j = 0; j < let_pos.size(); ++j) {
            int i = 0;
            while(i < let_pos.size() - 1) {
                if(needSwap(result[let_pos[i]], result[let_pos[i + 1]])) {
                    swap(result[let_pos[i]], result[let_pos[i+1]]);
                }
                ++i;
            }
        }
        return result;
    }


bool Calculate(const string &expression, int& result)
{
    stack<int> cals;
    int start = 0, flag = 1;
    for(int i = 0; i < expression.size(); ++i) {
        char c = expression[i];
        if(c == '+' || c == '-') {
            if(start < i)
                cals.push(stoi(expression.substr(start, i - start)) * flag);
            start = i + 1;
            flag = (c == '+') ? 1 : -1;
        }
        if(c == '*' || c == '/') {
            if(start < i)
                cals.push(stoi(expression.substr(start, i - start)) * flag);
            start = i + 1;
            int j = i + 1;
            while(j < expression.size()) {
                if(expression[j] >= '0' && expression[j] <= '9')
                    ++j;
                else
                    break;
            }
            int left = cals.top();
            int right = stoi(expression.substr(start, j - start));
            if(c == '/' && right == 0) {
                return false;
            }
            if(c == '*') 
                left *= right;
            else
                left /= right;
            cals.pop();
            cals.push(left);
            i = j - 1;
            start = j + 1;
        }
    }
    if(start <= expression.size()) {
        cals.push(flag * stoi(expression.substr(start)));
    }
    while(!cals.empty()) {
        result += cals.top();
        cals.pop();
    }
    return true;
}

bool Calculate2(const string &expression, int& result)
{
    stack<int> nums;
    int start = 0;
    char pre_operator{'+'};
    for(int i = 0; i < expression.size(); ++i) {
        char c = expression[i];
        if(c >= '0' && c <= '9' && i < expression.size() - 1) {
            continue;
        }
        if(i == 0) {
            pre_operator = c;
            start = i + 1;
            continue;
        }
        int cur_num = stoi(expression.substr(start, i == nums.size() -1 ? 
            i - start : (i - start + 1)));
        start = i + 1;
        // if(pre_operator == '+') {
        //     nums.push(cur_num);
        // }
        // else if(pre_operator == '-') {
        //     nums.push(-cur_num);
        // }
        // else {
        //     int left = nums.top();
        //     if(pre_operator == '*') {
        //         left *= cur_num;
        //     }
        //     else if(cur_num == 0) {
        //         return false;
        //     }
        //     else {
        //         left /= cur_num;
        //     }
        //     nums.pop();
        //     nums.push(left);
        // }
        switch(pre_operator) {
            case'+': {
                nums.push(cur_num);
                break;
            }
            case '-': {
                nums.push(-cur_num);
                break;
            }
            case '*': {
                int left = nums.top();
                left *= cur_num;
                nums.pop();
                nums.push(left);
                break;
            }
            case '/': {
                int left = nums.top();
                if(cur_num == 0)
                    return false;
                left /= cur_num;
                nums.pop();
                nums.push(left);
                break;
            }
            cout << "test" << endl;
        }
        pre_operator = c;
    }
    while(!nums.empty()) {
        result += nums.top();
        nums.pop();
    }
    return true;
}

int BinaryToDecimal(const string &binaryString)
{
    int result;
    bitset<32> num;
    int j = 0;
    for(int i = binaryString.size() - 1; i >= 0; --i) {
        num[j++] = binaryString[i] - '0';
    }
    result = num.to_ulong();
    return result;
}

vector<int> huaweiSolver(const vector<vector<int>>& input, const vector<int>& request) {
    // cpuCount  memory  cpuArch  NP
    auto Is_Valid = [&](const vector<int>& computer)->bool {
        if(request[2] > computer[0] || request[3] > computer[1]) {
            return false;
        }
        if(computer[2] != request[4] && request[4] != 9) {
            return false;
        }
        if(computer[3] != request[5] && request[5] != 2) {
            return false;
        }
        return true;
    };
    auto strategy1 = [&](int a, int b)->bool {
        if(input[a][0] < input[b][0])
            return true;
        if(input[a][0] == input[b][0])
            return input[a][1] < input[b][1];
        return false;
    };
    auto strategy2 = [&](int a, int b)->bool {
        if(input[a][1] < input[b][1])
            return true;
        if(input[a][1] == input[b][1])
            return input[a][0] < input[b][0];
        return false;
    };
    
    // 最大分配数量N 、策略
    vector<int> result;
    for(int i = 0; i < input.size(); ++i) {
        if(Is_Valid(input[i])) {
            result.push_back(i);
        }
    }
    if(request[1] == 1)
        sort(result.begin(), result.end(), strategy1);
    else 
        sort(result.begin(), result.end(), strategy2);
    if(result.size() > request[0]) {
        result.resize(request[0]);
    }
    sort(result.begin(), result.end());
    return result;
}

int BinarySearchLowerBound(const vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while(left <= right) {
        int mid = left + (right - left)/2;
        if(nums[mid] < target) {
            left = mid + 1;
        }
        else if(nums[mid] >= target) {
            right = mid - 1;
        }
    }
    return left;
}

int GetMinPeople(int questionsCount, int peopleCount, const vector<pair<int, int>>& correctRanges)
{
    vector<int> start_maxlength(questionsCount + 1);
    for(auto& range : correctRanges) {
        start_maxlength[range.first] = max(start_maxlength[range.first], range.second);
    }
    int people_num = 0;
    int can_arrive = 1;
    int cur_pos = 1;
    while(can_arrive <= questionsCount) {
        int right = can_arrive;
        for(int i = cur_pos; i <= right; i++) {
            can_arrive = max(can_arrive, start_maxlength[i] + 1);
        }
        if(right == can_arrive) {
            return -1;
        }
        cur_pos = right;
        people_num++;
    }
    return people_num;
}
string GetHexString(long long input)
{
    if(input < INT_MIN || input > UINT32_MAX) {
        return "overflow";
    }
    bitset<32> bin_input(input);
    string hex_input{"00 00 00 00"};
    int j = hex_input.size() - 1;
    for(int i = 0; i < bin_input.size(); i += 4) {
        int dec = bin_input[i] + bin_input[i+1] * 2 +
                  bin_input[i+2] * 4 + bin_input[i+3] * 8;
        hex_input[j--] = (dec < 10) ? ('0' + dec) : ('A' + dec - 10);
        if(j == 2 || j == 5 || j == 8) { // 跳过空格
            --j;
        }
    }
    string result;
    result.append(hex_input);
    result.append(1, '\n');
    // 转换成小端字节序
    swap(hex_input[0], hex_input[9]);
    swap(hex_input[1], hex_input[10]);
    swap(hex_input[3], hex_input[6]);
    swap(hex_input[4], hex_input[7]);
    result.append(hex_input);
    return result;
}

size_t GetIpCount(const std::string& numChars)
{
    vector<int> nums(10);
    for(char c : numChars) {
        nums[c - '0'] = 1;
    }
    int count = accumulate(nums.begin(), nums.end(), 0);
    size_t valid_num = 0;
    int first_bit = 0;
    if(nums[0] == 0) {
        valid_num += count;
    }
    valid_num += count*count;
    if(nums[1] == 1) {
        valid_num += count*count;
    }
    int less_five = nums[0] + nums[1] + nums[2] + nums[3] + nums[4];
    if(nums[2] == 1) {
        valid_num += less_five*count;
        if(nums[5] == 1) {
            valid_num += less_five + nums[5];
        }
    }
    return pow(valid_num, 4);
}
vector<string> GetAllFault(const vector<string> &arrayA, const vector<string> &arrayB)
{
    set<string> visited;
    vector<string> result;
    for(const string& warn : arrayA) {
        visited.insert(warn);
    }
    for(const string& warn : arrayB) {
        visited.insert(warn);
    }
    for_each(visited.begin(), visited.end(), [&](const string& warn){
        result.emplace_back(warn);
    });
    return result;
}
int main()
{
    cout << (int)'0' << endl;
    ////////////////////////////////////////////////////////////////
    // 并行执行
    vector<double> v(10000000, 0.0625);
    {
        auto t1 = chrono::high_resolution_clock::now();
        double result = accumulate(v.begin(), v.end(), 0.0);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms = t2-t1;
        cout << "accumulate: result" << result << "took "
            <<ms.count() <<"ms" << endl;
    }
    {
        // auto t1 = chrono::high_resolution_clock::now();
        // double result = reduce(execution::par, v.begin(), v.end());
        // auto t2 = chrono::high_resolution_clock::now();
        // chrono::duration<double, milli> ms = t2-t1;
        // cout << "reduce: result" << result << "took "
        //     <<ms.count() <<"ms" << endl;
    }
    ////////////////////////////////////////////////////////////////
    PrintfData(A());
    A a;
    PrintfData(a);
    array arrtest{0,1,2,3,4,5,6,7};
    vector vectest{923,32,234,3423};
    swap(vectest[0], vectest[1]);
    string s("hi\0world");
    cout << s << endl;
    cout << "hi\0word"s << "hi\0word"s.size() << endl;
    
    unsigned mask = 0b111'000'000;
    
    //////////////////////////////////////////////////////////////////
    // cout << bitset<sizeof(int) * 8>(1) << endl;
    // std::cout << GetMinStep(nums);
    // set<char> init_res;
    // vector<char> result;
    // for_each(init_res.begin(), init_res.end(), [&](char it)
    //          { result.push_back(it); });
    ///////////////////////////////////////////////////////////////////
    // ifstream in("D:/liusk.txt");
    // string line;
    // vector<double> nums;
    // stringstream ls;
    // while(getline(in, line)) {
    //     string word;
    //     ls.str(line);
    //     while(getline(ls, word, ',')) {
    //         double num{};
    //         num = stod(word);
    //         nums.push_back(num);    
    //     }
    //     ls.clear();
    // }
    // in.close();
    vector<vector<int>> input{{2,200,0,1},
                              {4,330,2,1},
                              {3,400,3,1},
                              {3,310,1,1},
                              {3,320,8,1},
                              {3,330,0,1}};
    vector<vector<int>> input2{{2,200,0,1},
                            {3,400,0,1},
                            {3,400,1,0},
                            {3,300,0,1}};
    vector<int> request{3,2,3,300,9,2};
    vector<int> request2{3,1,3,200,0,1};
    auto ret = huaweiSolver(input2, request2);
    PrintfVec(ret);
    //Solve25();

    return 0;
}
