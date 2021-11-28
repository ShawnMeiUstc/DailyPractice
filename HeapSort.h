/// 以向量结构实现堆的位置关系：
/// 下标为i的元素它的（假如存在）父节点为：（i-1）/ 2;
/// 左子节点LC: i * 2 + 1 , 右子节点RC: (i + 1) * 2;

/// （大顶）堆结构常见的三个操作接口：getMax()  delMax()  insert()
///  getMax() : return arr[0]  O(1)
///  delMax() : 末元素代替堆顶元素；然后进行下滤（父节点与较大的子节点互换位置）；直至到达叶节点或提前满足堆序性；O(h) = O(lgn)
///  insert() : 将元素插到向量尾；然后与父节点比较并上滤；直到到达根节点或提前满足堆序性；O(h) = O(lgn)
/// 
///  建堆的两种思路： (1) 不断insert(), 也就是从末尾插入不断上滤（蛮力），这相当于从完全二叉树底部开始调整使其符合堆序性，最坏情况下
///  每次插入都上滤到目前二叉树的根部，总的时间复杂度应该是所有节点的深度之和 O(∑depth) = O(nlgn);
///  （2）

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
