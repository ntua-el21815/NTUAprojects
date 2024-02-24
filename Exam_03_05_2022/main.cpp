#include<iostream>
#include<map>
#include<string>
#include<utility>
#include<vector>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<tuple>

std::tuple<std::pair<double,double>,std::map<std::string,double>> 
findMInDistance(std::pair<double,double> const & point , std::map<std::pair<double,double>,std::string> const & map){
    double x1 = point.first;
    double y1 = point.second;
    std::map<std::string,double> min_map;
    for(auto const & it : map){
        min_map.insert(std::make_pair(it.second,std::numeric_limits<double>::max()));
    }
    for(auto const & it : map){
        double x2 = it.first.first;
        double y2 = it.first.second;
        double distance = std::sqrt(std::pow(x1-x2,2)+std::pow(y1-y2,2));
        if(distance < min_map[it.second]){
            min_map[it.second] = distance;
            if (min_map.find(it.second) == min_map.end()){
                min_map.insert(std::make_pair(it.second,distance));
            }
            else{
                min_map.erase(it.second);
                min_map.insert(std::make_pair(it.second,distance));
            }
        }
    }
    return std::make_tuple(point,min_map);
}

int main(){
    std::vector<std::pair<double,double>> points;
    std::map<std::pair<double,double>,std::string> pois;
    std::vector<std::tuple<std::pair<double,double>,std::map<std::string,double>>> results;
    int N,K;
    std::cin >> N;
    for(int i = 0; i < N; i++){
        double x,y;
        std::string s;
        std::cin >> x >> y >> s;
        pois.insert(std::make_pair(std::make_pair(x,y),s));
    }
    std::cin >> K;
    for(int i = 0; i < K; i++){
        double x,y;
        std::cin >> x >> y;
        points.push_back(std::make_pair(x,y));
    }
    for(auto const & point : points){
        results.push_back(findMInDistance(point,pois));
    }
    for(auto const & result : results){
        std::cout << std::get<0>(result).first << " " << std::get<0>(result).second << std::endl;
        for(auto const & it : std::get<1>(result)){
            std::cout << "  "  << it.first << " " << it.second << std::endl;
        }
    }
}