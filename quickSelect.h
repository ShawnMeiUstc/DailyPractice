#pragma once
#include "stdafx.h"

class QuickSelect {
public:
	/// <summary>
	/// 快速选取思想：快排的partition每走一次一个数mid就位，比较mid与待选取
	/// 的数，可以剔除掉mid一边的数，平均情况下复杂度O(len2)
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

	/// 两个有序向量的中位数
	/// 
	/// 方法一：
	/// 寻找两个有序向量的第k小数 
	/// 中位数就是k = (m + n + 1) / 2 
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


	/// 找两个有序数组第k小数
	/// 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
	/// 这里的 "/" 表示整除
	/// nums1 中小于等于 pivot1 的元素有 nums1[0 ..k / 2 - 2] 共计 k / 2 - 1 个
	/// nums2 中小于等于 pivot2 的元素有 nums2[0 ..k / 2 - 2] 共计 k / 2 - 1 个
	/// 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过(k / 2 - 1) + (k / 2 - 1) <= k - 2 个
	/// 这样 pivot 本身最大也只能是第 k - 1 小的元素
	/// 如果 pivot = pivot1，那么 nums1[0 ..k / 2 - 1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
	/// 如果 pivot = pivot2，那么 nums2[0 ..k / 2 - 1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
	/// 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数

	int findKthNum(vector<int>& nums1, vector<int>& nums2, int k)
	{
		/// <summary>
		/// index1 index2指示当前有效数组（剔除后的部分）起始位置
		/// </summary>
		int len1 = nums1.size(), len2 = nums2.size();
		int index1 = 0, index2 = 0;

		/// 每次循环过后，k的大小（即查找范围）减小一半，所以时间O(lgk),这里是求中位数
		/// 因此 k = (m + n + 1) / 2，时间为O(lg(m+n))

		while (true) {
			/// <summary>
			/// 某一数组已经空了
			/// </summary>
			if (index1 >= len1) {
				return nums2[index2 + k - 1];
			}
			if (index2 >= len2) {
				return nums1[index1 + k - 1];
			}
			/// <summary>
			/// k == 1 直接返回两数组有效部分首元素较小者即可
			/// </summary>
			if (k == 1) {
				return min(nums1[index1], nums2[index2]);
			}

			/// 正常情况 
			/// pivotIndex 取 index + k / 2 - 1 与 len - 1(最大index)更小者，防止数组中元素不够了越界了
			int pivotIndex1 = min(index1 + k / 2 - 1, len1 - 1);
			int pivotIndex2 = min(index2 + k / 2 - 1, len2 - 1);

			int pivot1 = nums1[pivotIndex1];
			int pivot2 = nums2[pivotIndex2];
			/// <summary>
			/// pivot本身最大只能是k-1小元素，没用，去除掉
			/// </summary>
			if (pivot1 <= pivot2) {
				/// <summary>
				/// k减少了（pivotIndex-起始index） + 1 个元素
				/// </summary>
				k -= pivotIndex1 - index1 + 1;
				/// <summary>
				/// 更新起始index，pivot本身也去掉
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
	/// 方法二:划分数组，将nums1 nums2都划分成两部分，用nums_im1, nums_i, nums_jm1, nums_j 分别表示
	/// nums1[i-1], nums1[i], nums2[j-1], nums2[j]，即两个数组划分后的相邻的四个数，用i j两个指标表
	/// 示两个数组的划分的前半段的数量，即前一部分包含 nums1[0 .. i-1] 和 nums2[0 .. j-1]，后一部分包
	/// 含 nums1[i .. m-1] 和 nums2[j .. n-1]  
	/// 
	/// 正常情况下，由中位数的定义可得 i+j = m-i + n-j 或者 i+j = m-i + n-j - 1(m n是两个数组的size)，∴ j = (m+n+1)/2-i; 
	/// j由i确定，因此只要找到合适的i满足中位数划分的另一个条件nums1[i-1] <= nums1[i] && nums2[j-1] <= nums[j] && nums1[i-1] <= nums2[j]
	/// && nums[j-1] <= nums[i]  
	/// 前两个天然满足，因此只需要满足后两个即可，而后两个条件又可以简化：
	/// i递增，j递减，所以nums1[i-1]递增nums2[j]递减，那么一定存在最大的i满足nums1[i-1] <= nums2[j];
	/// i最大，i+1带入则不满足，即nums1[i] > nums2[j-1](或者nums[j])， 这个条件比nums2[j-1] <= nums1[i]还要强；
	/// ∴ 问题等价于找最大的i满足nums1[i-1] <= nums2[j]
	/// 
	/// 可用二分查找在[0, m+1)中寻找这样合适的i；i取lo hi中点，比较上述条件，如满足，说明i可能不是最大，(记录下可能的中位数候选者)
	/// 在[i+1, hi)之间找，不满足说明i过大，在[lo,i)之间找；
	/// 
	/// 边界情况（）处理：下标-1 = INT_MIN 下标m或n = INT_MAX；这也是比较直观的：当一个数组不出现在前一部分时，对
	/// 应的值为负无穷，就不会对前一部分的最大值产生影响；当一个数组不出现在后一部分时，对应的值为正无穷，就不会对后
	/// 一部分的最小值产生影响

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
		// median1：前一部分的最大值
		// median2：后一部分的最小值
		int median1 = 0, median2 = 0;

		while (lo < hi) {
			// 前一部分包含 nums1[0 .. i-1] 和 nums2[0 .. j-1]
			// 后一部分包含 nums1[i .. m-1] 和 nums2[j .. n-1]
			int i = (lo + hi) / 2; 
			int j = (m + n + 1) / 2 - i;

			// nums_im1, nums_i, nums_jm1, nums_j 分别表示 nums1[i-1], nums1[i], nums2[j-1], nums2[j]
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