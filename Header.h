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
class Solution {
public:
    ListNode* sortList(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode* cur = head;
        int length = 0;
        while (head)
        {
            ++length;
            head = head->next;
        }
        ListNode* dumbNode = new ListNode(-1);
        for (int step = 1; step < length; step <<= 1)
        {
            while (cur)
            {
                ListNode* firstBeg = cur, * secondBeg = split(firstBeg, step),
                    * tailNode = nullptr;
                cur = split(secondBeg, step);
                ListNode* tmp = merge2List(firstBeg, secondBeg, tailNode);
                tailNode->next = cur;
                dumbNode->next = tmp;
            }
        }
        return dumbNode->next;
    }
    ListNode* split(ListNode* begin, int step)
    {
        while (--step && begin)
        {
            begin = begin->next;
        }
        if (!begin)
        {
            return nullptr;
        }
        ListNode* res = begin->next;
        begin->next = nullptr;
        return res;
    }
    ListNode* merge2List(ListNode* l1, ListNode* l2, ListNode*& tailNode)
    {
        if (!l1)
        {
            return l2;
        }
        if (!l2)
        {
            return l1;
        }
        ListNode* dumbNode = new ListNode(-1), * cur = dumbNode;
        while (l1 && l2)
        {
            if (l1->val < l2->val)
            {
                dumbNode->next = l1;
                l1 = l1->next;
            }
            else
            {
                dumbNode->next = l2;
                l2 = l2->next;
            }
            dumbNode = dumbNode->next;
        }
        dumbNode->next = l1 ? l1 : l2;
        while (dumbNode->next)
        {
            dumbNode = dumbNode->next;
        }
        tailNode = dumbNode;
        return cur->next;

    }
};

