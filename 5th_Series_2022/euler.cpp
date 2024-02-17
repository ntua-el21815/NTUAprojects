#include<iostream>
#include <list>
#include <tuple>

class Graph{
	int Vertices;
	std::list<int> *adj;
public:
	Graph(int V) {this->Vertices = V; adj = new std::list<int>[V]; }
	~Graph() { delete [] adj; }
	void addEdge(int v, int w){
        adj[v].push_back(w);
        adj[w].push_back(v); 
    }
	std::tuple<int,int,int> hasPathOrCycle(){
        int start = 0;
        int end = 0;
        int result  = 0;
        // Count vertices with odd degree
        int odd = 0;
        int count = 0;
        for(int i = 0; i < Vertices; i++){
            if(adj[i].size() % 2 != 0){
                odd++;
                start = (odd == 1) ? i : start;
                end = (odd == 2) ? i : end;
            }
        }

        if (odd > 2)
            result = 0;
        else result = (odd)? 1 : 2;        
        return std::make_tuple(result,start,end);
    }
};

int main()
{
	int V, E;
    std::cin >> V >> E;
    Graph g(V);
    for (int i = 0; i < E; i++)
    {
        int v, w;
        std::cin >> v >> w;
        g.addEdge(v, w);
    }
    std::tuple<int,int,int> result = g.hasPathOrCycle();
    if (std::get<0>(result) == 0)
        std::cout << "IMPOSSIBLE" << "\n";
    else if (std::get<0>(result) == 1)
        std::cout << "PATH " << std::get<1>(result) << " " << std::get<2>(result) << "\n";
    else
        std::cout << "CYCLE" << "\n";
    return 0;
}
