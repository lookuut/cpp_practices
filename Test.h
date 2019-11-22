//
// Created by lookuut on 05.11.19.
//

#ifndef WORDSEARCH_TEST_H
#define WORDSEARCH_TEST_H

#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int nums_size = nums.size();

        //checking if input count less than 3
        if (nums_size<3) return result;

        //sorting nums with bybble algorithm
        bubbleSort(nums, nums_size);

        //search from minus
        int sum_first_part;
        int sum_second_part;
        int sum_opposite;
        int positive_start_idx = 0;
        bool is_zero_item = false;



        //preparing start positions for negative search line
        int cand_idx_left;
        int cand_idx_right;
        int cand_num_value; // second part of sum
        int cand_num_value_prev;
        int cand_idx_right_max;
        int cand_idx_left_max;

        int zero_idx = bsearch(nums,0,nums_size-1,0);
        if (zero_idx != -1) is_zero_item = true;

        //finding triple from zeros
        if(is_zero_item){
            if (count_num_repeats(nums, 0, zero_idx) >= 3){
                addItemToResult(result,0,0,0);
            }
        }

        if (nums[nums_size-1]>0 and nums[0]<0){  // if no positives and no negatives then return empty set

            //initiate minus part
            cand_idx_right = nums_size-1;
            cand_idx_right_max = nums_size-1;
            positive_start_idx = search_start_of_positive(nums); //start of positive numbers starting from 0
            for (int i=0; i<positive_start_idx; i++){
                if (nums[i] != nums[i+1]){
                    cand_idx_left = positive_start_idx;
                    sum_opposite = abs(nums[i]);
                    cand_idx_right = cand_idx_right_max;

                    while (cand_idx_right > positive_start_idx and nums[cand_idx_right]>sum_opposite){
                        cand_idx_right--;
                    }
                    //add triple with zero
                    if (nums[cand_idx_right] == sum_opposite && is_zero_item){
                        addItemToResult(result,nums[cand_idx_right],nums[i],0);
                        cand_idx_right--;
                    }
                    cand_idx_right_max = cand_idx_right;

                    //[-6,-7,-5,-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6]
                    //calculating part of sum
                    cand_num_value_prev = 0;
                    cand_num_value = abs(nums[cand_idx_right] + nums[i]);
                    while (cand_idx_right > cand_idx_left){
                        if (cand_num_value_prev != cand_num_value){
                            while (cand_idx_left < cand_idx_right and nums[cand_idx_left]<cand_num_value){
                            cand_idx_left++;
                            }
                            if (cand_idx_left <cand_idx_right and nums[cand_idx_left] == cand_num_value){
                                addItemToResult(result,nums[cand_idx_left],nums[cand_idx_right],nums[i]);
                            }
                        }
                        cand_idx_right--;
                        cand_num_value_prev = cand_num_value;
                        cand_num_value = abs(nums[cand_idx_right] + nums[i]);
                    }
                }
            }
            //[-1,0,1,2,-1,-4]


            cand_idx_left = 0;
            cand_idx_left_max = 0;

            for (int i=nums_size-1; i>positive_start_idx-1; i--){
                //initiate plus part
                if (nums[i]!=nums[i-1] and nums[i]>0){
                    cand_idx_right = positive_start_idx-1;
                    //[-5,-4,-2,-2,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6]
                    sum_opposite = 0-nums[i];
                    cand_idx_left = cand_idx_left_max;

                    while (cand_idx_left < positive_start_idx and nums[cand_idx_left]<=sum_opposite){
                        cand_idx_left++;
                    }
                    cand_idx_left_max = cand_idx_left;
cand_num_value_prev = 0;
                    cand_num_value = nums[cand_idx_left] + nums[i];

                    while (cand_idx_left < cand_idx_right){
                        if (cand_num_value_prev != cand_num_value){
                            while(cand_idx_right > cand_idx_left and abs(nums[cand_idx_right]) < cand_num_value){
                                cand_idx_right--;
                            }
                            if (cand_idx_left < cand_idx_right and abs(nums[cand_idx_right]) == cand_num_value){
                                addItemToResult(result,nums[cand_idx_right],nums[cand_idx_left],nums[i]);
                            }
                        }
                        cand_idx_left++;
                        cand_num_value_prev = cand_num_value;
                        cand_num_value = nums[cand_idx_left] + nums[i];
                    }
                }
            }
        }


        return result;
    }



    void swap(int *xp, int *yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    void bubbleSort(vector<int>& arr, int n)
    {
        int i, j;
        for (i = 0; i < n-1; i++)
            for (j = 0; j < n-i-1; j++)
                if (arr[j] > arr[j+1])
                    swap(&arr[j], &arr[j+1]);
    }

    void addItemToResult(vector<vector<int>>& result, int n1,int n2, int n3)
    {
        vector<int> result_item;
        result_item.push_back(n1);
        result_item.push_back(n2);
        result_item.push_back(n3);
        result.push_back(result_item);
    }


    int bsearch(vector<int> &arr, int l, int r, int q)
    {
        while (l <= r)
        {
            int mid = l + (r-l)/2;
            if (arr[mid] == q) return mid;

            if (q < arr[mid]) { r = mid - 1; }
            else              { l = mid + 1; }
        }
        return -1; //not found
    }


    // finding start of found number inside repeats
    int search_start(vector<int> &arr, int number, int current_index)
    {
        int i = current_index;
        if (i>=0 && number == arr[i]){
            while(number==arr[i]) i--;
            return i+1;
        }
        return -1; //not found
    }

    int search_start_of_positive(vector<int> &arr)
    {
        int mid = arr.size()/2;
        if (arr[mid] < 0 ){
            while (arr[mid] < 0) mid++;
            return mid;
        }else{
            while (arr[mid] >= 0) mid--;
            return mid+1;
        }
        return -1;
    }


    int count_num_repeats(vector<int> &arr, int num, int found_idx)
    {
        int idx = found_idx;
        while(idx > 0 and arr[idx]==num) {
            idx--;
        }
        if (arr[idx] != num) idx++;
        int count=0;
        while(idx<arr.size() and arr[idx]==num){
            idx++;
            count++;
        }
       return count;

    }


};

#endif //WORDSEARCH_TEST_H
