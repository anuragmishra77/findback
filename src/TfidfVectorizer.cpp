#include "TfidfVectorizer.h"
#include <cmath>
#include <unordered_set>
TfidfVectorizer::TfidfVectorizer(const TextPreprocessor& p) : preprocessor_(p) {}
std::vector<std::string> TfidfVectorizer::terms(const std::string& d) const {
    return preprocessor_.tokenize(d);
}
void TfidfVectorizer::fit(const std::vector<std::string>& documents) {
    vocabulary_.clear(); idf_.clear();
    std::vector<std::unordered_set<std::string>> documentTerms;
    for (const auto& document : documents) {
        std::unordered_set<std::string> unique;
        for (const auto& term : terms(document)) {
            unique.insert(term);
            if (!vocabulary_.count(term)) vocabulary_[term] = vocabulary_.size();
        }
        documentTerms.push_back(std::move(unique));
    }
    const double n = static_cast<double>(documents.size());
    idf_.resize(vocabulary_.size(), 0.0);
    if (documents.empty()) { fitted_=true; return; }
    for (const auto& [term,index] : vocabulary_) {
        std::size_t df=0;
        for (const auto& unique : documentTerms) if (unique.count(term)) ++df;
        idf_[index] = std::log((1.0+n)/(1.0+static_cast<double>(df)))+1.0;
    }
    fitted_=true;
}
std::vector<double> TfidfVectorizer::transform(const std::string& document) const {
    std::vector<double> vector(vocabulary_.size(),0.0);
    if (!fitted_ || vocabulary_.empty()) return vector;
    const auto tokens=terms(document);
    if (tokens.empty()) return vector;
    std::unordered_map<std::string,double> frequency;
    for (const auto& token:tokens) if(vocabulary_.count(token)) ++frequency[token];
    const double total=static_cast<double>(tokens.size());
    for(const auto& [term,count]:frequency) {
        const auto index=vocabulary_.at(term);
        vector[index]=(count/total)*idf_[index];
    }
    return vector;
}
std::vector<std::vector<double>> TfidfVectorizer::fitTransform(const std::vector<std::string>& documents) {
    fit(documents);
    std::vector<std::vector<double>> result;
    for(const auto& document:documents) result.push_back(transform(document));
    return result;
}
std::size_t TfidfVectorizer::vocabularySize() const { return vocabulary_.size(); }
