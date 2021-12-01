/// 以向量结构实现堆的位置关系：
/// 下标为i的元素它的（假如存在）父节点为：（i-1）/ 2;
/// 左子节点LC: i * 2 + 1 , 右子节点RC: (i + 1) * 2;
/// 
///  向量堆化的两种思路： (1) 低效建堆：树：从上至下，从左至右，层次遍历，对每个结点上滤；向量：从前往后遍历上滤即可；最坏情况下
///  每次插入都上滤到目前二叉树的根部，总的时间复杂度应该是所有节点的深度之和 O(∑depth) = O(nlgn)（深度就是结点到根部的距离）;
///  （2）高效建堆（Floyd建堆法）：树：从下至上，从右至左，（对叶子节点下滤没有意义，起点是最后一个有孩子的结点）对每个结点下滤；
///   向量：从后向前遍历，起点是：n / 2 - 1; 最坏情况下，每次下滤至叶子结点，时间复杂度是所有结点的高度之和O(∑height) = O(n)（高度是结点
///   到叶子的距离）
/// 
/// （大顶）堆结构常见的三个操作接口：getMax()  delMax()  insert()
///  getMax() : return arr[0]  O(1)
///  delMax() : 末元素代替堆顶元素；然后进行下滤（父节点与较大的子节点互换位置）；直至到达叶节点或提前满足堆序性；O(h) = O(lgn)
///  insert() : 将元素插到向量尾；然后与父节点比较并上滤；直到到达根节点或提前满足堆序性；O(h) = O(lgn)
///

#pragma once
#include "stdafx.h"

class HeapSort
{
public:
    bool indexValid(vector<int> &nums, int i)
    {
        return (0 <= i && i < nums.size());
    }
    /// <summary>
    /// 定义父子关系 /// 拿 0 1 2三个结点就能记住
    /// </summary>
    int leftChild(vector<int>& nums, int i) {
        int LC = (i << 1) + 1;
        if (indexValid(nums, LC)) {
            return LC;
        }
        return -1;
    }
    int rightChild(vector<int>& nums, int i) {
        int RC = ((i + 1) << 1);
        if (indexValid(nums, RC)) {
            return RC;
        }
        return -1;
    }
    int parent(vector<int>& nums, int i)
    {
        if (i == 0) {
            return -1;
        }
        int P = ((i - 1) >> 1);
        if (indexValid(nums, P)) {
            return P;
        }
        return -1;
    }

    
    int biggerOfTwo(vector<int>& nums, int i, int j)
    {
        return nums[i] > nums[j] ? i : j;
    }
    int biggestOfThree(vector<int>& nums, int i, int j, int k) {
        return biggerOfTwo(nums, biggerOfTwo(nums, i, j), biggerOfTwo(nums, j, k));
    }

    /// <summary>
    /// 对结点i的上滤 下滤
    /// </summary>
    /// 上滤i在向量末尾(叶子结点)，nums[i]可能比它的父节点大，所以与父节点比较，直到
    /// 小于等于父节点或自己到达根部
    /// 
    /// 下滤i在向量头（树的根部），nums[i]可能比它的两个孩子中的某一个小，所以
    /// 要不断跟两个孩子比较，直到nums[i]最大或成为叶子结点
    void percolateUp(vector<int>& nums, int i) { 
        while (parent(nums, i) != -1) {
            int j = parent(nums, i);
            if (nums[i] <= nums[j]) {
                break;
            }
            swap(nums[i], nums[j]);
            i = j;
        }
    }

    void percolateDown(vector<int>& nums, int i)
    {
        while (leftChild(nums, i) != -1 || rightChild(nums, i) != -1) {
            int lc = leftChild(nums, i), rc = rightChild(nums, i);
            int propParent = 0;
            if (lc == -1) {
                propParent = biggerOfTwo(nums, i, rc);
            }
            else if (rc == -1) {
                propParent = biggerOfTwo(nums, i, lc);
            }
            else {
                propParent = biggestOfThree(nums, i, lc, rc);
            }

            if (propParent == i) {
                break;
            }
            else {
                swap(nums[propParent], nums[i]);
                i = propParent;
            }
        }
    }

    /// <summary>
    /// 向量堆化算法
    /// 低效： 树：从上至下，从左至右，层次遍历，对每个结点上滤  向量：从前往后遍历即可（自上而下的上滤）
    /// 高效： 树：从下至上，从右至左，（对叶子节点下滤没有意义，起点是最后一个有孩子的结点）对每个结点下滤；
    ///           向量：从后向前遍历，起点是：n / 2 - 1; （自下而上的下滤）
    /// </summary>

    void ineffectiveHeapify(vector<int>& nums) {
        for (int i = 1; i != nums.size(); ++i) {
            percolateUp(nums, i);
        }
    }

    void FloydHeapfy(vector<int>& nums) {
        for (int i = (nums.size() >> 1) - 1; i >= 0; --i) {
            percolateDown(nums, i);
        }
    }

    /// 三个接口

    int getMax(vector<int>& nums) {
        return nums[0];
    }
    /// <summary>
    /// 删除最大值 末元素代替首元素（置换后弹出），然后下滤到正确位置 O(lgn)
    /// </summary>
    /// <param name="nums"></param>
    int delMax(vector<int>& nums)
    {
        int ret = nums[0];
        swap(nums[0], nums[nums.size() - 1]);
        nums.pop_back();
        percolateDown(nums, 0);
        return ret;
    }
    /// <summary>
    /// 插入元素 放在向量尾然后上滤 O(lgn)
    /// </summary>
    /// <param name="nums"></param>
    /// <param name="elem"></param>
    void insert(vector<int>& nums, int elem)
    {
        nums.push_back(elem);
        percolateUp(nums, nums.size() - 1);
    }
    /// <summary>
    /// 不断取出堆顶元素 也可以原址排序，只需要delMax传入
    /// nums的起始位置即可
    /// </summary>
    /// <param name="nums"></param>
    /// <returns></returns>
    vector<int> heapSort(vector<int>& nums) {
        vector<int> res;
        while (nums.size() > 0) {
            res.push_back(delMax(nums));
        }
        return res;
    }
  
};
