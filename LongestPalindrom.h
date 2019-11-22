//
// Created by lookuut on 23.10.19.
//

#include <iostream>
#include <list>
#include <map>
#ifndef WORDSEARCH_LONGESTPALINDROM_H
#define WORDSEARCH_LONGESTPALINDROM_H

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {


        int n = s.size();

        if (n == 0) {
            return "";
        }

        int max_palindrome_size = -1;
        int max_palindrome_left_pos, max_palindrome_right_pos;


        for (int i = 0; i < n and n - i > max_palindrome_size; i++) {

            for (int j = n - 1 ; j > i; j--) {
                int l = i;
                int r = j;

                while (l < r) {
                    if (s[l] != s[r]) {
                        break;
                    }
                    l++;
                    r--;
                }

                if (l >= r and max_palindrome_size < j - i + 1) {
                    max_palindrome_size = j - i + 1;
                    max_palindrome_left_pos = i;
                    max_palindrome_right_pos = j;
                    break;
                }
            }
        }

        return max_palindrome_size > 0 ? s.substr(max_palindrome_left_pos, max_palindrome_right_pos - max_palindrome_left_pos + 1) : s.substr(0, 1);
    }


    string expandFromCenter(string s) {
        int n = s.size();

        if (n == 0) {
            return "";
        }

        if (n == 1) {
            return s.substr(0, 1);
        }


        int max_palindrome_size = 1;
        int max_palindrome_left_pos = 0;
        int max_palindrome_right_pos = 0;

        for (int i = 1; i < n; i++) {

            int r = i;
            int l = i -1;
            int palindrome_size = 0;

            while(r < n and l >= 0 and s[r] == s[l]) {
                palindrome_size += 2;
                r++;
                l--;
            }

            if (max_palindrome_size < palindrome_size) {
                max_palindrome_size = palindrome_size;
                max_palindrome_left_pos = l + 1;
                max_palindrome_right_pos = r - 1;
            }

            r = i + 1;
            l = i - 1;
            palindrome_size = 1;

            while(r < n and l >= 0 and s[r] == s[l]) {
                palindrome_size += 2;
                r++;
                l--;
            }

            if (max_palindrome_size < palindrome_size) {
                max_palindrome_size = palindrome_size;
                max_palindrome_left_pos = l + 1;
                max_palindrome_right_pos = r - 1;
            }
        }

        return s.substr(max_palindrome_left_pos, max_palindrome_right_pos - max_palindrome_left_pos + 1);
    }

};
#endif //WORDSEARCH_LONGESTPALINDROM_H
