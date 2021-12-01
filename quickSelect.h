#pragma once
#include "stdafx.h"

class QuickSelect {
public:
	/// <summary>
	/// ����ѡȡ˼�룺���ŵ�partitionÿ��һ��һ����mid��λ���Ƚ�mid���ѡȡ
	/// �����������޳���midһ�ߵ�����ƽ������¸��Ӷ�O(len2)
	/// </summary>
	/// <param name="nums"></param>
	/// <param name="k"></param>
	/// <returns></returns>
	int findKthLargest(vector<int>& nums, int k) {
		int n = nums.size();
		return findK(nums, k, 0, n - 1);
	}

	int findK(vector<int>& nums, int k, int lo, int hi) {

		int mid = partition(nums, lo, hi);
		if (mid == k - 1) {
			return nums[mid];
		}
		else if (mid > k - 1) {
			return findK(nums, k, lo, mid - 1);
		}
		else {
			return findK(nums, k, mid + 1, hi);
		}
	}

	int partition(vector<int>& nums, int lo, int hi) {
		swap(nums[lo], nums[rand() % (hi - lo + 1) + lo]);
		int pivot = nums[lo];
		while (lo < hi) {
			while (lo < hi && pivot >= nums[hi]) {
				--hi;
			}
			nums[lo] = nums[hi];
			if (lo < hi) {
				++lo;
			}
			while (lo < hi && nums[lo] >= pivot) {
				++lo;
			}
			nums[hi] = nums[lo];
			if (lo < hi) {
				--hi;
			}
		}
		nums[lo] = pivot;
		return lo;
	}

	/// ����������������λ��
	/// 
	/// ����һ��
	/// Ѱ���������������ĵ�kС�� 
	/// ��λ������k = (m + n + 1) / 2 
	double findMedianSortedArrays0(vector<int>& nums1, vector<int>& nums2)
	{
		int m = nums1.size(), n = nums2.size();
		if (m > n)
		{
			return findMedianSortedArrays0(nums2, nums1);
		}
		if (m == 0)
		{
			return n % 2 ? nums2[n >> 1] : (nums2[n >> 1] + nums2[(n >> 1) - 1]) / 2.0;
		}
		int k = (m + n + 1) / 2;
		return (m + n) % 2 ? findKthNum(nums1, nums2, k) : ((double)findKthNum(nums1, nums2, k) + (double)findKthNum(nums1, nums2, k + 1)) / 2.0;
	}


	/// ���������������kС��
	/// ��Ҫ˼·��Ҫ�ҵ��� k (k>1) С��Ԫ�أ���ô��ȡ pivot1 = nums1[k/2-1] �� pivot2 = nums2[k/2-1] ���бȽ�
	/// ����� "/" ��ʾ����
	/// nums1 ��С�ڵ��� pivot1 ��Ԫ���� nums1[0 ..k / 2 - 2] ���� k / 2 - 1 ��
	/// nums2 ��С�ڵ��� pivot2 ��Ԫ���� nums2[0 ..k / 2 - 2] ���� k / 2 - 1 ��
	/// ȡ pivot = min(pivot1, pivot2)������������С�ڵ��� pivot ��Ԫ�ع��Ʋ��ᳬ��(k / 2 - 1) + (k / 2 - 1) <= k - 2 ��
	/// ���� pivot �������Ҳֻ���ǵ� k - 1 С��Ԫ��
	/// ��� pivot = pivot1����ô nums1[0 ..k / 2 - 1] ���������ǵ� k С��Ԫ�ء�����ЩԪ��ȫ�� "ɾ��"��ʣ�µ���Ϊ�µ� nums1 ����
	/// ��� pivot = pivot2����ô nums2[0 ..k / 2 - 1] ���������ǵ� k С��Ԫ�ء�����ЩԪ��ȫ�� "ɾ��"��ʣ�µ���Ϊ�µ� nums2 ����
	/// �������� "ɾ��" ��һЩԪ�أ���ЩԪ�ض��ȵ� k С��Ԫ��ҪС���������Ҫ�޸� k ��ֵ����ȥɾ�������ĸ���

