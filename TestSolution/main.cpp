/*
 * @Author: Skye
 * @Date: 2021-07-25 16:20:17
 * @LastEditTime: 2021-08-26 22:17:42
 * @Description: 笔试
 * Skye:'Never stop!'
 */
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using std::vector;
using std::cout;

class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        if(flag) {
            memo1 = vector<vector<vector<int>>>(m+1, 
                            vector<vector<int>>(n+1, vector<int>(maxMove+1, -1)));
            flag = false;
        }
        if(maxMove < 0) {
            return 0;
        }
        if(startRow < 0 || startRow >= m || startColumn < 0 || startColumn >= n) {
            return 1;
        }
        int res = 0;
        int shortestPath = std::min({startRow+1, m-startRow, startColumn+1, n-startColumn});
        if(maxMove < shortestPath) {
            return 0;
        }
        if(memo1[startRow][startColumn][maxMove] >= 0) {
            return memo1[startRow][startColumn][maxMove];
        }
        res = (res + findPaths(m, n, maxMove-1, startRow-1, startColumn))%(1000000007);
        res = (res + findPaths(m, n, maxMove-1, startRow+1, startColumn))%(1000000007);
        res = (res + findPaths(m, n, maxMove-1, startRow, startColumn-1))%(1000000007);
        res = (res + findPaths(m, n, maxMove-1, startRow, startColumn+1))%(1000000007);
        memo1[startRow][startColumn][maxMove] = res;
        return res;
    }

    vector<vector<vector<int>>> memo1;
    bool flag = true;
    // int memo[m][n][maxMove];
};

class A {
public:
class B{};
};

int main()
{
    

    int m = 36, n = 5 ,maxMove = 50, startRow = 15, startColumn = 3;
    Solution sol;
    cout << sol.findPaths(m ,n, maxMove, startRow, startColumn);
    return 0;
}
