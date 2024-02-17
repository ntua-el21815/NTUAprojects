#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>

enum state{
    UNVISITED,
    VISITING,
    VISITED
};
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
        bool dfscycle(int source,std::vector<state> &visited){
            visited[source] = VISITING;
            for(int n:adj[source]){
                if(visited[n] == VISITING){
                    //path.push_back(n);
                    return true;
                }
                if(visited[n] == UNVISITED && dfscycle(n,visited)){
                    //path.push_back(n);
                    return true;
                }
            }
            visited[source] = VISITED;
            return false;
        }
        bool cycle(std::vector<int> &path){
            std::vector<state> visited(Vertices,UNVISITED);
            for(int i=0;i<Vertices;i++){
                if(visited[i] == UNVISITED && dfscycle(i,visited)){
                    for(int j=0;j<Vertices;j++){
                        if(visited[j] == VISITING){
                            path.push_back(j);
                        }
                    }
                    return true;
                }
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

