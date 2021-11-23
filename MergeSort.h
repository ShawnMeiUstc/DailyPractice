#pragma once
// ����˼�룺�Ը��������У����м�λ�÷ֳ����ҵȳ����������֣�Ȼ������������еݹ����mergesort�����������
// ����ջ�Զ���ɣ�ֱ�����������г���Ϊ1��Ȼ�������ǲ��ù��ģ���֮���ٶ��������������������mergeһ�¾Ϳ����ˡ�
// 
// �����е㻮�������ȳ������У��ٺϲ����ϲ��Ĺ��̽������������ȳ������У���Ҫ����һ�����¿ռ䣨����Ļ�����Ҫ�����洢
// �ϲ��������

// O(NlgN) O(N)

#include "ListNode.h"
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

// �ݹ�Ĺ鲢
// ���е�����Σ�������ʱע�⴫��ͷβ
class MergeSortLinkedListRec {
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
		return merge2Lists(sorted, sorted1);
	}

	ListNode* findMid(ListNode* head, ListNode* tail) {
		ListNode* slow = head, * fast = head;
		while (fast != tail && fast->next != tail) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
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
		cur->next = l1 ? l1 : l2;
		return dumb->next;
	}
};

// �����Ĺ鲢
// ����˼�룺����һ������step����1��ʼ�ɱ�������ֱ�����������ܳ���һ�룻
// ÿ�γ�Ϊstep�Ķ����������ϲ������һ�κϲ���ʱ���������������������Ԫ�أ�ʹ��������
// ���裺�������ܳ�������ͷ��㷵���ã��������ָ�����������ͷ����һ�������ͷ��
// �����̺ϲ�֮���ĩԪ�أ�������������

class MergeSortLinkedListIter {
public:
	ListNode* sortList(ListNode* head)
	{
		if (!head || !head->next)
		{
			return head;
		}
		ListNode* cur = head;
		int len = 0;
		while (cur)
		{
			++len;
			cur = cur->next;
		}
		ListNode* dumbNode = new ListNode(-1, head);
		for (int step = 1; step < len; step <<= 1)
		{
			ListNode* cur = dumbNode->next, * lastSorted = dumbNode;

			while (cur)
			{
				auto pairBeforeSort1 = split(cur, step);
				auto pairBeforeSort2 = split(pairBeforeSort1.second, step);
				cur = pairBeforeSort2.second;
				auto pairAfterSort = merge2Lists(pairBeforeSort1.first, pairBeforeSort2.first);
				lastSorted->next = pairAfterSort.first;
				lastSorted = pairAfterSort.second;
			}
		}
		return dumbNode->next;
	}

	// ��step��δ����Ԫ�أ�������
	// ����δ������Ԫ�غ� ĩԪ�ص���һ��Ԫ��
	pair<ListNode*, ListNode*> split(ListNode* beg, int step)
	{
		ListNode* resFir = beg, * resSec = nullptr;
		while (--step && beg)
		{
			beg = beg->next;
		}
		if (beg)
		{
			resSec = beg->next;
			beg->next = nullptr;
		}
		return { resFir, resSec };
	}

	// ��������Ԫ�ء�ĩԪ��
	pair<ListNode*, ListNode*> merge2Lists(ListNode* l1, ListNode* l2)
	{
		ListNode* dumbNode = new ListNode(-1), * cur = dumbNode;
		while (l1 && l2)
		{
			if (l1->val < l2->val)
			{
				cur->next = l1;
				l1 = l1->next;
			}
			else
			{
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		cur->next = l1 ? l1 : l2;
		while (cur->next)
		{
			cur = cur->next;
		}
		return { dumbNode->next, cur };
	}
};