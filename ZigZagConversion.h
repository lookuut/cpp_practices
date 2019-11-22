//
// Created by lookuut on 23.10.19.
//

#include <iostream>
#include <list>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>

#ifndef WORDSEARCH_ZIGZAGCONVERSION_H
#define WORDSEARCH_ZIGZAGCONVERSION_H

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {

    }
};


class Solution {
public:
    //PAHNAPLSIIGYIR
    string convert(string s, int numRows) {
        int n = s.size();


        if (numRows <= 1) {
            return s;
        }

        string res;
        int cellLetterCount = numRows + (numRows - 2);

        for (int j = 0; j < numRows; j++) {
            for (int i = 0; i <= ceil(n / cellLetterCount); i++) {

                int pos = i * cellLetterCount + j;
                if (pos < n) {
                    res += s[pos];
                }

                pos = i * cellLetterCount + cellLetterCount - j;
                if (j >= 1 and j < numRows -1 and pos < n) {
                    res += s[pos];
                }

            }
        }

        return res;
    }

    int myAtoi(string s) {
        int n = s.size();

        if (n == 0) {
            return 0;
        }

        int start_pos = 0;

        while (s[start_pos] == 32) {
            start_pos++;
        }

        int res = 0;
        int sign = s[start_pos] == '-' ? -1 : 1;

        for(int i = (sign < 0 or s[start_pos] == '+' ? start_pos + 1: start_pos); i < n and (s[i] >= 48 and s[i] <= 57); i++) {
            int number = sign * (s[i] - 48);

            if (res > INT32_MAX/10 || (res == INT32_MAX / 10 && number > 7))
                return INT32_MAX;

            if (res < INT32_MIN / 10 || (res == INT32_MIN / 10 && number < -8)) {
                return INT32_MIN;
            }

            res = res * 10L + number;
        }

        return res;
    }

    bool isPalindrome(int number) {
        if (number < 0 or number >= 10 and number % 10 == 0) {
            return false;
        }
        int n = number;
        long inverted = 0;

        while (number != 0) {
            inverted = inverted * 10 + number % 10;
            number /= 10;
        }

        return n == inverted;
    }

