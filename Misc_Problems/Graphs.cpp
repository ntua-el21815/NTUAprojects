#include<iostream>
#include<unordered_map>
#include<queue>
#include<stack>
#include<vector>
#include<set>

void depthFirstPrint(std::unordered_map<char,std::vector<char>> & graph,char source){
    std::set<char> visited;
    std::stack<char> s;
    s.push(source);
    while(!s.empty()){
        char current = s.top();
        s.pop();
        std::cout<< current << " ";
        visited.insert(current);
        if(!graph[current].empty()){
            for(char c: graph[current]){
            if(!visited.count(c))s.push(c);
            }
        }
    }
    return;
}
void depthFirstRecursive(std::unordered_map<char,std::vector<char>> & graph,char source,std::set<char> & visited){
    std::cout<< source << " ";
    visited.insert(source);
    if(!graph[source].empty()){
        for(char c:graph[source])
            if(!visited.count(c))depthFirstRecursive(graph,c,visited);
    }
}
void breadthFirstPrint(std::unordered_map<char,std::vector<char>> & graph,char source){
    std::set<char> visited;
    std::queue<char> q;
    q.push(source);
    visited.insert(source);
    while(!q.empty()){
        char current = q.front();
        q.pop();
        std::cout<< current << " ";
            for(char c: graph[current]){
                if(!visited.count(c)){ 
                    visited.insert(c);
                    q.push(c);
                }
            }
    }
    return;
}

bool hasPath(std::unordered_map<char,std::vector<char>> graph,char source,char dest){
    std::set<char> visited;
    std::stack<char> s;
    s.push(source);
    while(!s.empty()){
        char current = s.top();
        s.pop();
        visited.insert(current);
        if(current == dest){
            return true;
        }
        if(!graph[current].empty()){
            for(char c: graph[current]){
            if(!visited.count(c)) s.push(c);
            }
        }
    }
    return false;
}

int main(){
    std::unordered_map<char,std::vector<char>> graph;
    /* 
        i -> j,k
        j -> i,k
        k -> i,l,m
        m -> k
        o -> n
        n -> o
    */
    graph['i'].push_back('j');
    graph['i'].push_back('k');
    graph['j'].push_back('i');
    graph['j'].push_back('k');
    graph['k'].push_back('i');
    graph['k'].push_back('l');
    graph['k'].push_back('m');
    graph['m'].push_back('k');
    graph['o'].push_back('n');
    graph['n'].push_back('o');
    std::string answer = hasPath(graph,'j','o') ? "Yes" : "No";
    std::cout<< answer << std::endl;
    depthFirstPrint(graph,'i');
    std::cout<< std::endl;
    std::set<char> visited;
    depthFirstRecursive(graph,'i',visited);
    std::cout<< std::endl;
    breadthFirstPrint(graph,'i');
    std::cout<< std::endl;   
}