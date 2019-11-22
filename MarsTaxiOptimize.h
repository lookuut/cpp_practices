//
// Created by lookuut on 21.10.19.
//

#ifndef WORDSEARCH_MARSTAXIOPTIMIZE_H
#define WORDSEARCH_MARSTAXIOPTIMIZE_H

#include <iostream>

#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <cstdlib>

using namespace std;

pair<int, int> min_cabble_shuttle_for_cluster(const map<int, int> & cluster, const vector<list<tuple<int, int>>> & cabbles, const map<int, int> & shuttle_queue, vector<int> & sorted_shuttles_cost) {

    int min_cabble_shuttle_id = -1;
    int min_cabble_cost = -1;

    for (auto & [shuttle_id, t] : cluster) {

        list<tuple<int, int>> near_shuttles = cabbles[shuttle_id];

        for (auto & [near_shuttle_id, cabble_cost] : near_shuttles) {

            if (
                    cluster.find(near_shuttle_id) == cluster.end()
                    and
                    shuttle_queue.find(near_shuttle_id) != shuttle_queue.end()
                    and
                    cabble_cost <= shuttle_queue.at(near_shuttle_id)
                    and
                    cabble_cost < sorted_shuttles_cost[0]
                    ) {

                if (min_cabble_cost < 0 || min_cabble_cost > cabble_cost) {
                    min_cabble_cost = cabble_cost;
                    min_cabble_shuttle_id = near_shuttle_id;
                }

            }
        }
    }

    if (min_cabble_shuttle_id >= 0) {
        return make_pair(min_cabble_shuttle_id, min_cabble_cost);
    }

    return make_pair(-1, -1);
}

pair<int, int> pop_min_cost_shuttle(map<int, int> &shuttles_costs, vector<int> & sorted_shuttle_costs) {

    int min_cost_shuttle_id = shuttles_costs.begin()->first;
    long min_cost = shuttles_costs.begin()->second;

    for(auto &[shuttle_id, cost] : shuttles_costs) {
        if (cost < min_cost) {
            min_cost = cost;
            min_cost_shuttle_id = shuttle_id;
        }
    }

    shuttles_costs.erase(min_cost_shuttle_id);

    sorted_shuttle_costs.erase(sorted_shuttle_costs.begin());

    return make_pair(min_cost_shuttle_id, min_cost);
}


class MarsTaxiOptimize{

public:

    int primaWithClusters(vector<list<tuple<int, int>>> & shuttle_cabbles, map<int, int> & shuttles_queue, vector<int> & sorted_shuttles_cost) {

        sort(sorted_shuttles_cost.begin(), sorted_shuttles_cost.end());

        map<int, int> current_cluster = map<int, int>();
        int energy_build_cost = 0;

        while (shuttles_queue.size() > 0) {

            auto shuttle = min_cabble_shuttle_for_cluster(current_cluster, shuttle_cabbles, shuttles_queue, sorted_shuttles_cost);

            if (shuttle.first < 0) {
                auto shuttle = pop_min_cost_shuttle(shuttles_queue, sorted_shuttles_cost);
                current_cluster.insert(shuttle);
                energy_build_cost += shuttle.second;
            } else {
                current_cluster.insert(shuttle);
                for (int i = 0; i < sorted_shuttles_cost.size(); i++) {

                    if (sorted_shuttles_cost[i] == shuttles_queue[shuttle.first] ) {
                        sorted_shuttles_cost.erase(sorted_shuttles_cost.begin() + i);
                        break;
                    }
                }

                shuttles_queue.erase(shuttle.first);
                energy_build_cost += shuttle.second;
            }
        }

        return energy_build_cost;
    }

