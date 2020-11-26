#include "solution.h"
#include "printf_tools.h"
#include <string>
#include <Windows.h>
#include <map>
#include <functional>
#include "test.h"

int numTilePossibilities(string tiles) {
	map<char, int> map_tiles;
	for (char& tile : tiles)
	{
		map_tiles[tile]++;
	}
	//vector<vector<char>> level;
	auto iter = map_tiles.begin();
	vector<char> level_1;
	while (iter != map_tiles.end())
	{
		level_1.push_back(iter->first);
		iter++;
	}
	auto visitable = map_tiles;

	function<int(int)> FindNum = [&](int level)->int {
		if (level == tiles.size())
		{
			return 0;
		}

		int num = 0;
		for (int i = 0; i < level_1.size(); i++)
		{
			auto temp = visitable;
			if (map_tiles[level_1[i]] != 0)
			{
				num++;
				visitable[level_1[i]]--;
				num += FindNum(level + 1);

			}
			visitable = temp;
		}
		return num;
	};

	return FindNum(0);
}

int main()
{
    Solution solution;
    // string str("adhakhlidufjhkkljioolppppeeeee");
    // auto vec = solution.PartionLabels(str);    

    // PrintfVec(vec);

    f(0);
    if (NULL==0)
    {
        cout<<"NULL==0"<<endl;
    }
    f(nullptr);
    nullptr_t n1;
    f(n1);

    XCIs<string,Vec> myVec;
    
    string s("1101");
    cout<<solution.NumSteps(s);

    string tiles("AAB");
    cout << numTilePossibilities(tiles)<<endl;
    system("pause");
    return 0;
}