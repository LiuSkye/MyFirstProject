/*
 * @Author: Skye_Liu
 * @Date: 2021-05-27 16:21:48
 * @Last Modified by: Skye_Liu
 * @Last Modified time: 2021-05-27 17:24:07
 */
#include "solution.h"

#include <algorithm>
#include <assert.h>
#include <exception>
#include <functional>
#include <map>
#include <numeric>
#include <set>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>

vector<int> Solution::PartionLabels(string S)
{
    vector<int> res;

    vector<char> ss(S.begin(), S.end());

    int length = 0;
    int j = 0;
    for (int i = 0; i < ss.size(); i++) {
        auto iter1 = ss.begin() + i;
        auto iter2 = iter1;
        while (iter2 != ss.end()) {
            if (*iter2 == *iter1) {
                iter1 = iter2;
            }
            iter2++;
        }
        int len = (iter1 - ss.begin()) + 1;
        length = (length < len) ? len : length;
        if (i == length - 1) {
            res.push_back(length - j);
            j = iter1 - ss.begin() + 1;
            length = 0;
        }
    }
    return res;
}

int Solution::NumSteps(string s)
{
    vector<bool> bits;

    for (int i = 0; i < s.size(); i++) {
        string a(s.begin() + i, s.begin() + 1 + i);
        bits.push_back(atoi(a.c_str()));
    }

    int numStep = 0;
    while (bits.size() != 1) {
        if (bits.back()) {
            int cur_pos = bits.size() - 1;

            while (cur_pos >= 0 && bits[cur_pos] == 1) {
                bits[cur_pos] = 0;

                cur_pos--;
                if (cur_pos < 0) {
                    bits.insert(bits.begin(), true);
                }
            }
            if (cur_pos >= 0) {
                bits[cur_pos] = 1;
            }
        } else
            bits.pop_back();

        numStep++;
    }
    return numStep;
}

vector<vector<int>> Solution::multiSearch(string big, vector<string>& smalls)
{
    Trie tree;
    vector<vector<int>> res(smalls.size());
    for (int i = 0; i < smalls.size(); ++i) {
        tree.insert(smalls[i], i);
    }
    int m = big.size();
    for (size_t i = 0; i < m; ++i) {
        tree.search(big.substr(i, m - i), res, i);
        // for (size_t j = 1; j <= m; ++j)
        // {
        //     if (j > m - i)
        //     {
        //         break;
        //     }
        //     int sid = tree.search(big.substr(i, j));
        //     if (sid != -1)
        //     {
        //         res[sid].push_back(i);
        //     }
        // }
    }
    return res;
}

string Solution::longestWord(vector<string>& words)
{
    unordered_set<string> memo(words.begin(), words.end());
    function<bool(const string&)> IsMeet = [&](const string& word) -> bool {
        if (word.empty())
            return true;
        for (int i = 0; i <= word.size(); ++i) {
            if (memo.count(word.substr(0, i)) && IsMeet(word.substr(i)))
                return true;
        }
        return false;
    };
    string res;
    for (auto& w : words) {
        memo.erase(w);
        if (IsMeet(w)) {
            if (w.size() > res.size() || (w.size() == res.size() && res > w)) {
                res = w;
            }
        }
        memo.insert(w);
    }
    return res;
}

int Solution::respace(vector<string>& dictionary, string sentence)
{
    unordered_set<string> dict(dictionary.begin(), dictionary.end());
    int n = sentence.size();
    // dp[i]表示前i个字符的最少未匹配数
    vector<int> dp(n + 1, n);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] + 1;
        for (int j = 0; j <= i; ++j) {
            if (dict.count(sentence.substr(j, i - j))) {
                dp[i] = min(dp[i], dp[j]);
            }
        }
    }
    return dp[n];
}

int Solution::totalHammingDistance(vector<int>& nums)
{
    // 逐位统计
    int res = 0, n = nums.size();
    for (int i = 0; i < 30; ++i) {
        int c = 0;
        for (int val : nums) {
            c += (val >> i) & 1;
        }
        // m个数在此位上为0，n个数在此位上为1，所以此位上汉明距离总和m*n
        res += c * (n - c);
    }
    return res;
}

