#include <iostream>

int findMaxDiff(int *array,int N){
    int dif=0;
    int min_term=array[0];
    for(int i=0;i<N;i++){
    if(array[i]>=min_term) continue;
    else min_term=array[i];
        for(int j=i+1;j<N;j++){
            if(dif<=array[j]-array[i]) dif=array[j]-array[i] ;
        }
    }
    return dif;
}

void readArray(int N,int* array){
    for(int i=0;i<N;i++){
        std::cin>>array[i];
    }
}

int main(){
    int N;
    int sequence[100000];
    std::cin>>N;
    readArray(N,sequence);
    std::cout<<findMaxDiff(sequence,N)<<'\n';
}