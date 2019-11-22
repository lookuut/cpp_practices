//
// Created by lookuut on 21.10.19.
//

#ifndef WORDSEARCH_CUSTOMERDYNAMICCOST_H
#define WORDSEARCH_CUSTOMERDYNAMICCOST_H

#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;

class CustomerDynamicCost{
private:
    int psg_count, driver_count, dist_limit, basic_cost;

    vector<list<tuple<int, int>>> driver_2_psg_dist;
    vector<list<tuple<int, int>>> psg_2_psg_dist;
    vector<int> psg_driver_cost;

    int min_cost;

public:

    int run() {

        cin >> psg_count;

        cin >> driver_count;
        cin >> dist_limit;
        cin >> basic_cost;

        min_cost = basic_cost;

        psg_driver_cost = vector(psg_count, basic_cost);
        psg_2_psg_dist = vector(psg_count, list<tuple<int, int>>());
        driver_2_psg_dist = vector(driver_count, list<tuple<int, int>>());

        int s, driver_id, passenger_id, distance;
        cin >> s;

        for (int i = 0; i < s; i++) {
            cin >> driver_id;
            cin >> passenger_id;
            cin >> distance;

            driver_2_psg_dist[driver_id].push_back(make_tuple(passenger_id, distance));
        }

        cin >> s;

        int near_passenger_id;

        for (int i = 0; i < s; i++) {
            cin >> passenger_id;
            cin >> near_passenger_id;
            cin >> distance;

            psg_2_psg_dist[passenger_id].push_back(make_tuple(near_passenger_id, distance));
        }


        for (int driver_id = 0; driver_id < driver_count; driver_id++) {
            list<tuple<int, int>> passengers = this->driver_2_psg_dist[driver_id];


            vector<int> psg_2_driver_true_dist = vector(psg_count, 0);

            while (passengers.size() > 0) {
                int passenger_id, distance;

                std::tie(passenger_id, distance) = passengers.back();
                passengers.pop_back();

                if (distance < dist_limit) {

                    int & cost = psg_driver_cost[passenger_id];

                    if (psg_2_driver_true_dist[passenger_id] > 0) {

                        if (psg_2_driver_true_dist[passenger_id] < distance) {
                            continue;
                        }

                        cost += (dist_limit - psg_2_driver_true_dist[passenger_id]);
                    }

                    psg_2_driver_true_dist[passenger_id] = distance;

                    cost -= (dist_limit - distance);

                    min_cost = min(min_cost, cost);

                    if (min_cost <= 1) {
                        return 1;
                    }

                    auto near_passengers = this->psg_2_psg_dist[passenger_id];

                    for (auto & [n_psg, dist] : near_passengers) {
                        if (dist + distance < dist_limit) {
                            passengers.push_back(make_tuple(n_psg, dist + distance));
                        }
                    }
                }
            }
        }

        return min_cost;
    }
};


#endif //WORDSEARCH_CUSTOMERDYNAMICCOST_H
