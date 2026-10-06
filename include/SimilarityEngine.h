#pragma once
#include <vector>
class SimilarityEngine {
public:
    static double cosineSimilarity(const std::vector<double>& a,
                                   const std::vector<double>& b);
};
