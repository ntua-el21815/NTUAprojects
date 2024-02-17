#include<iostream> 
#include<string>
#include<map>
#include<vector>
#include<tuple>

std::tuple <int,int> findMaxDict (std::vector<std::vector<std::string>> const & vec){
    unsigned int max_books = 0;
    unsigned int max_dict = 0;
    for(unsigned int i = 0; i < vec.size(); i++){
        if(vec[i].size() > max_books){
            max_books = vec[i].size();
            max_dict = i;
        }
    }
    return std::make_tuple(max_books, max_dict);
}

std::vector<std::string> wordsInAllDict(std::vector<std::vector<std::string>> const & vec,unsigned int D){
    std::map<std::string, int> dict;
    std::vector<std::string> words;
    for(std::vector<std::string> const & v : vec){
        for(std::string const & s : v){
            dict[s]=0;
        }
    }
    for(std::vector<std::string> const & v : vec){
        for(std::string const & s : v){
            dict[s]++;
        }
    }
    for(std::pair<std::string,int> const & p : dict){
        if(p.second == D){
            words.push_back(p.first);
        }
    }
    return words;
}

int main(){
    unsigned int N,D;
    std::vector<std::vector<std::string>> vec(100);
    std::cin >> N >> D;
    for(unsigned int i=0;i<N;i++){
        unsigned int d;
        std::string s;
        std::cin >>d;
        std::cin >> s;
        bool in_vector = false;
        for(unsigned int j=0;j<vec[d].size();j++){
            if(vec[d][j] == s) in_vector = true;
        }
        if(!in_vector) vec[d].push_back(s);
    }
    std::tuple <int,int> max_dict = findMaxDict(vec);
    std::vector<std::string> words = wordsInAllDict(vec,D);
    std::cout<< "largest dictionary is " << std::get<1>(max_dict) << " with " << std::get<0>(max_dict) << " word(s)" << std::endl;
    unsigned int total_words = 0;
    for(std::string const & s : words){
        std::cout << s << std::endl;
        total_words++;
    }
    std::cout << total_words << " word(s) appear in all dictionaries"<<std::endl;
}
