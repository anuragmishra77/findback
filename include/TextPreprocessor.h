#pragma once
#include <string>
#include <unordered_set>
#include <vector>
class TextPreprocessor {
public:
    TextPreprocessor();
    std::vector<std::string> tokenize(const std::string& text) const;
    std::string normalize(const std::string& text) const;
private:
    std::unordered_set<std::string> stopWords_;
    std::string stem(const std::string& token) const;
    bool isStopWord(const std::string& token) const;
};