	int findKthNum(vector<int>& nums1, vector<int>& nums2, int k)
	{
		/// <summary>
		/// index1 index2ָʾ��ǰ��Ч���飨�޳���Ĳ��֣���ʼλ��
		/// </summary>
		int len1 = nums1.size(), len2 = nums2.size();
		int index1 = 0, index2 = 0;

		/// ÿ��ѭ������k�Ĵ�С�������ҷ�Χ����Сһ�룬����ʱ��O(lgk),����������λ��
		/// ��� k = (m + n + 1) / 2��ʱ��ΪO(lg(m+n))

		while (true) {
			/// <summary>
			/// ĳһ�����Ѿ�����
			/// </summary>
			if (index1 >= len1) {
				return nums2[index2 + k - 1];
			}
			if (index2 >= len2) {
				return nums1[index1 + k - 1];
			}
			/// <summary>
			/// k == 1 ֱ�ӷ�����������Ч������Ԫ�ؽ�С�߼���
			/// </summary>
			if (k == 1) {
				return min(nums1[index1], nums2[index2]);
			}

			/// ������� 
			/// pivotIndex ȡ index + k / 2 - 1 �� len - 1(���index)��С�ߣ���ֹ������Ԫ�ز�����Խ����
			int pivotIndex1 = min(index1 + k / 2 - 1, len1 - 1);
			int pivotIndex2 = min(index2 + k / 2 - 1, len2 - 1);

			int pivot1 = nums1[pivotIndex1];
			int pivot2 = nums2[pivotIndex2];
			/// <summary>
			/// pivot�������ֻ����k-1СԪ�أ�û�ã�ȥ����
			/// </summary>
			if (pivot1 <= pivot2) {
				/// <summary>
				/// k�����ˣ�pivotIndex-��ʼindex�� + 1 ��Ԫ��
				/// </summary>
				k -= pivotIndex1 - index1 + 1;
				/// <summary>
				/// ������ʼindex��pivot����Ҳȥ��
				/// </summary>
				index1 = pivotIndex1 + 1;
			}
			else {
				k -= pivotIndex2 - index2 + 1;
				index2 = pivotIndex2 + 1;
			}
		}
	}



	/// <summary>
	/// ������:�������飬��nums1 nums2�����ֳ������֣���nums_im1, nums_i, nums_jm1, nums_j �ֱ��ʾ
	/// nums1[i-1], nums1[i], nums2[j-1], nums2[j]�����������黮�ֺ�����ڵ��ĸ�������i j����ָ���
	/// ʾ��������Ļ��ֵ�ǰ��ε���������ǰһ���ְ��� nums1[0 .. i-1] �� nums2[0 .. j-1]����һ���ְ�
	/// �� nums1[i .. m-1] �� nums2[j .. n-1]  
	/// 
	/// ��������£�����λ���Ķ���ɵ� i+j = m-i + n-j ���� i+j = m-i + n-j - 1(m n�����������size)���� j = (m+n+1)/2-i; 
	/// j��iȷ�������ֻҪ�ҵ����ʵ�i������λ�����ֵ���һ������nums1[i-1] <= nums1[i] && nums2[j-1] <= nums[j] && nums1[i-1] <= nums2[j]
	/// && nums[j-1] <= nums[i]  
	/// ǰ������Ȼ���㣬���ֻ��Ҫ������������ɣ��������������ֿ��Լ򻯣�
	/// i������j�ݼ�������nums1[i-1]����nums2[j]�ݼ�����ôһ����������i����nums1[i-1] <= nums2[j];
	/// i���i+1���������㣬��nums1[i] > nums2[j-1](����nums[j])�� ���������nums2[j-1] <= nums1[i]��Ҫǿ��
	/// �� ����ȼ���������i����nums1[i-1] <= nums2[j]
	/// 
	/// ���ö��ֲ�����[0, m+1)��Ѱ���������ʵ�i��iȡlo hi�е㣬�Ƚ����������������㣬˵��i���ܲ������(��¼�¿��ܵ���λ����ѡ��)
	/// ��[i+1, hi)֮���ң�������˵��i������[lo,i)֮���ң�
	/// 
	/// �߽�������������±�-1 = INT_MIN �±�m��n = INT_MAX����Ҳ�ǱȽ�ֱ�۵ģ���һ�����鲻������ǰһ����ʱ����
	/// Ӧ��ֵΪ������Ͳ����ǰһ���ֵ����ֵ����Ӱ�죻��һ�����鲻�����ں�һ����ʱ����Ӧ��ֵΪ������Ͳ���Ժ�
	/// һ���ֵ���Сֵ����Ӱ��

	/// </summary>
	/// 
	double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size();
		int n = nums2.size();
		if (m > n) {
			return findMedianSortedArrays1(nums2, nums1);
		}
		if (m == 0) {
			return n == 0 ? 0 : (nums2[(n - 1) / 2] + nums2[n / 2]) / 2.0;
		}
		
		int lo = 0, hi = m + 1;
		// median1��ǰһ���ֵ����ֵ
		// median2����һ���ֵ���Сֵ
		int median1 = 0, median2 = 0;

		while (lo < hi) {
			// ǰһ���ְ��� nums1[0 .. i-1] �� nums2[0 .. j-1]
			// ��һ���ְ��� nums1[i .. m-1] �� nums2[j .. n-1]
			int i = (lo + hi) / 2; 
			int j = (m + n + 1) / 2 - i;

			// nums_im1, nums_i, nums_jm1, nums_j �ֱ��ʾ nums1[i-1], nums1[i], nums2[j-1], nums2[j]
			int nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);
			int nums_i = (i == m ? INT_MAX : nums1[i]);
			int nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);
			int nums_j = (j == n ? INT_MAX : nums2[j]);

			if (nums_im1 <= nums_j) {
				median1 = max(nums_im1, nums_jm1);
				median2 = min(nums_i, nums_j);
				lo = i + 1;
			}
			else {
				hi = i;
			}
		}

		return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
	}
};