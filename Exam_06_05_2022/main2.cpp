#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<algorithm>
#include<map>


struct compare{
    int elem;
    std::string ord;
    compare(int element,std::string order) : elem(element), ord(order) {}
    bool operator () (std::vector<std::string> & vec1, std::vector<std::string> & vec2){
        if (elem == 1) {
            if(vec1[elem] == vec2[elem] && vec1[elem+1] == vec2[elem+1]){
                return ord == "asc" ? vec1[0] < vec2[0] : vec1[0] > vec2[0];
            }
            if(vec1[elem+1] == vec2[elem+1]){
                return ord == "asc" ? vec1[elem] < vec2[elem] : vec1[elem] > vec2[elem];
            }
            return ord == "asc" ? vec1[elem+1] < vec2[elem+1] : vec1[elem+1] > vec2[elem+1];
        }
        if(vec1[elem] == vec2[elem]){
            return ord == "asc" ? vec1[0] < vec2[0] : vec1[0] > vec2[0];
        }
        return ord == "asc" ? vec1[elem] < vec2[elem] : vec1[elem] > vec2[elem];
    }
};

std::vector<std::vector<std::string>> findExtremeValues(std::vector<std::vector<std::string>> & vec, std::string order , int num_of_elements, int category){
    std::vector<std::vector<std::string>> result;
    std::sort(vec.begin(), vec.end(), compare(category, order));
    for(int i = 0; i < num_of_elements; i++){
        result.push_back(vec[i]);
    }
    return result;
}

int main(){
    std::vector<std::vector<std::string>> vec;
    std::map<std::string, int> representation = {{"id", 0}, {"name", 1}, {"surname", 2}, {"year", 3}, {"salary", 4}};
    int N;
    std::cin >> N;
    vec.resize(N);
    for(int i = 0; i < N; i++){
        std::vector<std::string> temp;
        std::string temp_str;
        temp.resize(5);
        for(int j = 0; j < 5; j++){
            std::cin >> temp_str;
            temp[j] = temp_str;
        }
        vec[i] = temp;
    }
    int K;
    std::cin >> K;
    for(int i = 0; i < K; i++){
        std::string order;
        int num_of_elements;
        std::string category;
        std::cin >> category >> order >> num_of_elements;
        std::vector<std::vector<std::string>> result = findExtremeValues(vec, order, num_of_elements, representation[category]);
        for(int j = 0; j < result.size(); j++){
            for(int k = 0; k < result[j].size(); k++){
                std::cout << result[j][k] << " ";
            }
            std::cout << std::endl;
        }
    }
}