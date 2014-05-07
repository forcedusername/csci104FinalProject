#include <deque>
#include <iostream>
using namespace std;

template<class T, class Comparator>
void merge(deque<T> & a, int l, int r, int & m, Comparator & comp)
{
	deque<T> temp; //stores temp merged deque
	int left = l;
	int mid = m + 1; 
	while (left <= m || mid <= r)
	{
		if (left <= m && (mid > r || comp(a[left], a[mid])))
		//left is smaller than the right, or there's none remaining on right
		{			
			temp.push_back(a[left]);
			left++;
		}
		else //right is smaller than left
		{
			temp.push_back(a[mid]);
			mid++;
		}
	}
	int length = r + 1 - l;
	for (int i = 0; i < length; i++)//copy temp array into orig
	{
		a[i + l] = temp[i];
	}
}

template<class T, class Comparator>
void helper(deque<T> & a, int l, int r, Comparator & comp)
{
	if (l < r) // if more than one element
	{
		int m = (l + r) / 2;
		helper(a, l, m, comp);//sort left
		helper(a, m + 1, r, comp);//sort right
		merge(a, l, r, m, comp);
	}
}
template <class T, class Comparator>
void mergeSort (deque<T> & myArray, Comparator & comp)
{
	int size = myArray.size();
	helper(myArray, 0, size- 1, comp);
	//cerr << "Sorting" << endl;
}
