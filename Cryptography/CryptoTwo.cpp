#include<iostream>
#include<string>
using namespace std;

int readText(int *input){
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
void decoder(int *decoding,int *encoding){
    for(int i=0;i<=100;i++){
        decoding[i]=i;
    }
    for(int i=173;i<=177;i++){
        decoding[i]=i;
    }
    for(int i='a';i<='z';i++){
        decoding[encoding[i]]=i;
        decoding[encoding['A'+ i -'a']]='A' + i -'a';
        }
}

int main(){
    int text[100000];
    int codec[100000];
    int decodec[100000];
    bool cip = cipher(codec);
    char discard = getchar();
    string function;
    getline(cin,function);
    int text_size = readText(text);
    decoder(decodec,codec);
    if(cip){
        for(int i=0;i<text_size;i++){
        if(function[0] == 'e') printf("%c",codec[text[i]]);
        if(function[0] == 'd') printf("%c",decodec[text[i]]);
    }
    }
    else{
        printf("error\n");
    }
    
}