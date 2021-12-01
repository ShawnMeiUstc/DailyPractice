#include "quicksort.h"
#include "mergesort.h"
#include "HeapSort.h"
#include "quickSelect.h"

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

	vector<int> arr{ 1,3 }, arr1 = { 2,7 };
	QuickSelect Q;
	cout << Q.findMedianSortedArrays0(arr, arr1);
	return 0;
}