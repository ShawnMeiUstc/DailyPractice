#include "quicksort.h"
#include "mergesort.h"

int main()
{
	//cout << __FILE__ << endl;
	//cout << __func__ << endl;
	//cout << __LINE__ << endl;
	//cout << __TIME__ << endl;
	//cout << __DATE__ << endl;
	//MergeSort M;
	//vector<int> arr{ 3,1,2 };
	////M.mergeSort(arr);
	//QuickSort Q;
	//Q.quickSort(arr);
	//for_each(arr.begin(), arr.end(), [](int n) { cout << n << " "; });

	vector<vector<int>> a{ {3,2}, {2,4} };
	sort(a.begin(), a.end());
	cout << a[0][0];
}