#pragma once
// ����˼�룺ѡȡpivot��ͨ��һ�˱���ʹpivot��λ������ߵ��������������ұߵ�����������С��
// ���������������еݹ�����˲�����ʹ����Ԫ�ؾ�λ���������
// 
// ���裺���ѡȡpivot����������һ��λ�ã�һ����������pivot�� �൱�ڿճ�arr[lo]��
// ����ָ��һǰһ�󣬺����ָ������ȸ�pivot�Ƚϣ����ڵ������ָ��ǰ�ƣ���չ����pivot�����У�С�����arr[hi]ֱ�Ӹ���arr[lo]��
// Ȼ������ǰָ��������ƵĲ�����ֱ������ָ���غϣ�����һ��ɨ�裬�����غ�ָ��λ��mid��
// �ݹ��������У�����������Ȼ����

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
		assert(lo == hi); // assert ��������ʱ���ԣ�static_assert���ڱ���ʱ��̬����
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