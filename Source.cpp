#include <iostream>
#include <algorithm>
#include "quicksort.h"

using namespace std;

int main()
{
	//cout << __FILE__ << endl;
	//cout << __func__ << endl;
	//cout << __LINE__ << endl;
	//cout << __TIME__ << endl;
	//cout << __DATE__ << endl;
	QuickSort a;
	vector<int> arr{ 7,1,5,1,3,3 };
	a.quickSort(arr);
	for_each(arr.begin(), arr.end(), [](int n) { cout << n << " "; });
}