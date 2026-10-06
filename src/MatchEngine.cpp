#include "MatchEngine.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>
namespace {
std::time_t parseDate(const std::string& date) {
    std::tm tm{};
    std::istringstream input(date);
    input >> std::get_time(&tm,"%Y-%m-%d");
    if(input.fail()) return static_cast<std::time_t>(-1);
    tm.tm_hour=12;
    return std::mktime(&tm);
}
}
MatchEngine::MatchEngine(const TextPreprocessor& p):preprocessor_(p){}
double MatchEngine::clamp(double value){return std::max(0.0,std::min(1.0,value));}
double MatchEngine::exactSimilarity(const std::string&a,const std::string&b){
    if(a.empty()||b.empty()) return 0;
    return a==b?1.0:0.0;
}
double MatchEngine::dateSimilarity(const std::string&a,const std::string&b){
    const auto first=parseDate(a),second=parseDate(b);
    if(first==(std::time_t)-1||second==(std::time_t)-1) return 0;
    const double days=std::abs(std::difftime(first,second))/(60.0*60.0*24.0);
    if(days==0) return 1.0; if(days<=1) return .9; if(days<=3) return .7; if(days<=7) return .4; return 0;
}
std::vector<MatchResult> MatchEngine::findMatches(const Item& query,const std::vector<Item>& candidates) const {
    std::vector<Item> eligible;
    for(const auto& c:candidates){
        if(c.id==query.id||c.status!=ItemStatus::ACTIVE||c.type==query.type) continue;
        eligible.push_back(c);
    }
    if(eligible.empty()) return {};
    std::vector<std::string> documents{query.searchableText()};
    for(const auto& c:eligible) documents.push_back(c.searchableText());
    TfidfVectorizer vectorizer(preprocessor_);
    const auto vectors=vectorizer.fitTransform(documents);
    std::vector<MatchResult> results;
    for(std::size_t i=0;i<eligible.size();++i){
        const auto& c=eligible[i];
        const double text=clamp(SimilarityEngine::cosineSimilarity(vectors[0],vectors[i+1]));
        const double location=exactSimilarity(preprocessor_.normalize(query.location),preprocessor_.normalize(c.location));
        const double category=exactSimilarity(preprocessor_.normalize(query.category),preprocessor_.normalize(c.category));
        const double date=dateSimilarity(query.date,c.date);
        const double score=.70*text+.15*location+.10*category+.05*date;
        results.push_back({c,text,location,category,date,score});
    }
    std::sort(results.begin(),results.end(),[](const MatchResult&a,const MatchResult&b){return a.finalScore>b.finalScore;});
    return results;
}
