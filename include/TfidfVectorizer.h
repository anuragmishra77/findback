#pragma once
#include "TextPreprocessor.h"
#include <string>
#include <unordered_map>
#include <vector>
class TfidfVectorizer {
public:
    explicit TfidfVectorizer(const TextPreprocessor& preprocessor);
    void fit(const std::vector<std::string>& documents);
    std::vector<double> transform(const std::string& document) const;
    std::vector<std::vector<double>> fitTransform(const std::vector<std::string>& documents);
    std::size_t vocabularySize() const;
private:
    const TextPreprocessor& preprocessor_;
    std::unordered_map<std::string, std::size_t> vocabulary_;
    std::vector<double> idf_;
    bool fitted_{false};
    std::vector<std::string> terms(const std::string& document) const;
};
