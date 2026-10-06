#include "TextPreprocessor.h"
#include <cctype>
#include <sstream>
TextPreprocessor::TextPreprocessor()
    : stopWords_{"a","an","and","are","at","be","been","for","from","has",
                 "have","in","is","it","of","on","or","the","this","to","was","with"} {}
bool TextPreprocessor::isStopWord(const std::string& token) const {
    return stopWords_.count(token) > 0;
}
std::string TextPreprocessor::stem(const std::string& token) const {
    if (token.size() > 4 && token.compare(token.size()-3,3,"ing") == 0)
        return token.substr(0, token.size()-3);
    if (token.size() > 3 && token.compare(token.size()-2,2,"ed") == 0)
        return token.substr(0, token.size()-2);
    if (token.size() > 3 && token.back() == 's')
        return token.substr(0, token.size()-1);
    return token;
}
std::vector<std::string> TextPreprocessor::tokenize(const std::string& text) const {
    std::string cleaned;
    for (unsigned char ch : text)
        cleaned += std::isalnum(ch) ? static_cast<char>(std::tolower(ch)) : ' ';
    std::istringstream input(cleaned);
    std::vector<std::string> tokens;
    std::string token;
    while (input >> token)
        if (!isStopWord(token)) tokens.push_back(stem(token));
    return tokens;
}
std::string TextPreprocessor::normalize(const std::string& text) const {
    const auto tokens = tokenize(text);
    std::ostringstream output;
    for (std::size_t i=0; i<tokens.size(); ++i) {
        if (i) output << ' ';
        output << tokens[i];
    }
    return output.str();
}
