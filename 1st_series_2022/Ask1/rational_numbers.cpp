#include<iostream>
#include"babyratio.hpp"


int main(){
    rational a(1, 1);
    rational b(3, 4);
    rational c(5, 6);
    a.add(b).mul(c).print();
    std::cout << std::endl;
    a.print();
    std::cout << "should still be what it was" << std::endl;
}


