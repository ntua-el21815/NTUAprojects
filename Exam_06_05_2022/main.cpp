#include<iostream>
#include<vector>
#include<map>
#include<tuple>
#include<algorithm>

bool asc(std::pair<std::string, std::string> a, std::pair<std::string, std::string> b) {
    if(a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

bool desc(std::pair<std::string, std::string> a, std::pair<std::string, std::string> b) {
    if(a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

bool asc_2(std::pair<std::string, std::pair<std::string,std::string>> a, std::pair<std::string, std::pair<std::string,std::string>> b) {
    if(a.second.second == b.second.second) {
        return a.second.first < b.second.first;
    }
    return a.second.second < b.second.second;
}

bool desc_2(std::pair<std::string, std::pair<std::string,std::string>> a, std::pair<std::string, std::pair<std::string,std::string>> b) {
    if(a.second.second == b.second.second) {
        return a.second.first > b.second.first;
    }
    return a.second.second > b.second.second;
}

std::vector<std::pair<std::string, std::string>> sort_map(std::map<std::string, std::string> m, std::string order) {
    std::vector<std::pair<std::string, std::string>> v;
    for (auto &i : m) {
        v.push_back(std::make_pair(i.first, i.second));
    }
    std::sort(v.begin(), v.end(), order == "asc" ? asc : desc);
    return v;
}


int main(){
    std::map<std::string, std::string> ids_to_names;
    std::map<std::string, std::string> ids_to_surnames;
    std::map<std::string, std::string> ids_to_years;
    std::map<std::string, std::string> ids_to_salaries;
    int N;
    std::cin>>N;
    for(int i=0;i<N;i++){
        std::string id;
        std::string name;
        std::string surname;
        std::string year;
        std::string salary;
        std::cin>>id>>name>>surname>>year>>salary;
        ids_to_names[id] = name;
        ids_to_surnames[id] = surname;
        ids_to_years[id] = year;
        ids_to_salaries[id] = salary;
    }
    int K;
    std::cin>>K;
    for(int i=0;i<K;i++){
        std::string category;
        std::string order;
        int numOfElements;
        std::cin>>category>>order>>numOfElements;
        std::vector<std::pair<std::string,std::string>> v1 = sort_map(ids_to_surnames, order);
        std::vector<std::pair<std::string,std::string>> v2 = sort_map(ids_to_years, order);
        std::vector<std::pair<std::string,std::string>> v3 = sort_map(ids_to_salaries, order);
        std::vector<std::pair<std::string,std::pair<std::string,std::string>>> vsp;
        std::cout<< "Query: " << category << " " << order << " " << numOfElements <<  std::endl;
        switch(category[0]){
            case 'n':  
                for(int j=0;j<numOfElements;j++){
                    vsp.push_back(std::make_pair(v1[j].first, std::make_pair(ids_to_names[v1[j].first], v1[j].second)));
                }
                std::sort(vsp.begin(), vsp.end(), order == "asc" ? asc_2 : desc_2);
                for(int i=0;i<numOfElements;i++){
                    std::cout<<vsp[i].first<<" "<<vsp[i].second.first << " " << vsp[i].second.second << " " << ids_to_years[vsp[i].first] << " " << ids_to_salaries[vsp[i].first] << std::endl;
                }
                break;
            case 'y':
                for(int j=0;j<numOfElements;j++){
                    std::cout<<v2[j].first<<" "<< ids_to_names[v2[j].first]<< " " << ids_to_surnames[v2[j].first] << " " << ids_to_years[v2[j].first]<< " " << ids_to_salaries[v2[j].first]<<std::endl;
                }
                break;
            case 's':
                for(int j=0;j<numOfElements;j++){
                    std::cout<<v3[j].first<<" "<< ids_to_names[v3[j].first]<< " " << ids_to_surnames[v3[j].first] << " " << ids_to_years[v3[j].first]<< " " << ids_to_salaries[v3[j].first]<<std::endl;
                }
                break;
            case 'i':
                for(auto r : ids_to_names){
                    std::cout<<r.first<<" "<< r.second<< " " << ids_to_surnames[r.first] << " " << ids_to_years[r.first]<< " " << ids_to_salaries[r.first]<<std::endl;
                }
        }       
    }

}