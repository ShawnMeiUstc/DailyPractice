#pragma once
// 基本思想：对给定的序列，从中间位置分成左右等长的两个部分，然后对两个子序列递归调用mergesort（这个过程由
// 程序栈自动完成，直到所有子序列长度为1自然有序，我们不用关心），之后再对上面两个处理的子序列merge一下就可以了。
// 
// 先由中点划分两个等长子序列，再合并；合并的过程接收两个几乎等长的序列，需要申请一定的新空间（链表的话不需要），存储
// 合并后的序列

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

// 递归的归并
// 从中点分两段，传参数时注意传递头尾
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

// 迭代的归并
// 总体思想：定义一个步长step，从1开始成倍递增，直到超过链表总长的一半；
// 每次长为step的短链表两两合并，最后一次合并的时候两个短链表包含了所有元素，使总体有序
// 步骤：求链表总长；虚拟头结点返回用；按步长分割链表，返回其头和下一个链表的头；
// 两个短合并之后的末元素，用于连接链表；

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

	// 找step个未排序元素，并断链
	// 返回未排序首元素和 末元素的下一个元素
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

	// 已排序首元素、末元素
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