int Solution::countEval(string s, int result)
{
    vector<int> nums;
    vector<char> labels;
    for (char c : s) {
        if (c == '&' || c == '|' || c == '^')
            labels.push_back(c);
        else if (c == '0')
            nums.push_back(0);
        else if (c == '1')
            nums.push_back(1);
    }
    int m = nums.size();
    int dp[m][m][2];
    for (int i = 0; i < m; ++i) {
        dp[i][i][nums[i]] = 1;
        dp[i][i][nums[i] ^ 1] = 0;
    }
    for (int len = 2; len <= m; ++len) {
        for (int i = 0; i + len - 1 < m; ++i) {
            int j = i + len - 1;
            dp[i][j][0] = dp[i][j][1] = 0;
            for (int k = i; k < j; ++k) {
                if (labels[k] == '&') {
                    dp[i][j][1] += dp[i][k][1] * dp[k + 1][j][1];
                    dp[i][j][0] += dp[i][k][1] * dp[k + 1][j][0];
                    dp[i][j][0] += dp[i][k][0] * dp[k + 1][j][1];
                    dp[i][j][0] += dp[i][k][0] * dp[k + 1][j][0];
                } else if (labels[k] == '|') {
                    dp[i][j][1] += dp[i][k][1] * dp[k + 1][j][1];
                    dp[i][j][1] += dp[i][k][1] * dp[k + 1][j][0];
                    dp[i][j][1] += dp[i][k][0] * dp[k + 1][j][1];
                    dp[i][j][0] += dp[i][k][0] * dp[k + 1][j][0];
                } else {
                    dp[i][j][0] += dp[i][k][1] * dp[k + 1][j][1];
                    dp[i][j][1] += dp[i][k][1] * dp[k + 1][j][0];
                    dp[i][j][1] += dp[i][k][0] * dp[k + 1][j][1];
                    dp[i][j][0] += dp[i][k][0] * dp[k + 1][j][0];
                }
            }
        }
    }
    return dp[0][m - 1][result];
}

int bestSeqAtIndex(vector<int>& height, vector<int>& weight)
{
    int n = height.size();
    vector<pair<int, int>> h_w;
    for (int i = 0; i < n; ++i) {
        h_w.emplace_back(make_pair(height[i], weight[i]));
    }
    sort(h_w.begin(), h_w.end(), [](const pair<int, int>& h1, const pair<int, int>& h2) -> bool { return (h1.first == h2.first) ? h1.second > h2.second : h1.first < h2.first; });
    vector<int> dp;
    for (const auto& hw : h_w) {
        auto iter = lower_bound(dp.begin(), dp.end(), hw.second);
        if (iter == dp.end()) {
            dp.push_back(hw.second);
        } else // 替换最下一个
            *iter = hw.second;
    }
    return dp.size();

    // //判断h_w[j]能否在h_w[i]下面
    // auto isMeet = [&](int i, int j) -> bool
    // {
    //     return (h_w[j].first > h_w[i].first) && (h_w[j].second > h_w[i].second);
    // };
    // vector<int> dp(n, 1);
    // //vector<vector<int>> dp(n, vector<int>(n));
    // dp[0] = 1;
    // int max_level = 1;
    // for (int i = 1; i < n; ++i)
    // {
    //     for (int j = i - 1; j >= dp[i] - 1; --j)
    //     {
    //         if (isMeet(j, i))
    //         {
    //             dp[i] = max(dp[i], dp[j] + 1);
    //         }
    //     }
    //     max_level = max(max_level, dp[i]);
    // }
    // return max_level;
}

int Solution::findMaxLength(vector<int>& nums)
{
    int time = 0;
    unordered_map<int, int> memo;
    memo[0] = -1;
    int len = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == 0) {
            ++time;
        } else if (nums[i] == 1) {
            --time;
        }
        if (memo.count(time)) {
            len = max(len, i - memo[time]);
        } else {
            memo[time] = i;
        }
    }
    return len;
}

