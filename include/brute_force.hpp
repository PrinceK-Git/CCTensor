#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include "vrec.hpp"
#include "distances.hpp"

class BruteForceSearch {
public:

    static std::vector<int> flat_search(
        const std::vector<float>& query,
        const std::vector<VectorRecord<float>>& database,
        int k)
    {
        
        std::priority_queue<std::pair<float, int>> pq;

        for (const auto& record : database) {
            float dist = Distances::l2_sqr(query, record.vector);

            if ((int)pq.size() < k) {
                pq.push({dist, record.id});
            } else if (dist < pq.top().first) {
                pq.pop();
                pq.push({dist, record.id});
            }
            
        }

        std::vector<int> results;
        results.reserve(k);
        while (!pq.empty()) {
            results.push_back(pq.top().second);
            pq.pop();
        }

        std::reverse(results.begin(), results.end());
        return results;
    }
};