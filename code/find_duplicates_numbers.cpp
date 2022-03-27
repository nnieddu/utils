#include <iostream>
#include <vector>

int main()
{
	std::vector<int> ans;
	int tab[] = {2, 3, 85, 44, 4, 9, 1541, 3, 1, 3, 4, 2, 2};
	int sizeTab = sizeof(tab) / sizeof(int);
	int *ptr1 = NULL;
	int *ptr2 = NULL;
	int i = -1;
	int j = 0;

	while (++i < sizeTab - 1)
	{
		ptr1 = &tab[i];
		while (++j < sizeTab)
		{
			ptr2 = &tab[j];
			if (*ptr1 == *ptr2)
			{
				ans.push_back(*ptr1);
				break;
			}
		}
		j = i + 1;
	}
	std::cout << "There are : " << ans.size() << " duplicates numbers :";
	for (std::vector<int>::iterator it = ans.begin() ; it != ans.end(); ++it)
		std::cout << ' ' << *it;
	return 0;
}