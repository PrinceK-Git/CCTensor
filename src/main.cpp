#include <iostream>
#include "vrec.hpp"
#include <cstdint>
#include "vector_store_io.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: CCTensor <path_to_.fvecs_file>" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];

    try {
        auto records = VectorStoreIo::read_vecs<float>(file_path);

        std::cout << "Loaded " << records.size() << " vectors." << std::endl;

        if (!records.empty()) {
            std::cout << "Dimension: " << records[0].dimension() << std::endl;
            std::cout << "First vector (id=" << records[0].id << "): [";
            for (size_t i = 0; i < std::min<size_t>(5, records[0].dimension()); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << records[0].vector[i];
            }
            if (records[0].dimension() > 5) std::cout << ", ...";
            std::cout << "]" << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

