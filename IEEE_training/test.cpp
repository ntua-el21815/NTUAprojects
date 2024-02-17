#include<iostream>

int find_min_energy(int r,int c,int **forest){
    int **min_energies = new int*[r];
    for(int i=0;i<r;i++){
        min_energies[i] = new int[c];
    }
    min_energies[r-1][c-1] = 1;
    for(int i=r-1;i>=0;i--){
        for(int j=c-1;j>=0;j--){
            if(i==r-1 && j==c-1){
                continue;
            }
            else if(i==r-1){
                min_energies[i][j] = std::max(-forest[i][j] + min_energies[i][j+1],1);
            }
            else if(j==c-1){
                min_energies[i][j] = std::max(-forest[i][j] + min_energies[i+1][j],1);
            }
            else{
                min_energies[i][j] = std::max(-forest[i][j] + std::min(min_energies[i+1][j],min_energies[i][j+1]),1);
            }
        }
    }
    return min_energies[0][0];
}

int main(){
    int r,c;
    std::cin>>r>>c;
    int **forest = new int*[r];
    for(int i=0;i<r;i++){
        forest[i] = new int[c];
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            std::cin>>forest[i][j];
        }
    }
    std::cout<<find_min_energy(r,c,forest);
}