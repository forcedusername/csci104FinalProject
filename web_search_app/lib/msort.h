#ifndef MSORT_H
#define MSORT_H
//MergeSort Implementations In this File
#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <class T, class Comparator>
void mergeSort(vector<T>& myArray, int start, int end, Comparator comp) 
{ 
	// base case 
	if(start >= end) return; 
	// recursive calls 
	int mid = (start+end)/2; 
	mergeSort(myArray, start, mid, comp); 
	mergeSort(myArray, mid+1, end, comp); 
	// merge 
/*DEBUG
 	cout <<"Before a merge... myArray:\n";
  	for(int i=0; i<myArray.size(); i++)
 		cout << myArray[i] << " ";
 	cout << endl;
 	cout << "Merging... " << start << mid << mid+1 << end << endl;
*/
	merge(myArray, start, mid, mid+1, end, comp); 
/*DEBUG
  	cout << "After merge... myArray:\n";
 	for(int i=0; i<myArray.size(); i++)
 		cout << myArray[i] << " ";
 	cout << endl;
*/
} 

template <class T, class Comparator>
void merge(vector<T>& myArray, int s1, int e1, int s2, int e2, Comparator comp) 
{ 
	//T temp[e2];
	vector<T> temp;
	int step1 = s1;
	int step2 = s2;

	int pos = s1;
	while ((step1<=e1)&&(step2<=e2))
	{
		//if (myArray[step1] <= myArray[step2])
		if (comp(myArray[step1], myArray[step2]))
		{
			//temp[pos] = myArray[step1];
			temp.push_back(myArray[step1]);
			step1++;
		}
		else
		{
			//temp[pos] = myArray[step2];
			temp.push_back(myArray[step2]);
			step2++;
		}
		//pos++;
	}
	
	while(step1 <= e1)
	{
		temp.push_back(myArray[step1]);
		//temp[pos] = myArray[step1];
		step1++;
		//pos++;
	}
	while(step2 <= e2)
	{
		//temp[pos] = myArray[step2];
		temp.push_back(myArray[step2]);
		step2++;
		//pos++;
	}

	for(pos = s1; pos<=e2; pos++)
	{
		//myArray[pos] = temp[pos];
		myArray[pos] = temp[0];
		temp.erase(temp.begin());
	}
}

template <class T, class Comparator>
void mergeSortStarter(vector<T>& myArray, Comparator comp) 
{ 
	mergeSort(myArray, 0, myArray.size()-1, comp); 
}

#endif