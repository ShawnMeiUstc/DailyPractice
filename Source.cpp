#include <iostream>
#include <algorithm>
#include "quicksort.h"
#include "mergesort.h"
using namespace std;

int main()
{
	//cout << __FILE__ << endl;
	//cout << __func__ << endl;
	//cout << __LINE__ << endl;
	//cout << __TIME__ << endl;
	//cout << __DATE__ << endl;
	MergeSort M;
	vector<int> arr{ 3,1,2 };
	//M.mergeSort(arr);
	QuickSort Q;
	Q.quickSort(arr);
	for_each(arr.begin(), arr.end(), [](int n) { cout << n << " "; });
}