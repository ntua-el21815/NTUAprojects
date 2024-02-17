#include<iostream>
using namespace std;

void swap(int *x,int *y){
    int temp = *x;
    *x = *y;
    *y =temp;
}
bool checkAndSwap(int *array,int N,int *count){
    bool check;
    for(int i=0;i<N;i++){
        check=0;
        if(array[i]>0 && array[i+1]<0){
            swap(array[i],array[i+1]);
            count++;
            check=1;
        }
    }
    return check;
}

int main(){
    int N;
    int *counter=0;
    cin>>N;
    int Seq[100000];
    for(int i=0;i<N;i++){
        cin>>Seq[i];
    }
    while(checkAndSwap(Seq,N,counter));
    printf("%d\n",counter);
    printf("%d\n",Seq[0]);
    printf("%d\n",Seq[N-1]);
}