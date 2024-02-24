#include<iostream>

int findMaxSum(int* array,int N,int K){
    int max_sum=array[0]+array[K];
    int max_term=array[0];
    for(int i=0;i<N;i++){
        if(array[i]>max_term) max_term=array[i];
        else continue;
        for(int j=std::max(i+1,i+K);j<N;j++){
            if(array[j]+array[i]>max_sum){
                max_sum=array[j]+array[i];
            }
        }
    }
    return max_sum;
}

void readArray(int N,int* array){
    for(int i=0;i<N;i++){
        std::cin>>array[i];
    }
}


int main(){
    int seq[1000];
    int N,K;
    std::cin>>N>>K;
    readArray(N,seq);
    std::cout<<findMaxSum(seq,N,K)<<'\n';
}