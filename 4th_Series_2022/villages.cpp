#include<iostream>

class unionFind{
    private:
        struct Node{
            int parent;
            int rank;
        };
        Node *nodes;
        int size;
        int independent_sets;
    public:
        unionFind(int n){
            size = n;
            independent_sets = n;
            nodes = new Node[n+1];
            for(int i = 1; i <= n; i++){
                nodes[i].parent = i;
                nodes[i].rank = 0;
            }
        }
        ~unionFind(){
            delete[] nodes;
        }
        int find(int x){
            if(nodes[x].parent == x)
                return x;
            return nodes[x].parent = find(nodes[x].parent);
        }
        void union_op(int x,int y){
            int ap_x = find(x);
            int ap_y = find(y);
            if(ap_x == ap_y)
                return;
            if(nodes[ap_x].rank < nodes[ap_y].rank){
                nodes[ap_x].parent=ap_y;
                independent_sets--;
            }
            else if(nodes[ap_x].rank > nodes[ap_y].rank){
                nodes[ap_y].parent=ap_x;
                independent_sets--;
            }
            else{
                nodes[ap_y].parent=ap_x;
                nodes[ap_x].rank++;
                independent_sets--;
            }
            
        }
        int get_independent_sets(){
            return independent_sets;
        }
};

int main(){
    int N,M,K;
    scanf("%d %d %d",&N,&M,&K);
    unionFind connections(N);
    for(int i = 0; i < M; i++){
        int x,y;
        scanf("%d %d",&x,&y);
        connections.union_op(x,y);
    }
    printf("%d\n",std::max(connections.get_independent_sets()-K,1));
}

