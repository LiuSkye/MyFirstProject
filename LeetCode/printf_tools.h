#ifndef PRINTFTOOLS
#define PRINTFTOOLS

#include <iostream>
using namespace std;

template <typename Vec>
void PrintfVec(const Vec& vec)
{
    if (vec.empty()) {
        cout << "[]" << endl;
        return;
    }

    auto iter = vec.begin();
    cout << "[";
    while (iter != --(vec.end())) {
        cout << *iter << ",";
        iter++;
    }
    if (iter == --(vec.end())) {
        cout << *iter << "]" << endl;
    }
}

#endif