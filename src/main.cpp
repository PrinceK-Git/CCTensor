#include <iostream>
#include "vrec.hpp"
#include <cstdint>
#include "vector_store_io.hpp"
#include <set>
#include "brute_force.hpp"

int main(int argc, char* argv[]) {

    if (argc < 4) {
        std::cerr << "Usage: CCTensor <base.fvecs> <query.fvecs> <groundtruth.ivecs>" << std::endl;
        return 1;
    }

    std::string base_path = argv[1];
    std::string query_path = argv[2];
    std::string gt_path = argv[3];

    try {
        
        std::cout << "Loading base vectors..." << std::endl;
        auto base = VectorStoreIo::read_vecs<float>(base_path);

        std::cout << "Loading query vectors..." << std::endl;
        auto queries = VectorStoreIo::read_vecs<float>(query_path);

        std::cout << "Loading ground truth..." << std::endl;
        auto ground_truth = VectorStoreIo::read_vecs<int32_t>(gt_path);

        std::cout << "Base: " << base.size() << " vectors, dim=" << base[0].dimension() << std::endl;
        std::cout << "Queries: " << queries.size() << std::endl;
        std::cout << std::endl;

        int k = 100;
        int total_correct = 0;

        for (size_t i = 0; i < queries.size(); ++i) {
            std::vector<int> our_results = BruteForceSearch::flat_search(
                queries[i].vector, base, k);

            std::set<int> true_set(
                ground_truth[i].vector.begin(),
                ground_truth[i].vector.begin() + k);

            int hits = 0;
            for (int id : our_results) {
                if (true_set.count(id)) {
                    hits++;
                }
            }
            total_correct += hits;

            if ((i + 1) % 10 == 0) {
                std::cout << "Processed " << (i + 1) << "/" << queries.size()
                          << " queries..." << std::endl;
            }
        }

        float recall = (float)total_correct / (queries.size() * k);
        std::cout << "\n=== RESULTS ===" << std::endl;
        std::cout << "Recall@" << k << ": " << (recall * 100.0f) << "%" << std::endl;

    }

    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

