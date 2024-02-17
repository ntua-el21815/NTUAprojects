#include<iostream>
#include<queue>
#include<stack>

void printqueue(std::queue<int> q){
    while(!q.empty()){
        std::cout<<q.front();
        if(q.size()>1)
            std::cout<<" ";
        q.pop();
    }
    std::cout<<std::endl;
}

void doMoves(std::string s,std::queue<int> q,std::stack<int> st){
    for(unsigned int i=0;i<s.length();i++){
        if(s[i]=='P'){
            printqueue(q);
        }
        if(s[i]=='Q'){
            if(!q.empty()){
                st.push(q.front());
                q.pop();
            }
            else{
                std::cout<<"error"<<std::endl;
                return;
            }
        }
        if(s[i]=='S'){
            if(!st.empty()){
                q.push(st.top());
                st.pop();
            }
            else{
                std::cout<<"error"<<std::endl;
                return;
            }
        }
    }
}

int main(){
    std::stack<int> s;
    std::queue<int> q;
    unsigned int N;
    std::cin>>N;
    for(unsigned int i=0;i<N;i++){
        int x;
        std::cin>>x;
        q.push(x);
    }
    std::string moves;
    std::cin>>moves;
    doMoves(moves,q,s);
}