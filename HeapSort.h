/// �������ṹʵ�ֶѵ�λ�ù�ϵ��
/// �±�Ϊi��Ԫ�����ģ�������ڣ����ڵ�Ϊ����i-1��/ 2;
/// ���ӽڵ�LC: i * 2 + 1 , ���ӽڵ�RC: (i + 1) * 2;

/// ���󶥣��ѽṹ���������������ӿڣ�getMax()  delMax()  insert()
///  getMax() : return arr[0]  O(1)
///  delMax() : ĩԪ�ش���Ѷ�Ԫ�أ�Ȼ��������ˣ����ڵ���ϴ���ӽڵ㻥��λ�ã���ֱ������Ҷ�ڵ����ǰ��������ԣ�O(h) = O(lgn)
///  insert() : ��Ԫ�ز嵽����β��Ȼ���븸�ڵ�Ƚϲ����ˣ�ֱ��������ڵ����ǰ��������ԣ�O(h) = O(lgn)
/// 
///  ���ѵ�����˼·�� (1) ����insert(), Ҳ���Ǵ�ĩβ���벻�����ˣ������������൱�ڴ���ȫ�������ײ���ʼ����ʹ����϶����ԣ�������
///  ÿ�β��붼���˵�Ŀǰ�������ĸ������ܵ�ʱ�临�Ӷ�Ӧ�������нڵ�����֮�� O(��depth) = O(nlgn);
///  ��2��

#pragma once
#include "stdafx.h"

class HeapSort
{
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        heapify(nums);
        while (--k)
        {
            delMax(nums);
        }
        return nums[0];
    }

    void delMax(vector<int>& nums)
    {
        swap(nums[0], nums[nums.size() - 1]);
        nums.pop_back();
        percolateDown(nums, 0);
    }

    void heapify(vector<int>& nums)
    {
        int n = nums.size();
        for (int i = (n >> 1) - 1; i >= 0; --i)
        {
            percolateDown(nums, i);
        }
    }

    void percolateDown(vector<int>& nums, int i)
    {
        int proP = properParent(nums, i);
        while (valid(nums.size(), i) && i != proP)
        {
            swap(nums[i], nums[proP]);
            i = proP;
            proP = properParent(nums, i);
        }
    }

    int properParent(vector<int>& nums, int i)
    {
        int n = nums.size();
        int LC = (i << 1) + 1, RC = (i + 1) << 1;
        int bigger = valid(n, LC) ? (valid(n, RC) ? biggerOne(nums, LC, RC) : LC) : (valid(n, RC) ? RC : -1);
        if (bigger == -1)
        {
            return i;
        }
        return nums[i] > nums[bigger] ? i : bigger;
    }

    int biggerOne(vector<int>& nums, int i, int j)
    {
        return nums[i] > nums[j] ? i : j;
    }

    bool valid(int n, int i)
    {
        return (0 <= i && i < n);
    }
};
