//
// Created by lookuut on 29.10.19.
//

#ifndef WORDSEARCH_KMP_H
#define WORDSEARCH_KMP_H

#include <iostream>
#include <vector>

using namespace std;

void KMP(const string & needle, vector<int> & table) {
    int n = needle.size();

    int i = 1;
    int j = 0;

    for (; i <  n;) {
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

#endif //WORDSEARCH_KMP_H
