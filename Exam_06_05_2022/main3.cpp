#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>


class employee {
    private:
        std::string id;
        std::string name;
        std::string surname;
        std::string year_of_birth;
        std::string salary;
    public:
        std::map<std::string,std::string> map; 
        employee(std::string id, std::string name, std::string surname, std::string year_of_birth, std::string salary) {
            this->id = id;
            this->name = name;
            this->surname = surname;
            this->year_of_birth = year_of_birth;
            this->salary = salary;
            this->map = {{"id", id}, {"name", name}, {"surname", surname}, {"year", year_of_birth}, {"salary", salary}};  
        }
};
struct compare{
    std::string ord;
    std::string b;
    compare(std::string order, std::string by) : ord(order), b(by) {};
    bool operator () (employee const & e1,employee const & e2) const {
        if(b == "name"){
            if(e1.map.at("surname") == e1.map.at("surname") && e1.map.at("name") == e2.map.at("name")){
                return ord == "asc" ? e1.map.at("id") < e2.map.at("id") : e1.map.at("id") > e2.map.at("id");
            }
            if(e1.map.at("surname") == e2.map.at("surname")){
                return ord == "asc" ? e1.map.at("name") < e2.map.at("name") : e1.map.at("name") > e2.map.at("name");
            }
            return ord == "asc" ? e1.map.at("surname") < e2.map.at("surname") : e1.map.at("surname") > e2.map.at("surname");
        }
        if(e1.map.at(b) == e2.map.at(b)){
            return ord == "asc" ? e1.map.at("id") < e2.map.at("id") : e1.map.at("id") > e2.map.at("id");
        }
        return ord == "asc" ? e1.map.at(b) < e2.map.at(b) : e1.map.at(b) > e2.map.at(b);
    }
};


int main(){
    std::vector<employee> employees;
    std::string id, name, surname, year_of_birth, salary;
    int N;
    std::cin >> N;
    for(int i = 0; i < N; i++){
        std::cin >> id >> name >> surname >> year_of_birth >> salary;
        employees.push_back(employee(id, name, surname, year_of_birth, salary));
    }
    int K;
    std::cin >> K;
    for(int i = 0; i < K; i++){
        std::string order, by;
        int number_of_entries;
        std::cin >> by >> order >> number_of_entries;
        std::sort(employees.begin(), employees.end(), compare(order, by));
        for(int j = 0; j < number_of_entries; j++){
            std::cout << employees[j].map.at("id") << " " << employees[j].map.at("name") << " " << employees[j].map.at("surname") << " " << employees[j].map.at("year") << " " << employees[j].map.at("salary") << std::endl;
        }
    }
}