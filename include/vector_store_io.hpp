#pragma once
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdint>
#include "vrec.hpp"

class VectorStoreIo {
public:
    template <typename T>
    static std::vector<VectorRecord<T>> read_vecs(const std::string& file_path) {

        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + file_path);
        }

        std::vector<VectorRecord<T>> records;
        int32_t dim = 0;
        int id_counter = 0;

        while (file.read(reinterpret_cast<char*>(&dim), sizeof(dim))) {
            VectorRecord<T> record;
            record.id = id_counter++;
            record.vector.resize(dim);

            file.read(reinterpret_cast<char*>(record.vector.data()),
                       dim * sizeof(T));

            if (file.fail()) {
                throw std::runtime_error(
                    "Unexpected end of file or read error at record " +
                    std::to_string(record.id));
            }

            records.push_back(std::move(record));
        }

        return records;
    }
};