#include "solution.h"
#include "printf_tools.h"
#include <string>
#include <Windows.h>

int main()
{
    Solution solution;
    string str("adhakhlidufjhkkljioolppppeeeee");
    auto vec = solution.PartionLabels(str);    

    PrintfVec(vec);
    system("pause");
    return 0;
}