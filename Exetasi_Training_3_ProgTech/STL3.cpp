#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<utility>

void storeText(std::map<char,std::vector<std::string>> & firstLetter){
    while(std::cin.eof()==false){
        std::string s;
        std::cin >> s;
        firstLetter[s[0]].push_back(s);
    }
}

std::pair<int,int> findWordsBeg(std::map<char,std::vector<std::string>> const & firstLetter,char letter){
    int total_words = firstLetter.at(letter).size();
    int unique_words = firstLetter.at(letter).size();
    for(int i=0;i<firstLetter.at(letter).size();i++){
        for(int j=i+1;j<firstLetter.at(letter).size();j++){
            if(firstLetter.at(letter).at(i)==firstLetter.at(letter).at(j)){
                unique_words--;
                break;
            }
        }
    }
    return std::make_pair(total_words,unique_words);
}

std::pair<std::string,std::string> findMaxMin(std::map<char,std::vector<std::string>> const & firstLetter,char letter){
    std::string max_word = firstLetter.at(letter).at(0);
    for(int i=1;i<firstLetter.at(letter).size();i++){
        if(max_word.size()<firstLetter.at(letter).at(i).size()){
            max_word = firstLetter.at(letter).at(i);
        }
        if(firstLetter.at(letter).at(i).size() == max_word.size() && firstLetter.at(letter).at(i)<max_word){
            max_word = firstLetter.at(letter).at(i);
        }
    }
    std::string min_word = firstLetter.at(letter).at(0);
    for(int i=1;i<firstLetter.at(letter).size();i++){
        if(min_word.size()>firstLetter.at(letter).at(i).size()){
            min_word = firstLetter.at(letter).at(i);
        }
        if(firstLetter.at(letter).at(i).size() == min_word.size() && firstLetter.at(letter).at(i)<min_word){
            min_word = firstLetter.at(letter).at(i);
        }
    }
    return std::make_pair(max_word,min_word);
}

/*void printText(std::map<char,std::vector<std::string>> const & firstLetter){
    for(std::pair<char,std::vector<std::string>>const & p: firstLetter){
        for(std::string const & s: p.second){
            std::cout << p.first << " : " << s << std::endl;
        }
    }
}*/

int main(){
    std::map<char,std::vector<std::string>> firstLetter;
    storeText(firstLetter);
    for(std::pair<char,std::vector<std::string>>const & p: firstLetter){
        if('a'<= p.first && p.first<='z')std::cout << p.first << ": " << findWordsBeg(firstLetter,p.first).first 
        << " word(s), " << findWordsBeg(firstLetter,p.first).second << " unique word(s), " <<
        "longest \'"<< findMaxMin(firstLetter,p.first).first <<
        "\' and shortest \'" << findMaxMin(firstLetter,p.first).second << "\'" << std::endl;
    }
}