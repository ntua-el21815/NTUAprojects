#include<iostream>
#include<set>
#include<vector>

int main(){
    std::set<int> myset;
    std::vector<int> doubles;
    int x=1;
    while(x != std::cin.eof()){
        std::cin>>x;
        if(myset.count(x)){
            doubles.push_back(x);
        }
        myset.insert(x);
    }
    for(int i=0;i<doubles.size();i++){
        printf("DUPLICATE #%d: %d\n",i+1,doubles[i]);
    }
    if(doubles.size() == 0){
        printf("NO DUPLICATES FOUND");
    }
}