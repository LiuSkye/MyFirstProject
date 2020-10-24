#include "solution.h"
#include <functional>

vector<int> Solution::PartionLabels(string S)
{
    vector<int> res;

	vector<char> ss(S.begin(), S.end());
    
	int length = 0;
	int j = 0;
	for (int i = 0; i < ss.size(); i++)
	{
		auto iter1 = ss.begin() + i;
		auto iter2 = iter1;
		while (iter2 != ss.end())
		{
			if (*iter2 == *iter1)
			{
				iter1 = iter2;
			}
			iter2++;
		}
		int len = (iter1 - ss.begin()) +1;
		length = (length < len) ? len : length;
		if (i == length-1)
		{
			res.push_back(length-j);
			j = iter1 - ss.begin()+1;
			length = 0;
		}

	}
	return res;
}

