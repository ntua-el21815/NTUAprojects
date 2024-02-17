#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int main(){
    FILE *f;
    f = fopen("myfile.txt", "r");
    char cstr[42];
    int chars = 0;
    char text[10000];
    while(feof(f) == 0){
        fscanf(f, "%s", cstr);
        //print into f2 backwards
        for(int i = 0; i < int(strlen(cstr)); i++){
            text[chars] = cstr[strlen(cstr) - i - 1];
            chars++;
        }
        char c = fgetc(f);
        if(c != EOF){
            text[chars] = c;
            chars++;
        }
    }
    fclose(f);
    f = fopen("myfile.txt", "w");
    for(int i = 0; i < chars; i++){
        fprintf(f, "%c", text[i]);
    }
}