int findMaxForm(vector<string>& strs, int m, int n)
{
    auto getzeroOnes = [&](int i) -> vector<int> {
        vector<int> zeroOnes(2);
        for (char c : strs[i]) {
            ++zeroOnes[c - '0'];
        }
        return zeroOnes;
    };

    int length = strs.size();
    vector<vector<vector<int>>> dp(length + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
    for (int i = 1; i <= length; i++) {
        auto zerosOnes = getzeroOnes(i - 1);
        int zeros = zerosOnes[0], ones = zerosOnes[1];
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= n; k++) {
                dp[i][j][k] = dp[i - 1][j][k];
                if (j >= zeros && k >= ones) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - zeros][k - ones] + 1);
                }
            }
        }
    }
    return dp[length][m][n];

    // int max_size = 0;
    // int t0 = 0, t1 = 0;
    // int size = 0;
    // //回溯法---超时
    // function<void(int)> dfs = [&](int pos)
    // {
    //     if (t0 > m || t1 > n)
    //     {
    //         max_size = max(max_size, size - 1);
    //         return;
    //     }
    //     if (pos >= strs.size())
    //     {
    //         max_size = max(max_size, size);
    //         return;
    //     }
    //     int temp1 = t1, temp0 = t0;
    //     t0 += memo[pos];
    //     t1 += strs[pos].size() - memo[pos];
    //     ++size;
    //     dfs(pos + 1);
    //     t0 = temp0;
    //     t1 = temp1;
    //     --size;
    //     dfs(pos + 1);
    // };
    // dfs(0);
    // return max_size;
}

int findTargetSumWays(vector<int>& nums, int S)
{
    unordered_map<string, int> memo;
    function<int(int, int)> backTrace = [&](int sum, int steps) -> int {
        if (steps == nums.size()) {
            if (sum == S) {
                return 1;
            }
            return 0;
        }
        // return backTrace(sum + nums[steps], steps + 1) + backTrace(sum - nums[steps], steps + 1);
        string str = to_string(steps) + "," + to_string(sum);
        if (memo.count(str) == 0) {
            memo.insert(make_pair(str, backTrace(sum + nums[steps], steps + 1) + backTrace(sum - nums[steps], steps + 1)));
        }
        return memo[str];
    };

    return backTrace(0, 0);
}
// split写法
int Split(vector<int>& data, int begin, int end)
{

    if (data.empty() || begin < 0 || end > data.size()) {
        return -1;
    }
    int index = begin + rand() % (end - begin);
    swap(data[index], data[end - 1]); // 交换到最后
    int small = begin - 1;
    for (index = begin; index < end - 1; ++index) {
        if (data[index] < data[end - 1]) {
            ++small;
            if (small != index) {
                swap(data[small], data[index]);
            }
        }
    }
    ++small;
    swap(data[small], data[end - 1]);
    return small;
}
// 中轴写法,非静态函数，在其他源文件中可见
int Partition(vector<int>& data, int begin, int end)
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
    swap(data[large], data[begin]);
    return large;
}

void quickSort(vector<int>& data, int begin, int end)
{
    if (begin == end) {
        return;
    }
    int index = Partition(data, begin, end);
    if (index > begin)
        quickSort(data, begin, index);
    if (index < end)
        quickSort(data, index + 1, end);
}

bool isMatch(string s, string p)
{
    function<bool(int, int)> Match = [&](int s_pos, int p_pos) -> bool {
        if (s_pos >= s.size()) {
            if (p_pos >= p.size())
                return true;
            else if (p[p_pos] == '*')
                return Match(s_pos, p_pos + 1) || Match(s_pos - 1, p_pos + 1);
            else {
                if (p_pos + 1 < p.size() && p[p_pos + 1] == '*')
                    return Match(s_pos, p_pos + 2);
                else
                    return false;
            }
        }
        if (p_pos == p.size() || p_pos < 0) {
            return false;
        }
        char cp = p[p_pos];
        if (cp == '.') {
            return Match(s_pos + 1, p_pos + 1);
        } else if (cp == '*') {
            // 前面匹配，'*'指代0次 或 '*'指代1次
            return Match(s_pos - 1, p_pos + 1) || Match(s_pos, p_pos - 1);
        } else if (cp == s[s_pos]) {
            return Match(s_pos + 1, p_pos + 1);
        } else {
            // 不匹配，用'*'抵消一个
            if (p_pos + 1 < p.size() && p[p_pos + 1] == '*') {
                return Match(s_pos, p_pos + 2);
            }
            // 不匹配，且后面没有'*'
            else
                return false;
        }
        return false;
    };
    return Match(0, 0);
}

