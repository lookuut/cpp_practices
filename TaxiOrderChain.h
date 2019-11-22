//
// Created by lookuut on 21.10.19.
//

#ifndef WORDSEARCH_TAXIORDERCHAIN_H
#define WORDSEARCH_TAXIORDERCHAIN_H

#include <iostream>

#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

typedef struct Order{
    unsigned short time_start;
    unsigned short time_end;
    unsigned int w;
} Order;

/*
3
1 10 10
10 20 10
12 13 20
20
*/
class TaxiOrderChain{
public:

    static int run() {
        int max_time = 20000;
        int N;
        cin >> N;

        string order_str;
        vector<list<Order>*> orders(max_time, NULL);

        for (int i = 0; i < N; i++) {
            Order order;
            cin >> order.time_start;
            cin >> order.time_end;
            cin >> order.w;

            if (orders[order.time_start] == NULL) {
                orders[order.time_start] = new list<Order>();
            }

            orders[order.time_start]->push_back(order);
        }


        list<Order> order_weights;

        unsigned int max_w = 0;
        unsigned short max_w_time_end = 0;

        unsigned int local_max_w = 0;

        for (int time = 0; time < max_time; time++) {
            if (orders[time] != NULL) {

                std::list<Order>::iterator it;

                bool new_timeline_added = false;

                for (it = order_weights.begin(); it != order_weights.end();) {

                    if (it->time_end <= time) {
                        local_max_w = max(local_max_w, it->w);

                        if (local_max_w > it->w) {
                            it = order_weights.erase(it);
                            continue;
                        }

                        for (Order order : *orders[time]) {
                            order.w += it->w;

                            if (max_w < order.w) {
                                max_w = order.w;
                                max_w_time_end = order.time_end;
                                order_weights.push_back(order);
                            } else if (order.time_end < max_w_time_end) {
                                order_weights.push_back(order);
                            }

                            new_timeline_added = true;
                        }
                        ++it;
                    } else {
                        ++it;
                    }
                }

                if (!new_timeline_added) {
                    for (Order order : *orders[time]) {

                        if (max_w < order.w) {
                            max_w = order.w;
                            max_w_time_end = order.time_end;
                        }

                        order_weights.push_back(order);
                    }
                }
                delete orders[time];
            }
        }

        return max_w;
    }
};
#endif //WORDSEARCH_TAXIORDERCHAIN_H
