/// �������ṹʵ�ֶѵ�λ�ù�ϵ��
/// �±�Ϊi��Ԫ�����ģ�������ڣ����ڵ�Ϊ����i-1��/ 2;
/// ���ӽڵ�LC: i * 2 + 1 , ���ӽڵ�RC: (i + 1) * 2;
/// 
///  �����ѻ�������˼·�� (1) ��Ч���ѣ������������£��������ң���α�������ÿ��������ˣ���������ǰ����������˼��ɣ�������
///  ÿ�β��붼���˵�Ŀǰ�������ĸ������ܵ�ʱ�临�Ӷ�Ӧ�������нڵ�����֮�� O(��depth) = O(nlgn)����Ⱦ��ǽ�㵽�����ľ��룩;
///  ��2����Ч���ѣ�Floyd���ѷ����������������ϣ��������󣬣���Ҷ�ӽڵ�����û�����壬��������һ���к��ӵĽ�㣩��ÿ��������ˣ�
///   �������Ӻ���ǰ����������ǣ�n / 2 - 1; �����£�ÿ��������Ҷ�ӽ�㣬ʱ�临�Ӷ������н��ĸ߶�֮��O(��height) = O(n)���߶��ǽ��
///   ��Ҷ�ӵľ��룩
/// 
/// ���󶥣��ѽṹ���������������ӿڣ�getMax()  delMax()  insert()
///  getMax() : return arr[0]  O(1)
///  delMax() : ĩԪ�ش���Ѷ�Ԫ�أ�Ȼ��������ˣ����ڵ���ϴ���ӽڵ㻥��λ�ã���ֱ������Ҷ�ڵ����ǰ��������ԣ�O(h) = O(lgn)
///  insert() : ��Ԫ�ز嵽����β��Ȼ���븸�ڵ�Ƚϲ����ˣ�ֱ��������ڵ����ǰ��������ԣ�O(h) = O(lgn)
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
    /// ���常�ӹ�ϵ /// �� 0 1 2���������ܼ�ס
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
    /// �Խ��i������ ����
    /// </summary>
    /// ����i������ĩβ(Ҷ�ӽ��)��nums[i]���ܱ����ĸ��ڵ�������븸�ڵ�Ƚϣ�ֱ��
    /// С�ڵ��ڸ��ڵ���Լ��������
    /// 
    /// ����i������ͷ�����ĸ�������nums[i]���ܱ��������������е�ĳһ��С������
    /// Ҫ���ϸ��������ӱȽϣ�ֱ��nums[i]�����ΪҶ�ӽ��
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
    /// �����ѻ��㷨
    /// ��Ч�� �����������£��������ң���α�������ÿ���������  ��������ǰ����������ɣ����϶��µ����ˣ�
    /// ��Ч�� �����������ϣ��������󣬣���Ҷ�ӽڵ�����û�����壬��������һ���к��ӵĽ�㣩��ÿ��������ˣ�
    ///           �������Ӻ���ǰ����������ǣ�n / 2 - 1; �����¶��ϵ����ˣ�
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

    /// �����ӿ�

    int getMax(vector<int>& nums) {
        return nums[0];
    }
    /// <summary>
    /// ɾ�����ֵ ĩԪ�ش�����Ԫ�أ��û��󵯳�����Ȼ�����˵���ȷλ�� O(lgn)
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
    /// ����Ԫ�� ��������βȻ������ O(lgn)
    /// </summary>
    /// <param name="nums"></param>
    /// <param name="elem"></param>
    void insert(vector<int>& nums, int elem)
    {
        nums.push_back(elem);
        percolateUp(nums, nums.size() - 1);
    }
    /// <summary>
    /// ����ȡ���Ѷ�Ԫ�� Ҳ����ԭַ����ֻ��ҪdelMax����
    /// nums����ʼλ�ü���
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