    int maxArea(vector<int>& height) {

        int n = height.size();

        int max_area = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int m = min(height[i], height[j]);

                int s = m  *  (j - i);

                if (s > max_area) {
                    max_area = s;
                }
            }
        }

        return max_area;
    }


    string intToRoman(int num) {

        if (num <= 0) {
            return 0;
        }

        int dim = 10;
        string roman = "";
        while (num != 0) {

            int rest = (num % dim);

            num -= rest;

            switch(rest) {
                case 900:
                    roman = "CM" + roman;
                    break;
                case 400:
                    roman = "CD" + roman;
                    break;
                case 90:
                    roman = "XC" + roman;
                    break;
                case 40:
                    roman = "XL" + roman;
                    break;
                case 9:
                    roman = "IX" + roman;
                    break;
                case 4:
                    roman = "IV" + roman;
                    break;
                default:
                    if (roman_dict.find(rest) != roman_dict.end()) {
                        roman = roman_dict[rest] + roman;
                    } else {

                        bool is_more_than_five = rest / (dim / 10) > 5;

                        for (auto &[dim10, roman_sign] : roman_dict) {

                            if (is_more_than_five) {

                                if (rest > dim10 and rest <= dim10 + 3 * dim / 10) {


                                    for (int i = 0; i < (rest - dim10) / (dim / 10); i++) {
                                        roman = roman_dict[dim / 10] + roman;
                                    }

                                    roman = roman_sign + roman;
                                    break;
                                }
                            } else {
                                if (rest > dim10 and rest <= 3 * dim10) {
                                    for (int i = 0; i < rest / dim10; i++) {
                                        roman = roman_sign + roman;
                                    }
                                    break;
                                }
                            }
                        }
                    }

            }

            dim *= 10;
        }

        return roman;
    }

    map<int, char> roman_dict = {{1, 'I'}, {5, 'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}, {500, 'D'}, {1000, 'M'}};

    map<char, int> dim10_2_roman = {{'I', 1}, {'V', 5},{'X', 10},{'L', 50},{'C', 100},{'D', 500}, {'M', 1000}};

    int romanToInt(string s) {
        int n = s.size();

        if (n == 0) {
            return 0;
        }

        int num = 0;

        int maxdim10 = 1;

        for (int i = n - 1; i >= 0; i--) {

            int dim10 = dim10_2_roman[s[i]];

            if (dim10 < maxdim10) {
                num -= dim10_2_roman[s[i]];
            } else {
                maxdim10 = dim10_2_roman[s[i]];
                num += dim10_2_roman[s[i]];
            }
        }

        return num;
    }

    string longestCommonPrefix(vector<string>& strs) {

        int n = strs.size();

        if (n == 0) {
            return "";
        }

        if (n == 1) {
            return strs[0];
        }

        string s = strs[0];

        string common = "";

        int s_size = s.size();

        bool is_find = true;

        for (int j = 0; j < s_size and is_find; j++) {

            for (int i = 1; i < n; i++) {
                if (j >= strs[i].size() or strs[i][j] != s[j]) {
                    is_find = false;
                    break;
                }
            }

            if (is_find) {
                common += s[j];
            }
        }

        return common;
    }

    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();

        int closest_num = 0;

        if (n < 3) {
            return closest_num;
        }

        sort(nums.begin(), nums.end());


        int mean = 0;
        int finish;

        int sum;
        unsigned min_diff = INT32_MAX;

        for(int start = 0; start < n - 2 and min_diff != 0; start++) {

            if (start > 0 and nums[start] == nums[start - 1]) {
                continue;
            }

            mean = start + 1;
            finish = n - 1;
            while (mean < finish) {

                sum = nums[start] + nums[mean] + nums[finish];

                if (abs(sum - target) < min_diff) {
                    min_diff = abs(sum - target);
                    closest_num = sum;

                    if (min_diff == 0) {
                        break;
                    }
                }

                if (sum < target) {
                    mean++;
                } else if(sum > target) {
                    finish--;
                }
            }
        }

        return closest_num;
    }

    void combinations(const string & digits, string & gen, int cur_pos, vector<string> & res) {

        int letter_start = (digits[cur_pos] - 50) * 3 + 97 + (digits[cur_pos] > 55) * 1;
        int letter_count = (digits[cur_pos] == 55 or digits[cur_pos] == 57) ? 4 : 3;

        if (cur_pos + 1 == n) {
            for (int j = 0; j < letter_count; ++j) {
                gen[cur_pos] = char(letter_start + j);
                res.push_back(gen);
            }
        } else {
            for (int j = 0; j < letter_count; ++j) {
                gen[cur_pos] = char(letter_start + j);
                combinations(digits, gen, cur_pos + 1, res);
            }
        }
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {

        int size = 1;

        ListNode * item = head;

        while (item->next != NULL) {
            item = item->next;
            size++;
        }

        item = head;

        ListNode * prev = head;
        for (int i = 0; i <= (size - n); i++) {
            prev = item;
            item = item->next;
        }

        prev->next = item->next;

        delete item;

        return head;
    }

    bool isValid(string s) {
        int n = s.size();

        list<char> queue;

        for (int i = 0; i < n; i++) {
            switch(s[i]) {
                case '(':
                case '[':
                case '{':
                    queue.push_back(s[i]);
                    break;
                case ')':
                    if (queue.back() != '(') {
                        return false;
                    }
                    queue.pop_back();
                    break;
                case ']':
                    if (queue.back() != '[') {
                        return false;
                    }
                    queue.pop_back();
                    break;
                case '}':
                    if (queue.back() != '{') {
                        return false;
                    }
                    queue.pop_back();
                    break;
            }
        }

        return queue.size() == 0;
    }

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();

        if (n < 4) {
            return {};
        }

        vector<vector<int>> res(10000, {0,0,0,0});

        sort(nums.begin(), nums.end());

        int res_size = 0;
        for (int start = 0; start < n - 3; ++start) {

            if (start > 0 and nums[start - 1] == nums[start]) {
                continue;
            }

            if (nums[start] + nums[start + 1] + nums[start + 2] + nums[start + 3] > target) break;
            if (nums[start] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target) continue;

            for (int sstart = start + 1; sstart < n - 2; ++sstart) {

                if (sstart > start + 1 and nums[sstart - 1] == nums[sstart]) {
                    continue;
                }

                if (nums[start] + nums[sstart] + nums[sstart + 1] + nums[start + 2] > target) break;
                if (nums[sstart] + nums[n - 2] + nums[n - 1] < target - nums[start]) continue;

                int left = sstart + 1;
                int right = n - 1;

                while (left < right) {
                    int sum = nums[start] + nums[left] + nums[right] + nums[sstart];

                    if (sum < target) {
                        ++left;
                    } else if (sum > target) {
                        --right;
                    } else {

                        res[res_size][0] = nums[start];
                        res[res_size][1] = nums[sstart];
                        res[res_size][2] = nums[left];
                        res[res_size][3] = nums[right];
                        res_size++;

                        while(left < right and nums[left] == nums[left + 1]) ++left;
                        while(left < right and nums[right] == nums[right - 1]) --right;
                        ++left;
                        --right;
                    }
                }
            }
        }

        res.resize(res_size);

        return res;
    }

    vector<string> letterCombinations(string digits) {
        this->n = digits.size();

        if (n < 1) {
            return {};
        }
        vector<string> res;

        string gen(n, ' ');
        combinations(digits, gen, 0, res);

        return res;
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();

        if (n < 3) {
            return {};
        }

        sort(nums.begin(), nums.end());

        vector<vector<int>> res;

        for (int start = 0; start < n - 2 and nums[start] <= 0; start++) {

            int mean = start + 1;
            int r = n - 1;

            if (start > 0 && nums[start] == nums[start - 1])
                continue;

            while (mean < r) {
                int sum = nums[mean] + nums[r] + nums[start];

                if (sum > 0) {
                    r--;
                } else if(sum < 0) {
                    mean++;
                } else {
                    res.push_back({nums[start], nums[mean], nums[r]});

                    while (mean < r && nums[mean] == nums[mean + 1]) mean++;
                    while (mean < r && nums[r] == nums[r - 1]) r--;
                    r--;
                    mean++;
                }
            }
        }

        return res;
    }

    vector<vector<int>> threeSum1(vector<int>& nums) {
        vector<vector<int>> store;

        if(nums.size()< 3) {
            return store;
        }

        sort(nums.begin(),nums.end());

        for(int i = 0; i < nums.size() - 2; i++) {

            if (nums[i] > 0) break;

            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int start = i + 1;
            int end = nums.size() - 1;

            while(start < end) {
                int sum = nums[i] + nums[start] + nums[end];
                if(sum > 0) end--;
                else if(sum < 0) start++;
                else{
                    store.push_back({nums[i],nums[start],nums[end]});
                    while (start < end && nums[start] == nums[start + 1]) ++start;
                    while (start < end && nums[end] == nums[end - 1]) --end;
                    end--,start++;
                }
            }
        }
        return store;
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

        if (l1 == NULL) {
            return l2;
        }

        if (l2 == NULL) {
            return l1;
        }

        ListNode * l = NULL;

        ListNode * head = NULL;

        while (l1 != NULL and l2 != NULL) {

            if (l == NULL) {
                l = new ListNode(0);
                head = l;
            } else {
                l->next = new ListNode(0);
                l = l->next;
            }

            if (l1->val < l2->val) {
                l->val = l1->val;
                l1 = l1->next;
            } else {
                l->val = l2->val;
                l2 = l2->next;
            }
        }

        if (l2 != NULL) {
            if (l == NULL) {
                head = l2;
            } else {
                l->next = l2;
            }

        } else if (l1 != NULL) {
            if (l == NULL) {
                head = l1;
            } else {
                l->next = l1;
            }
        }

        return head;
    }

    vector<string> generateParenthesis(int n) {
        if (n <= 0) {
            return {};
        }
        string gen = string(n, '(') + string(n, ')');

        vector<string> res = {gen};

        int counter = 0;
        int i = 2 * n;

        while (i > 0) {
            --i;

            if (gen[i] == ')') {
                ++counter;
            } else if (gen[i] == '(') {
                --counter;

                if (counter > 0) {
                    --counter;
                    gen[i] = ')';
                    int a = (2 * n - i - counter) / 2;

                    gen = gen.substr(0, i + 1) + string (a, '(') + string (a, ')') + string(counter, ')');

                    res.push_back(gen);

                    counter = 0;
                    i = 2 * n;
                }
            }
        }

        return res;
    }

    ListNode* swapPairs(ListNode* head) {

        ListNode ** pp = &head;
        ListNode *a;
        ListNode *b;

        while ((a = *pp) && (b = a->next)) {
            a->next = b->next;
            b->next = a;
            *pp = b;
            pp = &(a->next);
        }
        return head;
    }

    int removeDuplicates(vector<int>& nums) {

        int n = nums.size();

        int counter = 0;

        for (int i = 0; i < n; i++) {

            nums[counter] = nums[i];

            while (i < n - 1 and nums[i] == nums[i + 1]) {
                i++;
            }

            counter++;
        }

        return counter;
    }

    int removeElement(vector<int>& nums, int val) {

        int n = nums.size();

        int j = 0;
        for (int i = 0; i < n; i++) {

            while (i < n and nums[i] == val) {
                i++;
            }

            if (i < n) {
                nums[j] = nums[i];
                j++;
            }
        }

        return j;
    }

    void KMP(const string & needle, vector<int> & table) {
        int n = needle.size();

        int i = 1;
        int j = 0;

        for (; i <  n - 1;) {
            if (needle[i] == needle[j]) {
                ++j;
                table[i] = j;
                ++i;
            } else if (j == 0) {
                table[i] = 0;
                i++;
            } else {
                j = table[j - 1];
            }
        }
    }


    int strStr(string haystack, string needle) {
        int nsize = needle.size();
        int hsize = haystack.size();

        if (nsize > hsize) {
            return -1;
        }

        if (nsize == 0) return 0;

        vector<int> table(nsize, 0);
        KMP(needle, table);


        int k = 0;
        int l = 0;

        while (k < hsize) {

            if (needle[l] == haystack[k]) {
                ++l;
                ++k;

                if (l == nsize) {
                    return k - l;
                }

            } else if (l > 0){
                l = table[l - 1];
            } else {
                ++k;
            }
        }

        return -1;
    }

    int divide(int dividend, int divisor) {
        if (dividend == INT32_MIN and divisor == -1) {
            return INT32_MAX;
        }

        if (dividend == INT32_MAX) {
            return divide(dividend >> 1, divisor >> 1);
        }

        int answer = 0;

        while (dividend >= divisor) {

            int d = divisor;
            int i = 1;

            while(dividend >= d) {
                d = d << 1;
                i = i << 1;
            }
            answer += i;
            dividend = dividend - d;
        }

        return answer;
    }

    void nextPermutation(vector<int>& nums) {

        int n = nums.size();

        for (int i = n - 1; i > 0; --i) {

            if (nums[i - 1] < nums[i]) {

                int min_diff = nums[i] - nums[i - 1];
                int swap_pos = i;

                for (int j = i + 1; j < n; j++) {

                    if (nums[i - 1] < nums[j] and min_diff > nums[j] - nums[i -1]) {
                        min_diff = nums[j] - nums[i -1];
                        swap_pos = j;
                    }
                }

                swap(nums[i - 1], nums[swap_pos]);

                std::reverse(nums.begin() + i, nums.end());
                return;
            }
        }

        std::reverse(nums.begin(), nums.end());
    }

    int search(vector<int>& nums, int target) {

        int n = nums.size();

        if (n <= 0) {
            return -1;
        }

        return searchBinary(nums, target, 0, nums.size() - 1);
    }

    int searchBinary(vector<int> & nums, int target, int l_pos, int r_pos) {

        if (nums[l_pos] == target) {
            return l_pos;
        } else if (nums[r_pos] == target) {
            return r_pos;
        } else if (r_pos - 1 <= l_pos) {
            return -1;
        }

        int half_pos = (r_pos + l_pos) / 2;

        bool first_half_saw = nums[l_pos] > nums[half_pos];

        if (first_half_saw) {
            if (nums[half_pos] < target and target <= nums[r_pos]) {
                return searchBinary(nums, target, half_pos, r_pos);
            } else {
                return searchBinary(nums, target, l_pos, half_pos);
            }
        } else {
            if (nums[l_pos] < target and target <= nums[half_pos]) {
                return searchBinary(nums, target, l_pos, half_pos);
            } else {
                return searchBinary(nums, target, half_pos, r_pos);
            }
        }
    }


    vector<int> searchRange(vector<int>& nums, int target) {

        vector<int> ret(2, -1);

        int n = nums.size();

        if (n <= 0) {
            return ret;
        }

        int left = 0;
        int right = n - 1;

        while (left < right) {
            int mid = (left + right) / 2;

            if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }

        if (nums[left] != target) {
            return ret;
        }
        ret[0] = left;

        right = n - 1;

        while (left < right) {
            int mid = (left + right) / 2 + 1;

            if (nums[mid] > target) right = mid - 1;
            else left = mid;
        }

        ret[1] = right;

        return ret;
    }

    int searchInsert(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;

        // Invariant: the desired index is between [low, high+1]
        while (low <= high) {
            int mid = low + (high - low)/2;

            if (nums[mid] < target)
                low = mid+1;
            else
                high = mid-1;
        }

        return low;
    }

    bool isValidSudoku(vector<vector<char>>& board) {
        vector<unsigned short> hor(9, 0);
        vector<unsigned short> ver(9, 0);
        vector<unsigned short> cells(9, 0);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                if (board[i][j] - 49 < 0) {
                    continue;
                }

                unsigned short v = (1 << (board[i][j] - 49));

                if ((v & ver[j]) > 0) {
                    return false;
                }

                ver[j] |= v;

                if ((v & hor[i]) > 0) {
                    return false;
                }

                hor[i] |= v;

                int cell_id = (j / 3) + (i / 3) * 3;

                if ((v & cells[cell_id]) > 0) {
                    return false;
                }

                cells[cell_id] |= v;
            }
        }

        return true;
    }

    string countAndSay(int n) {
        if (n == 1) return "1";
        if (n == 2) return "11";

        string result = countAndSay(n - 1);

        string newresult = "";

        int count = 1;

        for(int i = 1; i < result.size(); ++i){
            if(result[i] != result[i - 1]){
                newresult.push_back('0' + count);
                newresult.push_back(result[i - 1]);
                count = 1;
            } else {
                count++;
            }
            if(i == result.size() - 1){
                newresult.push_back('0' + count);
                newresult.push_back(result[i]);
            }
        }

        return newresult;
    }



    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        n = candidates.size();

        if (n == 0 or candidates[0] > target) {
            return {};
        }

        vector<int> ress;
        recCombSum(candidates, 0, target, ress);
        return res;
    }

    void recCombSum(vector<int> & candidates, int pos, int target, vector<int> & res) {

        for (int i = pos; i < n; i++) {
            if (candidates[i] > target) {
                return;
            }

            if (candidates[i] <= target) {
                res.push_back(candidates[i]);

                if (candidates[i] < target) {
                    recCombSum(candidates, i, target - candidates[i], res);
                } else {
                    this->res.push_back(res);
                    res.pop_back();
                    return;
                }

                res.pop_back();
            }
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        n = candidates.size();

        if (n == 0 or candidates[0] > target) {
            return {};
        }

        vector<int> ress;
        recCombSum2(candidates, 0, target, ress);
        return res;
    }

    void recCombSum2(vector<int> & candidates, int pos, int target, vector<int> & res) {

        for (int i = pos; i < n; ) {
            if (candidates[i] > target) {
                return;
            }


            if (candidates[i] <= target) {
                res.push_back(candidates[i]);

                if (candidates[i] < target) {
                    recCombSum2(candidates, i + 1, target - candidates[i], res);
                } else {
                    this->res.push_back(res);
                    res.pop_back();
                    return;
                }

                res.pop_back();

                while (i < n - 1 and candidates[i] == candidates[i + 1]) {
                    i++;
                }
                i++;
            } else {
                i++;
            }
        }
    }

    /**
     * 12
     * 12
       12
       2
     * @param num1
     * @param num2
     * @return
     */

    string multiply(string num1, string num2) {

        int n = num1.size();
        int m = num2.size();

        string res(m +  n, '0');


        for (int i = n - 1; i >= 0; i--) {

            int carry = 0;
            for (int j = m - 1; j >= 0; j--) {
                char n = (num1[i] - '0') * (num2[j] - '0') + (res[i + j + 1] - '0') + carry;
                carry = n / 10;
                res[i + j + 1] = (n % 10) + '0';
            }
            res[i] += carry;
        }

        int first_non_zero = res.find_first_not_of('0');

        if (first_non_zero == string::npos) {
            return "0";
        }

        return res.substr(first_non_zero);
    }

    vector<vector<int>> permute(vector<int>& nums) {

        vector<vector<int>> res;

        this->n = nums.size();

        recursive_permute(res, nums, 0);

        return res;
    }

    void recursive_permute(vector<vector<int>> & result, vector<int> & nums, int pos) {


        if (pos >= n) {
            result.push_back(nums);
            return;
        }

        for (int i = pos; i < n; i++) {

            swap(nums[pos], nums[i]);

            recursive_permute(result, nums, pos + 1);
            swap(nums[pos], nums[i]);
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;


        map<int, int> counter;
        this->n = nums.size();

        vector<int> keys;

        for (int i = 0; i < n; i++) {

            if (counter.find(nums[i]) == counter.end()) {
                counter.insert(make_pair(nums[i], 0));
                keys.push_back(nums[i]);
            }

            counter[nums[i]]++;
        }

        vector<int> current;
        recursive_permute_unique(res, 0, counter, keys, current);

        return res;
    }


    void recursive_permute_unique(vector<vector<int>> & result, int pos, map<int, int> & counter, vector<int> & unique_elements, vector<int> &current) {

        if (pos >= this->n) {
            result.push_back(current);
            return;
        }

        for (int i = 0; i < unique_elements.size(); i++) {

            if (counter[unique_elements[i]] > 0) {
                counter[unique_elements[i]]--;

                current.push_back(unique_elements[i]);

                recursive_permute_unique(result, pos + 1, counter, unique_elements, current);

                current.pop_back();

                counter[unique_elements[i]]++;
            }
        }
    }

    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        for (int i = 0; i < n - 1; i++) {
            for (int j = i; j < n - i - 1; j++) {
                int a = matrix[i][j];
                int b = matrix[j][n - i - 1];
                int c = matrix[n - i - 1][n - j - 1];
                int d = matrix[n - j - 1][i];

                matrix[i][j] = d;
                matrix[j][n - i - 1] = a;
                matrix[n - i - 1][n - j - 1] = b;
                matrix[n - j - 1][i] = c;
            }
        }
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> mams;

        vector<vector<string>> res;

        for (auto & str : strs) {
            map<char, int> dict;
            string t = str;
            sort(t.begin(), t.end());

            mams[t].push_back(str);
        }

        for (auto &[key, v] :  mams) {
            res.push_back(v);
        }

        return res;
    }


    double myPow(double x, int n) {

        if (n == 0) {
            return 1;
        }

        if (n < 0) {
            if (n == INT32_MIN) {
                return myPow(1/x, -(n + 1) ) * 1/x;
            }

            return myPow(1/x, -n);
        }

        if (n == 1) {
            return x;
        }

        if (n % 2 == 1) {
            return x * myPow(x, n - 1);
        }

        return myPow(x * x, n / 2);
    }

    int maxSubArray(vector<int> & nums) {

        int n = nums.size();

        if (n == 0) {
            return 0;
        }

        int prev_max_sum = nums[0];
        int sum = 0;

        for (int i = 0; i < n; i++) {
            sum += nums[i];

            prev_max_sum = max(sum, prev_max_sum);
            sum = max(sum, 0);

        }

        return prev_max_sum;
    }

    vector<int> spiralOrder(vector<vector<int>>& matrix) {


        int m = matrix.size();

        if (m <= 0) {
            return {};
        }

        int n = matrix[0].size();

        vector<int> res = vector(n * m, 0);
        int index = 0;

        for (int i = 0; i < m; i++) {

            int hor_bottom = i;
            int hor_top = m - i - 1;
            int ver_left = i;
            int ver_right = n - i - 1;

            if (hor_bottom > hor_top or ver_right < ver_left) {
                break;
            }

            for (int j = ver_left; j <= ver_right; j++) {
                res[index] = matrix[hor_bottom][j];
                index++;
            }

            for (int j = hor_bottom + 1; j <= hor_top; j++) {
                res[index] = matrix[j][ver_right];
                index++;
            }

            if (hor_bottom != hor_top) {
                for (int j = ver_right - 1; j >= ver_left; j--) {
                    res[index] = matrix[hor_top][j];
                    index++;
                }
            }

            if (ver_left != ver_right) {
                for (int j = hor_top - 1; j >= hor_bottom + 1; j--) {
                    res[index] = matrix[j][ver_left];
                    index++;
                }
            }

        }

        return res;
    }


    bool canJump(vector<int>& nums) {


        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] == 0) {
                int j = i;
                while (i >= 0) {

                    if (nums[i] > j - i) {
                        break;
                    }

                    i--;
                }

                if (i < 0) {
                    return false;
                }
            }
        }

        return true;
    }


    static bool comparator(const vector<int> & l, const vector<int> & r) {
        return l[0] < r[0];
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        if (intervals.empty()) {
            return {};
        }

        sort(intervals.begin(), intervals.end(), Solution::comparator);

        vector<vector<int>> res;
        res.push_back({intervals.begin()->at(0), intervals.begin()->at(1)});

        for (auto & interval : intervals) {
            vector<int> & last = res.back();

            if (last[1] < interval[0]) {
                res.push_back(interval);
            } else if (interval[0] <= last[1]) {
                last[1] = max(interval[1], last[1]);
            }
        }

        return res;
    }


    int lengthOfLastWord(string s) {

        int local_size = 0;

        for (int i = s.size() - 1; i >= 0; --i) {

            if (local_size > 0 && s[i] == ' ') {
                continue;
            } else if (s[i] != ' ') {
                local_size++;
            } else {
                return local_size;
            }
        }

        return local_size;
    }


    vector<vector<int>> res;

    vector<vector<int>> & generateMatrix(int n) {
        res = vector(n, vector(n, 0));

        int index = 1;
        for (int i = 0; i < n; ++i) {


            int bottom_border = i;
            int top_border = n - i - 1;

            if (bottom_border > top_border) {
                break;
            }

            for (int j = bottom_border; j <= top_border; ++j) {
                res[bottom_border][j] = index++;
            }

            for (int j = bottom_border + 1; j <= top_border; ++j) {
                res[j][top_border] = index++;
            }

            for (int j = top_border - 1; j >= bottom_border; --j) {
                res[top_border][j] = index++;
            }

            for (int j = top_border - 1; j >= bottom_border + 1; --j) {
                res[j][bottom_border] = index++;
            }
        }

        return res;
    }

    unsigned long long factorial(int n) {

        unsigned long long res = 1;

        while (n > 0) {
            res *= n;
            n--;
        }

        return res;
    }

    string getPermutation(int n, int k) {

        vector<int> abs = vector<int>(n, 0);

        for (int i = 0; i < n; i++) {
            abs[i] = i + 1;
        }

        return getPermutation(n, k - 1, abs);
    }

    string getPermutation(int n, int k, vector<int> & abs) {

        if (n == 1) {
            return std::to_string(abs[0]);
        }

        int n1 = factorial(n - 1);

        int num = abs[k / n1];

        abs.erase(abs.begin() + k / n1);

        k = k % n1;

        return std::to_string(num) + getPermutation(n - 1, k, abs);
    }

    ListNode* rotateRight(ListNode* head, int k) {

        if (!head or !head->next) return head;

        ListNode * cur = head;

        int size = 1;

        while (cur->next != NULL) {
            cur = cur->next;
            size++;
        }

        cur->next = head;

        k = k % size;

        for (int i = 0; i < size - k; i++) {
            cur = cur->next;
        }

        head = cur->next;
        cur->next = NULL;

        return head;
    }


    int uniquePaths(int m, int n) {

        if (m == 0 or n == 0) {
            return 0;
        }

        if (m == 1 or n == 1) {
            return 1;
        }

        m--;
        n--;

        unsigned long long num = 1;

        for (int i = max(m, n) + 1; i <= m + n; i++) {
            num = num * i;
        }

        return (int)(num / factorial(min(n, m)));
    }

    string addBinary(string a, string b) {

        int a_len = a.size();
        int b_len = b.size();


        string res = "";

        int rest = 0;
        for (int i = 1; i <= max(a_len, b_len); i++) {

            unsigned char n = 0;

            if (i <= a_len) {
                n = a[a_len - i] - char('0');
            }

            if (i <= b_len) {
                n += (b[b_len - i] - char('0'));
            }

            n += rest;

            res = char(char('0') + (n & 1)) + res;
            rest = n / 2;
        }

        if (rest > 0) {
            res = char('1') + res;
        }

        return res;
    }

    string simplifyPath(string path) {
        string res, tmp;

        stringstream ss(path);

        list<string> result;
        while(getline(ss, tmp, '/')) {

            if (tmp == "..") {
                if (!result.empty()) {
                    result.pop_back();
                }
            } else if (!(tmp == "" or tmp == ".")) {
                result.push_back(tmp);
            }
        }

        for (auto & s : result) {
            res += ("/" + s);
        }

        return res.empty() ? "/" : res;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {

        int finish = matrix.size() - 1;

        if (finish < 0) {
            return false;
        }

        int m = matrix[0].size();

        int start = 0;
        int mean = (finish + start) / 2;

        while (!(matrix[start][0] <= target and target <= matrix[start][m - 1]) and finish - start >= 1) {

            if (target <= matrix[mean][m - 1]) {
                finish = mean;
            } else {
                start = mean;
            }

            mean = (finish + start) / 2;
        }

        if (!(matrix[start][0] <= target and target <= matrix[start][m - 1])) {
            return false;
        }
    }


    vector<vector<int>> subsets(vector<int>& nums) {

        int n = nums.size();

        vector<vector<int>> res;

        for (int k = 0; k <= n; k++) {
            vector<int> cur = vector<int>(k, 0);

            recursive(res, cur, nums, 0, 0, k, n);
        }

        return res;
    }

    void recursive(vector<vector<int>> & res, vector<int> & row, vector<int> & nums, int num, int pos, int & k, int & n) {

        if (pos == k) {
            res.push_back(row);
            return;
        }

        for (int i = num; i < n - (k - 1 - pos); i++) {
            row[pos] = nums[i];
            recursive(res, row, nums, i + 1, pos + 1, k, n);
        }
    }



    int word_cur_pos = 0;
    pair<int, int> cur_coor;

    vector<pair<int, int>> coors = {make_pair(-1, 0), make_pair(0, 1), make_pair(1, 0), make_pair(0, -1)};

    int n;
    int m;
    int word_size = 0;

    bool exist(vector<vector<char>>& board, string word) {

        word_size = word.size();

        n = board.size();

        if (word_size == 0 or n == 0) {
            return false;
        }


        m = board[0].size();

        if (m == 0) {
            return false;
        }

        vector<int> visited_cells = vector<int> (m * n, 0);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {

                if (board[i][j] == word[0]) {

                    visited_cells[i * m + j] = 1;

                    word_cur_pos = 1;
                    cur_coor = make_pair(j, i);

                    if (find(board, word, visited_cells)) {
                        return true;
                    }

                    visited_cells[i * m + j] = 0;
                }
            }
        }

        return false;
    }



    bool find(vector<vector<char>>& board, string & word, vector<int> & visited_cells) {

        if (word_cur_pos == word_size) {
            return true;
        }

        for (auto & coor : coors) {

            int x = coor.first + cur_coor.first;
            int y = coor.second + cur_coor.second;

            int pos = y * m + x;

            if (x >= 0 and x < m and y >= 0 and y < n and board[y][x] == word[word_cur_pos] and visited_cells[pos] == 0) {
                visited_cells[pos] = 1;
                ++word_cur_pos;

                cur_coor.first = x;
                cur_coor.second = y;

                bool is_find = find(board, word, visited_cells);

                if (is_find) {
                    return true;
                }

                visited_cells[pos] = 0;

                --word_cur_pos;
                cur_coor.first -= coor.first;
                cur_coor.second -= coor.second;
            }
        }

        return false;
    }
};

#endif //WORDSEARCH_ZIGZAGCONVERSION_H
