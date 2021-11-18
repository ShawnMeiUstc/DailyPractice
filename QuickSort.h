#pragma once
// 基本思想：选取pivot，通过一趟遍历使pivot就位，即左边的数都不比它大，右边的数都不比它小，
// 对左右两个子序列递归的做此操作，使所有元素就位，排序完成
// 
// 步骤：随机选取pivot并交换至第一个位置，一个变量保存pivot， 相当于空出arr[lo]，
// 两根指针一前一后，后面的指针的数先跟pivot比较，大于等于则后指针前移，扩展大于pivot的序列，小于则把arr[hi]直接付给arr[lo]，
// 然后跳到前指针进行类似的操作，直到两个指针重合，结束一趟扫描，返回重合指针位置mid；
// 递归左右序列，单个数字自然有序

#include <vector>
#include <cassert>
using namespace std;

class QuickSort {
public:
	void quickSort(vector<int>& arr) {
		int n = arr.size();
		if (n <= 1) {
			return;
		}
		sort(arr, 0, n - 1);
	}

	int partition(vector<int>& arr, int lo, int hi) {
		swap(arr[lo], arr[rand() % (hi - lo + 1) + lo]);
		int pivot = arr[lo];
		while (lo < hi) {
			while (lo < hi && pivot <= arr[hi]) { 
				--hi;
			}
			arr[lo] = arr[hi];
			if (lo < hi) {
				++lo;
			}
			while (lo < hi && arr[lo] <= pivot) {
				++lo;
			}
			arr[hi] = arr[lo];
			if (lo < hi) {
				--hi;
			}
		}
		assert(lo == hi); // assert 用于运行时断言，static_assert用于编译时静态断言
		arr[lo] = pivot;
		return lo;
	}

	void sort(vector<int>& arr, int lo, int hi) {
		if (hi <= lo) {
			return;
		}
		int mid = partition(arr, lo, hi);
		sort(arr, lo, mid);
		sort(arr, mid + 1, hi);
	}
};