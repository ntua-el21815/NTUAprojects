#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <stack>

class Graph{
    public:
       Graph(int V) {
           this->Vertices = V;
           adj = new std::list<int>[V];
       }
       ~Graph() { delete [] adj; }
        void addEdge(int u,int v){
            for(int u:adj[v]){
                if(u==v){
                    return;
                }
            }
            adj[u].push_back(v);
        }
        bool dfscycle(int source,std::vector<int> &visited,std::vector<int> &path){
            std::vector<bool> temp_visited(Vertices,false);
            std::stack<int> s;
            s.push(source);
            while(!s.empty()){
                int u = s.top();
                s.pop();
                if(temp_visited[u] && visited[u] < 2 && !adj[u].empty()){
                    return true;
                }
                visited[u] ++;
                temp_visited[u] = true;
                if(!adj[u].empty()){
                    path.push_back(u);
                }
                for(int v:adj[u]){
                        s.push(v);
                }
            }
            return false;
        }
        bool cycle(std::vector<int> &path){
            std::vector<int> visited(Vertices,0);
            for(int i=0;i<Vertices;i++){
                if(!visited[i]){
                    if(dfscycle(i,visited,path)){
                        return true;
                    }
                }
                path.clear();
            }
            return false;
        }
    private:
        int Vertices;
        std::list<int> * adj;

};
#ifndef CONTEST

int main(){
    int V, E;
    std::cin >> V >> E;
    Graph g(V);
    for (int i = 0; i < E; i++)
    {
        int u, v;
        std::cin >> u >> v;
        g.addEdge(u, v);
    }
    std::vector<int> path;
    if(g.cycle(path)){
        std::cout << "CYCLE ";
        for(auto i : path)
            std::cout << i << " ";
        std::cout << std::endl;
    } 
    else
        std::cout << "NO CYCLE\n";
    return 0;
}

#endif
