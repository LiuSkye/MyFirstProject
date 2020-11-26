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


int Solution::NumSteps(string s)
{
	vector<bool> bits;
	// for (auto iter = s.begin(); iter !=s.end(); iter++)
	// {
		
	// }
	
	for (int i = 0; i < s.size(); i++)
	{
		string a(s.begin() + i, s.begin() + 1 + i);
		bits.push_back(atoi(a.c_str()));
	}

	int numStep = 0;
	while (bits.size() != 1)
	{
		if (bits.back())
		{
			int cur_pos = bits.size() - 1;

			while (cur_pos >= 0 && bits[cur_pos] == 1)
			{
				bits[cur_pos] = 0;

				cur_pos--;
				if (cur_pos < 0)
				{
					bits.insert(bits.begin(), true);
				}
			}
			if (cur_pos >= 0)
			{
				bits[cur_pos] = 1;
			}
		}
		else
			bits.pop_back();

		numStep++;
	}
	return numStep;
}

