#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <any>
struct Metadata {
    std::unordered_map<std::string, std::any> payload; 
};
template <typename T>
struct VectorRecord {
    int id;
    std::vector<T> vector;
    Metadata metadata;
    size_t dimension() const {
        return vector.size();
    }
};