#include<iostream>
#include"fullratio.hpp"

int main(){
    rational a(1,2);
    rational b(3,4);
    rational c(5,6);
    std::cout<< a+b-c<<std::endl;
    std::cout<< a << std::endl;
}