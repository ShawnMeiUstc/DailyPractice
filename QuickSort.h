// 基本思想：选取pivot，通过一趟遍历使pivot就位，即左边的数都不比它大，右边的数都不比它小，
// 对左右两个子序列递归的做此操作，使所有元素就位，排序完成
// 
// 步骤：随机选取pivot并交换至第一个位置，一个变量保存pivot， 相当于空出arr[lo]，
// 两根指针一前一后，后面的指针的数先跟pivot比较，大于等于则后指针前移，扩展大于等于pivot的序列，小于则把arr[hi]直接付给arr[lo]，
// 然后跳到前指针进行类似的操作，直到两个指针重合，结束一趟扫描，返回重合指针位置mid；
// 递归左右序列，单个数字自然有序
// 
// 改进：当hi-lo比较小的时候，可以用插入排序代替快排

// 时间复杂度平均O(NlgN)，最坏O(N²), 空间O(lgN)(递归栈)  不稳定


// 另一种partition方法，适用于链表，先交换两个值，arr[lo]作为轴点，然后用i，j两个指标指示lo+1位置，
// 之后比较arr[j]与轴点的大小，移动指针，让i左边的数小于等于轴点，i j
// 之间的数大于轴点，直到j移出边界；  具体的说，若arr[lo] < arr[j], i不动，++j；若 arr[j] <= arr[lo], 则swap(arr[i], arr[j])，++i, ++j;
// 最后轴点归位到i-1位置

#pragma once
#include "stdafx.h"

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

	int partition1(vector<int>& arr, int lo, int hi) {
		swap(arr[lo], arr[rand() % (hi - lo + 1) + lo]);
		int i = lo + 1;
		for (int j = lo + 1; j <= hi; ++j) {
			if (arr[j] <= arr[lo]) {
				swap(arr[i++], arr[j]);
			}
		}
		swap(arr[lo], arr[i-1]);
		return i - 1;
	}

	void sort(vector<int>& arr, int lo, int hi) {
		if (hi <= lo) {
			return;
		}
		int mid = partition1(arr, lo, hi);
		sort(arr, lo, mid);
		sort(arr, mid + 1, hi);
	}
};


class QuickSortList {
public:
	ListNode* quickSort(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}
		ListNode* tail = head;
		while (tail->next) {
			tail = tail->next;
		}
		quickSortAug(head, tail);
		return head;
	}

	void quickSortAug(ListNode* head, ListNode* tail) {
		if (head == nullptr || tail == nullptr || head == tail) {
			return;
		}
		ListNode* mid = partition(head, tail);
		quickSortAug(head, mid);
		quickSortAug(mid->next, tail);
	}

	ListNode* partition(ListNode* head, ListNode* tail) {
		ListNode* iNode = head->next, * jNode = head->next, *iPre = head;
		while (jNode != tail) {
			if (jNode->val < head->val) {
				swap(jNode->val, iNode->val); // 不能交换数据的时候，保存iPre，iNext，jPre，jNext，断链组合
				iPre = iNode;
				iNode = iNode->next;
			}
			jNode = jNode->next;
		}
		// 这里jNode == tail，还没有移到出界位置，特殊处理一下
		if (jNode->val < head->val) {
			swap(jNode->val, iNode->val);
			iPre = iNode;
			iNode = iNode->next;
		}

		swap(head->val, iPre->val);
		return iPre;
	}
};