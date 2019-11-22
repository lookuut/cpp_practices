//
// Created by lookuut on 22.10.19.
//

#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

#ifndef WORDSEARCH_MEDIANTWOSORTEDVECTOR_H
#define WORDSEARCH_MEDIANTWOSORTEDVECTOR_H



class MedianTwoSortedVector{

    vector<int> nums1;
    vector<int> nums2;
    int n1;
    int n2;

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        this->nums1 = nums1;
        this->nums2 = nums2;

        this->n1 = nums1.size();
        this->n2 = nums2.size();

        auto res = vector_slice(0, n1 - 1, 0, n2 - 1);
        return 0;
    }


    std::tuple<int, int, int, int> vector_slice(int left_pos1, int right_pos1, int left_pos2, int right_pos2) {
        if (right_pos1 - left_pos1  + right_pos2 - left_pos2 <= 2) {
            return make_tuple(left_pos1, right_pos1, left_pos2, right_pos2);
        }

        int pos1 = floor((right_pos1 - left_pos1) / 2);
        int pos2 = floor((right_pos2 - left_pos2) / 2);

        if ((nums1[pos1] > nums2[pos2] or nums1[pos1] <= nums2[pos2]) and  right_pos1 + right_pos1 - left_pos1 - left_pos2 > n1 + n2) {
            return vector_slice(left_pos1, pos1, left_pos2, pos2);
        } else if (right_pos1 + right_pos1 - left_pos1 - left_pos2 <= n1 + n2) {
            return vector_slice(pos1, right_pos1, pos2, right_pos2);
        }
    }
};

#endif //WORDSEARCH_MEDIANTWOSORTEDVECTOR_H
