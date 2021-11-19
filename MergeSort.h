#pragma once
// ����˼�룺�Ը��������У����м�λ�÷ֳ����ҵȳ����������֣�Ȼ������������еݹ����mergesort�����������
// ����ջ�Զ���ɣ�ֱ�����������г���Ϊ1��Ȼ�������ǲ��ù��ģ���֮���ٶ��������������������mergeһ�¾Ϳ����ˡ�
// 
// �����е㻮�������ȳ������У��ٺϲ����ϲ��Ĺ��̽������������ȳ������У���Ҫ����һ�����¿ռ䣨����Ļ�����Ҫ�����洢
// �ϲ��������

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