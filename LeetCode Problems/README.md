# LeetCode Problem Code Samples
This repository contains my solutions to 2 LeetCode hard problems.


## Folder Structure
The repository has the following folder structure:

The `LeetCode Solutions` folder contains two subfolders, each corresponding to a LeetCode problem. 


## Problem Descriptions
### Problem #4 - Median of Two Sorted Arrays - in Java
The problem statement and description for Problem #4 can be found [https://leetcode.com/problems/median-of-two-sorted-arrays/] or below.

Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively, return **the median** of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).


**Example 1:**
```
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
```

**Example 2:**
```
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
```

**Constraints:**
* `nums1.length == m`
* `nums2.length == n`
* `0 <= m <= 1000`
* `0 <= n <= 1000`
* `1 <= m + n <= 2000`
* `-10^6 <= nums1[i], nums2[i] <= 10^6`

### Problem #42 - Trapping Rain Water - in C++
The problem statement and description for Problem #42 can be found [https://leetcode.com/problems/trapping-rain-water/submissions/917068290/] or below.

Given `n` non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.


**Example 1:**
```
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
```

**Example 2:**
```
Input: height = [4,2,0,3,2,5]
Output: 9
```

**Constraints:**
* `n == height.length`
* `1 <= n <= 2 * 10^4`
* `0 <= height[i] <= 10^5`
