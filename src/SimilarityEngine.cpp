#include "SimilarityEngine.h"
#include <cmath>
#include <stdexcept>
double SimilarityEngine::cosineSimilarity(const std::vector<double>& a,const std::vector<double>& b) {
    if(a.size()!=b.size()) throw std::invalid_argument("Vectors must have the same dimension");
    double dot=0,normA=0,normB=0;
    for(std::size_t i=0;i<a.size();++i){dot+=a[i]*b[i];normA+=a[i]*a[i];normB+=b[i]*b[i];}
    if(normA==0 || normB==0) return 0;
    return dot/(std::sqrt(normA)*std::sqrt(normB));
}
