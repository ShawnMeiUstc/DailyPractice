#pragma once
// 基本思想：对给定的序列，从中间位置分成左右等长的两个部分，然后对两个子序列递归调用mergesort（这个过程由
// 程序栈自动完成，直到所有子序列长度为1自然有序，我们不用关心），之后再对上面两个处理的子序列merge一下就可以了。
// 
// 先由中点划分两个等长子序列，再合并；合并的过程接收两个几乎等长的序列，需要申请一定的新空间（链表的话不需要），存储
// 合并后的序列

// O(NlgN) O(N)


#include <vector>

using namespace std;

class MergeSort {
public:
	void mergeSort(vector<int>& arr) {
		int n = arr.size();
		if (n <= 1) {
			return;
		}
		mergeSortAug(arr, 0, n - 1);
	}

	void mergeSortAug(vector<int>& arr, int lo, int hi) {
		if (hi <= lo) {
			return;
		}
		int mid = lo + ((hi - lo) >> 1);
		mergeSortAug(arr, lo, mid);
		mergeSortAug(arr, mid + 1, hi);
		merge(arr, lo, mid, hi);
	}

	void merge(vector<int>& arr, int lo, int mid, int hi) {
		vector<int> recordArr(hi - lo + 1, 0);
		int i = lo, j = mid + 1, k = 0;
		while (i <= mid && j <= hi) {
			if (arr[i] <= arr[j]) {
				recordArr[k++] = arr[i++];
			}
			else {
				recordArr[k++] = arr[j++];
			}
		}
		while (i <= mid) {
			recordArr[k++] = arr[i++];
		}
		while (j <= hi) {
			recordArr[k++] = arr[j++];
		}

		copy(recordArr.begin(), recordArr.end(), arr.begin() + lo);
	}
};



struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class MergeSortLinkedList {
public:
	ListNode* sortList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}
		ListNode* tail = head;
		while (tail->next) {
			tail = tail->next;
		}
		return sortList(head, tail);
	}

	ListNode* sortList(ListNode* head, ListNode* tail) {
		if (head == tail) {
			return head;
		}
		ListNode* mid = findMid(head, tail), * head1 = mid->next;
		mid->next = nullptr;
		ListNode* sorted = sortList(head, mid);
		ListNode* sorted1 = sortList(head1, tail);
		return merge(sorted, sorted1);
	}

	ListNode* findMid(ListNode* head, ListNode* tail) {
		ListNode* slow = head, * fast = head;
		while (fast != tail && fast->next != tail) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	ListNode* merge(ListNode* l1, ListNode* l2) {
		ListNode* dumb = new ListNode(-1), * cur = dumb;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				cur->next = l1;
				l1 = l1->next;
			}
			else {
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		if (l1) {
			cur->next = l1;
		}
		if (l2) {
			cur->next = l2;
		}
		return dumb->next;
	}
};