    bool test() {

        int max_test_count = 40;
        int max_shuttle_count = 1000;
        int cabbles_factor = 100;

        int max_shuttle_cost = 1000;
        int max_cabble_cost = 1000;

        for (int test = 0; test < max_test_count; ++test) {
            int shuttle_count = rand() % max_shuttle_count + 1;
            int cabbles_count = rand() % (cabbles_factor * shuttle_count);

            map<int, int> prima_shuttles_queue;
            vector<pair<int, pair<int, int>>> kruskal_graph;

            vector<int> shuttles = vector<int>(shuttle_count, 0);

            for (int i = 0; i < shuttle_count; ++i) {
                shuttles[i] = rand() % max_shuttle_cost;

                kruskal_graph.push_back(make_pair(shuttles[i], make_pair(i, shuttle_count)));
                prima_shuttles_queue[i] = shuttles[i];
            }

            vector<list<tuple<int, int>>> prima_shuttle_cabbles = vector(shuttle_count, list<tuple<int,int>>());

            vector<vector<int>> cabbles = vector<vector<int>>(shuttle_count, vector<int>(shuttle_count, 0));

            for (int i = 0; i < cabbles_count; ++i) {
                int shuttle1 = rand() % shuttle_count;
                int shuttle2 = rand() % shuttle_count;

                if (shuttle1 != shuttle2) {
                    cabbles[shuttle1][shuttle2] = rand() % max_cabble_cost + 1;
                    cabbles[shuttle2][shuttle1] = cabbles[shuttle1][shuttle2];
                }
            }

            for (int i = 0; i < shuttle_count; ++i) {
                for (int j = 0; j < shuttle_count; ++j) {
                    if (cabbles[i][j] > 0) {

                        prima_shuttle_cabbles[i].push_back(make_tuple(j, cabbles[i][j]));
                    }

                    if (cabbles[i][j] > 0 and i <= j) {
                        kruskal_graph.push_back(make_pair(cabbles[i][j], make_pair(i, j)));
                    }
                }
            }

            int prima_res = primaWithClusters(prima_shuttle_cabbles, prima_shuttles_queue, shuttles);
            int kruskal_res = kruskal(kruskal_graph, shuttle_count);

            if (prima_res != kruskal_res) {
                cout << kruskal_res << " " << prima_res << endl;
                return false;
            }

            cout << test << "test passed" << endl;
        }

        return true;
    }

    static int run() {
        int N;
        cin >> N;

        if (N <= 0) {
            return 0;
        }

        vector<int> shuttels = vector<int>(N, 0);

        int cost;

        for (int i = 0; i < N; i++) {
            cin >> cost;
            shuttels[i] = cost;
        }

        int K;
        cin >> K;

        vector<pair<int, pair<int, int>>> shuttle_cabbles;

        int shuttle1;
        int shuttle2;
        int cabble_cost;

        for (int i = 0; i < K; i++) {
            cin >> shuttle1;
            cin >> shuttle2;
            cin >> cabble_cost;

            shuttle_cabbles.push_back(make_pair(cabble_cost, make_pair(shuttle1 - 1, shuttle2 - 1)));
        }

        vector<int> trees = vector<int>(N + 1, 0);

        for (int i = 0; i < N; i++) {
            shuttle_cabbles.push_back(make_pair(shuttels[i], make_pair(i, N)));
            trees[i] = i;
        }

        trees[N] = N;

        sort(shuttle_cabbles.begin(), shuttle_cabbles.end());

        cost = 0;

        for (int i = 0; i < N + K; i++) {

            if (trees[shuttle_cabbles[i].second.first] != trees[shuttle_cabbles[i].second.second]) {
                cost += shuttle_cabbles[i].first;

                int old_tree_id = trees[shuttle_cabbles[i].second.second];
                int new_tree_id = trees[shuttle_cabbles[i].second.first];

                for (int j = 0; j <= N; j++) {
                    if (trees[j] == old_tree_id) {
                        trees[j] = new_tree_id;
                    }
                }
            }
        }


        return cost;
    }


    /**
     * Search min cost tree in graph, Kruskal algorithm
     * @param graph
     * @param N - number of tops in graph
     * @return cost
     */
    int kruskal(vector<pair<int, pair<int , int>>> & graph, int N) {

        vector<int> trees = vector<int>(N + 1, 0);

        for (int i = 0; i <= N; i++) {
            trees[i] = i;
        }

        sort(graph.begin(), graph.end());

        int cost = 0;

        for (int i = 0; i < graph.size(); i++) {

            if (trees[graph[i].second.first] != trees[graph[i].second.second]) {
                cost += graph[i].first;

                int old_tree_id = trees[graph[i].second.second];
                int new_tree_id = trees[graph[i].second.first];

                for (int j = 0; j <= N; j++) {
                    if (trees[j] == old_tree_id) {
                        trees[j] = new_tree_id;
                    }
                }
            }
        }

        return cost;
    }

};
#endif //WORDSEARCH_MARSTAXIOPTIMIZE_H
