#include <iostream>
#include <vector>

using namespace std;
/* insert ele in the iterator position*/
int main()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto begin = v.begin();
	while (begin != v.end())
	{
		++begin;
		begin = v.insert(begin, 42);
		++begin;
	}

	for (auto i : v)
		cout << i << " ";

	return 0;
}
/*
1 42 2 42 3 42 4 42 5 42 6 42 7 42 8 42 9 42
*/