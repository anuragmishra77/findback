#include "Item.h"
#include "MatchEngine.h"
#include "SimilarityEngine.h"
#include "TextPreprocessor.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
namespace {
void printItem(const Item& item){
    std::cout<<"["<<item.id<<"] "<<toString(item.type)<<" | "<<item.name<<" | "
             <<item.category<<" | "<<item.location<<" | "<<item.date<<" | "<<toString(item.status)<<"\n"
             <<"    "<<item.description<<"\n";
}
void printMatches(const std::vector<MatchResult>& matches){
    if(matches.empty()){std::cout<<"No eligible matches found.\n";return;}
    std::cout<<"\nRanked matches:\n";
    int rank=1;
    for(const auto& m:matches){
        std::cout<<rank++<<". "<<m.item.name<<" ["<<std::fixed<<std::setprecision(1)<<m.finalScore*100<<"%]\n";
        std::cout<<"   text="<<m.textSimilarity*100<<"%, location="<<m.locationSimilarity*100
                 <<"%, category="<<m.categorySimilarity*100<<"%, date="<<m.dateSimilarity*100<<"%\n";
        std::cout<<"   "<<m.item.description<<"\n";
    }
}
void runDemo(){
    TextPreprocessor preprocessor; MatchEngine matcher(preprocessor);
    const Item lost{1,ItemType::LOST,"Wallet","wallet",
        "black leather wallet with a small metal logo and student card",
        "central library","2026-10-05",ItemStatus::ACTIVE};
    const std::vector<Item> found{
        {2,ItemType::FOUND,"Black leather wallet","wallet",
         "dark leather wallet with metal logo and college student card",
         "central library","2026-10-05",ItemStatus::ACTIVE},
        {3,ItemType::FOUND,"Blue water bottle","bottle",
         "blue steel bottle with a sticker","sports complex","2026-10-04",ItemStatus::ACTIVE},
        {4,ItemType::FOUND,"Black purse","bag",
         "small black purse found near the library entrance",
         "central library","2026-10-07",ItemStatus::ACTIVE}};
    std::cout<<"=== FindBack: Intelligent Lost & Found ===\n\nQuery item:\n"; printItem(lost);
    std::cout<<"\nCandidates:\n"; for(const auto& item:found) printItem(item);
    printMatches(matcher.findMatches(lost,found));
}
void runSelfTest(){
    TextPreprocessor p;
    const auto tokens=p.tokenize("The black leather wallets are running");
    if(tokens.size()!=4) throw std::runtime_error("Preprocessor test failed");
    const double similarity=SimilarityEngine::cosineSimilarity({1.0,0.0},{1.0,0.0});
    if(std::abs(similarity-1.0)>1e-9) throw std::runtime_error("Cosine similarity test failed");
    std::cout<<"All self-tests passed.\n";
}
}
int main(int argc,char* argv[]){
    try { if(argc>1&&std::string(argv[1])=="--test") runSelfTest(); else runDemo(); }
    catch(const std::exception& error){std::cerr<<"Error: "<<error.what()<<"\n";return 1;}
    return 0;
}