bool isNumber(string s)
{
    if (s.empty())
        return false;
    int cur_pos = s.find_first_not_of(' ');
    if (cur_pos == string::npos)
        return false;
    int end = s.find_last_not_of(' ') + 1;
    auto ScanUInteger = [&]() -> bool {
        int temp = cur_pos;
        while (cur_pos < s.size() && s[cur_pos] >= '0' && s[cur_pos] <= '9') {
            ++cur_pos;
        }
        return cur_pos > temp;
    };
    auto ScanInteger = [&]() -> bool {
        if (s[cur_pos] == '+' || s[cur_pos] == '-')
            ++cur_pos;
        return ScanUInteger();
    };
    // 状态机
    bool res = true;
    res &= ScanInteger(); // 扫描前面的整数部分可以有符号
    if (cur_pos < s.size() && s[cur_pos] == '.') {
        ++cur_pos;
        // 小数点前可以没有整数部分，所以用’|‘
        res |= ScanUInteger(); // 扫描小数点后的整数部分，不可以有符号  .123
    }
    if (cur_pos < s.size() && (s[cur_pos] == 'E' || s[cur_pos] == 'e')) {
        throw std::exception();
        ++cur_pos;
        res &= ScanInteger(); // 扫描指数部分，必须为整数 .123 e +123
    }
    return res && cur_pos == end;
}

vector<string> permutation(string s)
{
    int n = s.size();
    vector<bool> flags(n);
    sort(s.begin(), s.end());
    vector<string> res;
    string perm;
    function<void(int)> backTrace = [&](int i) {
        if (i >= n) {
            res.push_back(perm);
            return;
        }
        for (int j = 0; j < n; ++j) {
            if (flags[j] || (j > 0 && !flags[j - 1] && s[j - 1] == s[j])) {
                continue;
            }
            flags[j] = true;
            perm.push_back(s[j]);
            backTrace(i + 1);
            perm.pop_back();
            flags[j] = false;
        }
    };
    backTrace(0);
    return res;
}

/**
 * @description:计算1~n整数中1出现的次数
 * @param {int} n
 * @return {int}
 */
int countDigitOne(int n)
{
    if (n == 0) {
        return 0;
    }
    int res = 0;
    // n = 2  3   0   4
    //     high  cur low
    int high = n / 10, cur = n % 10, low = 0;
    long digit = 1;
    while (high > 0 || cur != 0) {
        if (cur == 0) {
            res += high * digit;
        } else if (cur == 1) {
            res += high * digit + low + 1;
        } else {
            res += (high + 1) * digit;
        }
        low += cur * digit;
        cur = high % 10;
        high /= 10;
        digit *= 10;
    }
    return res;
}

int translateNum(int num)
{
    // 动态规划
    string str = to_string(num);
    int n = str.size();
    assert(n);
    vector<int> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (str[i - 2] == '0')
            dp[i] = dp[i - 1];
        else
            dp[i] = dp[i - 1] + (stoi(str.substr(i - 2, 2)) < 26 ? dp[i - 2] : 0);
    }
    return dp[n];
}

int GetLowerBound(const vector<int>& nums, int target)
{
    if (nums.empty())
        return 0;
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] >= target) {
            right = mid;
        }
    }
    return left;
}

int GetUpperBound(const vector<int>& nums, int target)
{
    if (nums.empty())
        return 0;
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid;
        }
    }
    return left;
}

int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2)
{
    int n = nums1.size();
    if (n != nums2.size()) {
        throw "invalid parameters!";
        return -1;
    }
    std::set<int> memo(nums1.begin(), nums1.end());
    int max_change = 0;
    int pos = 0;

    vector<int> diff(n);
    for (int i = 0; i < n; ++i) {
        diff[i] = abs(nums1[i] - nums2[i]);
        if (diff[i] == 0) {
            continue;
        }
        if (memo.count(nums2[i])) {
            int change = diff[i]; // 可以变成0
            if (change > max_change) {
                max_change = change;
                pos = i;
            }
        } else {
            auto iter = memo.insert(nums2[i]).first;
            int change = 0;
            if (iter != memo.begin()) {
                int front = *(--iter);
                change = nums2[i] - front;
            }
            if (++(++iter) != memo.end()) {
                int back = *iter;
                change = min(change, back - nums2[i]);
            }

            change = diff[i] - change;
            if (change > max_change) {
                max_change = change;
                pos = i;
            }
            memo.erase(nums2[i]);
        }
    }
    diff[pos] = diff[pos] - max_change;
    return std::accumulate(diff.begin(), diff.end(), 0);
}

// 不能放置在头文件中，会引起重定义
const int TestStaticConst::data; // 定义，声明已经赋初值，不可再赋值
double TestStaticConst::dd = 1.0;