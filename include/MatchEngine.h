#pragma once
#include "Item.h"
#include "SimilarityEngine.h"
#include "TextPreprocessor.h"
#include "TfidfVectorizer.h"
#include <string>
#include <vector>
struct MatchResult {
    Item item;
    double textSimilarity{}, locationSimilarity{}, categorySimilarity{}, dateSimilarity{}, finalScore{};
};
class MatchEngine {
public:
    explicit MatchEngine(const TextPreprocessor& preprocessor);
    std::vector<MatchResult> findMatches(const Item& query,
                                         const std::vector<Item>& candidates) const;
private:
    const TextPreprocessor& preprocessor_;
    static double exactSimilarity(const std::string& a, const std::string& b);
    static double dateSimilarity(const std::string& a, const std::string& b);
    static double clamp(double value);
};
