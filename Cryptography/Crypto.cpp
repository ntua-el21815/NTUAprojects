#include<iostream>
using namespace std;

int readText(int *input){
    int discard=getchar();
    int size=0;
    int c=getchar();
    while(c != EOF){
        input[size]=c;
        c=getchar();
        size++;
    }
    return size;  
}
bool cipher(int *encoding){
    bool valid=1;
    for(int i=0;i<=100;i++){
        encoding[i]=i;
    }
    for(int i=173;i<=177;i++){
        encoding[i]=i;
    }
    for(int i='a';i<='z';i++){
        encoding[i]=getchar();
        encoding['A'+ i -'a']='A' + encoding[i] -'a';
        for(int j='a';j<i;j++){
            if(encoding[i]==encoding[j] || encoding[i]<='A'){
                valid=0;
            }
        }
    }
    return valid;
}


int main(){
    int text[100000];
    int codec[100000];
    bool cip = cipher(codec);
    int text_size = readText(text);
    if(cip){
        for(int i=0;i<text_size;i++){
        printf("%c",codec[text[i]]);
    }
    }
    else{
        printf("error\n");
    }
    
}