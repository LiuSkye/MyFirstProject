/*
 * @Author: skye
 * @Date: 2021-06-23 09:58:42
 * @LastEditTime: 2021-06-24 17:31:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Code\DealFile.cpp
 */
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void DealLine(string& line, double& height, ofstream& ostr)
{
    if (line.empty()) {
        return;
    }

    int times = 0;
    int i = 0;
    for (; i < line.size(); ++i) {
        if (isalpha(line[i])) {
            return;
        }

        if (line[i] == ',') {
            if (times == 1) {
                ++i;
                break;
            }
            ++times;
        }
    }
    string threeNum;
    int start = i;
    for (; i < line.size(); ++i) {
        if (line[i] == ' ') {
            ++start;
            continue;
        }
        if (line[i] == ',') {
            threeNum = line.substr(start, i - start);
            break;
        }
    }
    double h = stod(threeNum);
    if (!ostr.is_open()) {
        ostr.open(string("D:/Code/result/") + to_string(h) + ".txt");
        if (!ostr.is_open()) {
            cout << "error" << endl;
        }
        height = h;
    }
    if (fabs(h - height) < 1e-5) {
        // 还是同一截面
        ostr << line.substr(0, i) << endl;
    } else {
        ostr.close();
        height = h;
        ostr.open(string("D:/Code/result/") + to_string(h) + ".txt");
        if (ostr.is_open()) {
            ostr << line.substr(0, i) << endl;
        } else
            cout << "error" << endl;
    }
}

int main()
{
    ifstream file("D:/Code/P01GZ29_XX10151019A_210623_084730.XYZ");
    string line;
    double height = 0.0;
    ofstream ostr;
    while (getline(file, line)) {
        DealLine(line, height, ostr);
    }
    ostr.close();
    return 0;
}

void AnalyzeLine(string& line, string& dir_name, int level)
{
    size_t pos = line.find_last_of('-');
    if (pos == string::npos) {
        level == 0;
        dir_name = line;
    } else {
        level = (pos + 1) / 2;
        dir_name = line.substr(pos + 1);
    }
}
