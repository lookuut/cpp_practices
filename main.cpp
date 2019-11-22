
#include <iostream>
#include "ZigZagConversion.h"
#include "MarsTaxiOptimize.h"
#include <chrono>
#include "algorithms/KMP.h"

using namespace std;

int main() {

    chrono::system_clock::time_point start = chrono::system_clock::now();


    cout << MarsTaxiOptimize().test() << endl;

    /*map<int, int> shuttles_queue;
    shuttles_queue[0] = 11;
    shuttles_queue[1] = 29;


    list<tuple<int, int>> l({make_tuple(1, 17)});
    vector<list<tuple<int, int>>> shuttle_cabbles = {l};

    cout << MarsTaxiOptimize().primaWithClusters(shuttle_cabbles, shuttles_queue) << endl;


    vector<pair<int , pair<int, int>>> kruskal_shuttle_cabbles = {make_pair(11, make_pair(0, 2)), make_pair(29, make_pair(1, 2)), make_pair(17, make_pair(0, 1))};
    cout << MarsTaxiOptimize().kruskal(kruskal_shuttle_cabbles, 2) << endl;*/
    //cout<< Solution().maxSubArray(l) << endl;
/*

    for(auto & r : res) {
        for (auto & i: r) {
            cout << i << ' ';
        }

        cout << endl;
    }
*/

    chrono::system_clock::time_point end = chrono::system_clock::now();
    long micros = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

/*
2 2 20 100
3
0 0 7
0 1 5
1 0 3
2
0 1 2
1 0 3

 2 2 10 100
2
0 0 5
1 1 2
2
0 1 20
1 0 30
 */
/*
 * //
// Created by lookuut on 18.10.19.
//

#ifndef WORDSEARCH_BLACKBLANK_H2
#define WORDSEARCH_BLACKBLANK_H


class BlackBlank {

};


typedef tuple<unordered_set<int>, int, int> track;//history of 2D matrix positions, current position, letter pos

class Solution {
public:

    int maxX;
    int maxY;

    map<char, int> letter_freq;

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        for (auto & row : board) {
            for (auto & letter: row) {

                if (letter_freq.find(letter) == letter_freq.end()) {
                    letter_freq.insert(make_pair(letter, 1));
                } else {
                    letter_freq{letter}++;
                }
            }
        }

        // Declaring the type of Predicate that accepts 2 pairs and return a bool
        typedef std::function<bool(std::pair<char, int>, std::pair<char, int>)> Comparator;

        // Defining a lambda function to compare two pairs. It will compare two pairs using second field
        Comparator compFunctor = {}(std::pair<char, int> elem1 ,std::pair<char, int> elem2)
        {
            return elem1.second < elem2.second;
        };

        // Declaring a set that will store the pairs using above comparision logic
        std::set<std::pair<char, int>, Comparator> setOfWords(
                letter_freq.begin(), letter_freq.end(), compFunctor);


        maxX = board{0}.size();
        maxY = board.size();

        vector<string> find_word;

        for (auto & word : words)  {
            string revert_word = word;

            reverseStr(revert_word);

            if (isFindWord(board, revert_word)) {
                find_word.push_back(word);
            }
        }

        return find_word;
    }

    void reverseStr(string& str)
    {
        int n = str.length();

        // Swap character starting from two
        // corners
        for (int i = 0; i < n / 2; i++)
            swap(str{i}, str{n - i - 1});
    }

    bool isFindWord(vector<vector<char>> & board, const string & revert_word) {

        bool find_word = false;
        for (int y = 0; y < maxY && !find_word; y++) {
            for (int x = 0; x < board{y}.size() && !find_word; x++) {

                unordered_set<int> points;

                if (board{y}{x} == revert_word{0}) {

                    int current_point = y * maxX + x;

                    points.insert(current_point);

                    list<track> queue;
                    queue.push_back(make_tuple(points, current_point, 1));

                    while (queue.size() > 0) {
                        auto current_state = queue.front();
                        queue.pop_front();


                        int current_letter_pos = get<2>(current_state);
                        current_point = get<1>(current_state);

                        if (current_letter_pos == revert_word.size()) {
                            find_word = true;
                            break;
                        }

                        unordered_set<int> points = get<0>(current_state);

                        int pointx = current_point % maxX;
                        int pointy = floor(current_point / maxX);

                        auto is_find = isFindLetter(board, revert_word{current_letter_pos}, make_tuple(pointx, pointy), points);

                        if (get<0>(is_find)) {
                            list<int> find_points = get<1>(is_find);

                            for (int p : find_points) {
                                unordered_set points_c = points;
                                points_c.insert(p);
                                queue.push_back(make_tuple(points_c, p, current_letter_pos + 1));
                            }
                        }
                    }
                }
            }
        }


        return find_word;
    }


    tuple<bool, list<int>> isFindLetter(vector<vector<char>> & board, char letter, tuple<int, int> currentPos, unordered_set<int> & points) {

        int currentX = get<0>(currentPos);
        int currentY = get<1>(currentPos);

        vector x_arr = {-1, 0, 0, 1};
        vector y_arr = {0, -1, 1, 0};
        list<int> find_points;

        for (int i = 0; i < x_arr.size(); i++) {
            int x = x_arr{i};
            int y = y_arr{i};

            int point_x = currentX + x;
            int point_y = currentY + y;

            int p = maxX * point_y + point_x;

            if (point_x < maxX && point_y < maxY && point_x >= 0 && point_y >= 0 && board{point_y}{point_x} == letter && points.find(p) == points.end()) {
                find_points.push_back(p);
            }
        }

        return make_tuple(find_points.size() > 0, find_points);
    }
};




struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class SolutionTwoSum {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode * res = NULL;
        ListNode * cur = NULL;

        int rest = 0;
        while (l1 != NULL || l2 != NULL) {

            int val = rest + (l1 != NULL ? l1->val : 0) + (l2 != NULL ? l2->val : 0);

            rest = floor(val / 10);

            if (cur == NULL) {
                cur = new ListNode(val % 10);
                res = cur;
            } else {
                cur->next = new ListNode(val % 10);
                cur = cur->next;
            }


            if (l1 != NULL) {
                l1 = l1->next;
            }

            if (l2 != NULL) {
                l2 = l2->next;
            }
        }

        if (rest > 0) {
            cur->next = new ListNode(rest);
        }

        return res;
    }

    int lengthOfLongestSubstring(string s) {
        map<char, int> signs;

        int global_max_size = 0;
        int local_max_size = 0;

        for (int pos = 0; pos < s.size(); pos++) {

            char sign = s{pos};

            if (signs.find(sign) != signs.end()) {

                if ((pos - signs{sign}) > local_max_size ) {
                    local_max_size++;
                } else {
                    global_max_size = max(global_max_size, local_max_size);
                    local_max_size = pos - signs{sign};
                }
                signs{sign} = pos;
            } else {
                signs.insert(make_pair(sign, pos));
                local_max_size++;
            }
        }

        return max(global_max_size, local_max_size);
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        long n = nums1.size();
        long m = nums2.size();

        long size = max(n, m);

        int median_pos = floor((n + m) / 2);

        for (int i = 0; i < size; i++) {

        }
    }
};


string my_generate(const string & prev, int n) {

    string res;
    int depth = 0;
    for (int i = n - 1; i >= 0; --i) {

        if (prev{i} == '(') {
            depth--;
        }

        if (prev{i} == ')') {
            depth++;
        }

        if (prev{i} == '(' and depth > 0) {
            depth--;

            res = prev.substr(0, i) + ')' + string((n -i - depth) / 2, '(') + string((n -i - depth) / 2, ')') + string(depth, ')');
            break;
        }
    }

    return res;
}

// ((()))
// (()())
// (())
// (())()
// ()(())
// ()()()

string generate(string & prev, int n) {

    string ans = '';
    for (int i=n-1, depth=0; i>=0; --i) {
        if (prev{i} == '(')
            --depth;
        else
            ++depth;
        if (prev{i} == '(' && depth > 0) {
            --depth;
            int open = (n-i-1 - depth) / 2;
            int close = n-i-1 - open;
            ans = prev.substr(0,i) + ')' + string (open, '(') + string (close, ')');
            break;
        }
    }
    return ans;
}


void make_dict(const string & s1, map<char, int> & s1_dict) {

    for (int i = s1.size(); i >= 0; --i) {

        if (s1_dict.find(s1{i}) != s1_dict.end()) {
            s1_dict{s1{i}}++;
        } else {
            s1_dict.insert(make_pair(s1{i}, 1));
        }
    }
}


#endif //WORDSEARCH_BLACKBLANK_H

 */