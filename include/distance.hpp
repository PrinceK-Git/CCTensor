#pragma once
#include <vector>
#include <cstddef>
#include <stdexcept>

class Distances {
public:
    
    static float l2_sqr(const std::vector<float>& a, const std::vector<float>& b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }

        float dist = 0.0f;
        for (size_t i = 0; i < a.size(); ++i) {
            float diff = a[i] - b[i];
            dist += diff * diff;     // (a[i] - b[i])^2
        }
        return dist;
    }
};