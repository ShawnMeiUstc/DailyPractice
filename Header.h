#pragma once
#pragma optimize("", off)

#include <iostream>
#include <cassert>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;


struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};
class HeapSort {
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
		ListNode* res = dumbNode->next;
		delete dumbNode;
		return res;
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
